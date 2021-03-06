// FBX_lib.cpp : Defines the exported functions for the DLL application.
//

#include "header.h"
#include "FBX_lib.h"

bool FBX::Node_Influence_Sort(Influence lhs, Influence rhs)
{
	return lhs.weight > rhs.weight;
}

FBXLIB_API int FBX::get_scene_poly_count(const char * fbx_file_path)
{
	int result = -1;
	// Scene pointer, set by call to create_and_import
	FbxScene* scene = nullptr;
	// Create the FbxManager and import the scene from file
	FbxManager* sdk_manager = create_and_import(fbx_file_path, scene);
	// Check if manager creation failed
	if (sdk_manager == nullptr)
		return result;
	//If the scene was imported...
	if (scene != nullptr)
	{
		//No errors to report, so start polygon count at 0
		result = 0;
		// Get the count of geometry objects in the scene
		int geo_count = scene->GetGeometryCount();
		for (int i = 0; i < geo_count; ++i)
		{
			//Get geometry number 'i'
			FbxGeometry* geo = scene->GetGeometry(i);
			// If it's not a mesh, skip it
			// Geometries might be some other type like nurbs
			if (geo->GetAttributeType() != FbxNodeAttribute::eMesh)
				continue;
			// Found a mesh, add its polygon count to the result
			FbxMesh* mesh = (FbxMesh*)geo;
			result += mesh->GetPolygonCount();
		}
	}
	//Destroy the manager
	sdk_manager->Destroy();
	//Return the polygon count for the scene
	return result;
}

FBXLIB_API HRESULT FBX::get_scene_content(const char * fbx_file_path, std::vector<MyVertex>* pOutVertexVector, std::vector<Joint> *pOutAnimationJoint, clip* pOutAnimationClip)
{
	FbxScene* scene = nullptr;
	FbxManager* sdk_manager = create_and_import(fbx_file_path, scene);
	if (sdk_manager == nullptr)
		return S_FALSE;

	FbxNode* pFbxRootNode = scene->GetRootNode();

	//Skeleton /////////////////////////////////////////////////////////////////////////////////////
	FbxString name;

	int lPoseCount = scene->GetPoseCount();

	//Get the root node of pose (translate matrix)
	FbxPose* lPose = nullptr;
	for (int i = 0; i < lPoseCount; i++)
	{
		if (scene->GetPose(i)->IsBindPose())
		{
			lPose = scene->GetPose(i);
			break;
		}
	}

	if (lPose == nullptr)
	{
		printf("There is no pose for this fbx.");
		return S_FALSE;
	}

	//Get the root node of skeleton
	int nodeCount = lPose->GetCount();
	FbxSkeleton *skeleton = nullptr;

	for (int i = 0; i < nodeCount; i++)
	{
		if (lPose->GetNode(i)->GetSkeleton() != NULL && lPose->GetNode(i)->GetSkeleton()->IsSkeletonRoot())
		{
			skeleton = lPose->GetNode(i)->GetSkeleton();
			break;
		}
	}

	if (skeleton == nullptr)
	{
		printf("There is no skeleton for this fbx.");
		return S_FALSE;
	}

	std::vector<fbx_Joint> joints;
	fbx_Joint rootNode;
	rootNode.node = skeleton->GetNode();
	rootNode.parentIndex = -1;
	joints.push_back(rootNode);

	//BFS get all the children of skeletons
	for (int i = 0; i < joints.size(); i++)
	{
		int childCount = joints[i].node->GetChildCount();
		for (int j = 0; j < childCount; j++)
		{
			if (joints[i].node->GetChild(j)->GetSkeleton() != NULL)
			{
				fbx_Joint temp;
				temp.node = joints[i].node->GetChild(j);
				temp.parentIndex = i;
				joints.push_back(temp);
			}
		}
	}

	//Create the joint for return (First return)
	std::vector<Joint> myJoints;

	for (int i = 0; i < joints.size(); i++)
	{
		Joint temp;

		FbxAMatrix matrix;
		matrix = joints[i].node->EvaluateGlobalTransform();

		//temp.mGlobalBindPoseInverse = matrix;
		temp.mGlobalBindPoseInverse.x1 = matrix[0][0];
		temp.mGlobalBindPoseInverse.x2 = matrix[0][1];
		temp.mGlobalBindPoseInverse.x3 = matrix[0][2];
		temp.mGlobalBindPoseInverse.x4 = matrix[0][3];

		temp.mGlobalBindPoseInverse.y1 = matrix[1][0];
		temp.mGlobalBindPoseInverse.y2 = matrix[1][1];
		temp.mGlobalBindPoseInverse.y3 = matrix[1][2];
		temp.mGlobalBindPoseInverse.y4 = matrix[1][3];

		temp.mGlobalBindPoseInverse.z1 = matrix[2][0];
		temp.mGlobalBindPoseInverse.z2 = matrix[2][1];
		temp.mGlobalBindPoseInverse.z3 = matrix[2][2];
		temp.mGlobalBindPoseInverse.z4 = matrix[2][3];

		temp.mGlobalBindPoseInverse.w1 = matrix[3][0];
		temp.mGlobalBindPoseInverse.w2 = matrix[3][1];
		temp.mGlobalBindPoseInverse.w3 = matrix[3][2];
		temp.mGlobalBindPoseInverse.w4 = matrix[3][3];
		
		temp.mParentIndex = joints[i].parentIndex;

		//myJoints.push_back(temp);
		pOutAnimationJoint->push_back(temp);
	}

	FbxAnimStack* animation = nullptr;
	animation = scene->GetCurrentAnimationStack();

	if (animation == nullptr)
	{
		printf("There is not animation for this fbx.");
		return S_FALSE;
	}

	//the start time and end time of the whole animation
	FbxTimeSpan time = animation->GetLocalTimeSpan();
	//How long this animation takes
	FbxTime fbxTime = time.GetDuration();
	//How many frame totally
	FbxLongLong frameCount = fbxTime.GetFrameCount(FbxTime::EMode::eFrames24);

	//Create the animationClip for return (Second return);
	clip animationClip;

	for (FbxLongLong i = 0; i < frameCount; i++)
	{
		Keyframe frame;

		fbxTime.SetFrame(i, FbxTime::EMode::eFrames24);
		frame.time = fbxTime.GetFramedTime().GetSecondDouble();

		for (int j = 0; j < joints.size(); j++)
		{
			FbxAMatrix globalTransform = joints[j].node->EvaluateGlobalTransform(fbxTime);
			myMatrix temp;
			
			//temp = globalTransform;
			temp.x1 = globalTransform[0][0];
			temp.x2 = globalTransform[0][1];
			temp.x3 = globalTransform[0][2];
			temp.x4 = globalTransform[0][3];

			temp.y1 = globalTransform[1][0];
			temp.y2 = globalTransform[1][1];
			temp.y3 = globalTransform[1][2];
			temp.y4 = globalTransform[1][3];

			temp.z1 = globalTransform[2][0];
			temp.z2 = globalTransform[2][1];
			temp.z3 = globalTransform[2][2];
			temp.z4 = globalTransform[2][3];

			temp.w1 = globalTransform[3][0];
			temp.w2 = globalTransform[3][1];
			temp.w3 = globalTransform[3][2];
			temp.w4 = globalTransform[3][3];

			frame.translateMatrix.push_back(temp);
		}
		//animationClip.frame.push_back(frame);
		pOutAnimationClip->frame.push_back(frame);
	}
	//animationClip.duration = (double)time.GetDuration().GetMilliSeconds();
	pOutAnimationClip->duration = (double)time.GetDuration().GetMilliSeconds();

	//animationClip.hasAnimation = true;
	pOutAnimationClip->hasAnimation = true;


	//Skinned Animation //////////////////////////////////////////////////////////////////////////

	if (pFbxRootNode)
	{
		for (int i = 0; i < pFbxRootNode->GetChildCount(); i++)
		{
			FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);

			if (pFbxChildNode->GetNodeAttribute() == NULL)
				continue;

			FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

			if (AttributeType != FbxNodeAttribute::eMesh)
				continue;

			FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();

			//Skinned Animation
			num_control_points_in_mesh = pMesh->GetPolygonCount() * 3;
		}
	}

	control_point_influences.resize(num_control_points_in_mesh);

	//Initialize values in control_point_influences
	for (int i = 0; i < control_point_influences.size(); i++)
	{
		control_point_influences[i].node.resize(4);
		for (int j = 0; j < 4; j++)
		{
			control_point_influences[i].node[j].joint = -1;
			control_point_influences[i].node[j].weight = 0.0f;
		}
	}

	FbxMesh *skinnedMesh = nullptr;
	for (int i = 0; i < nodeCount; i++)
	{
		if (lPose->GetNode(i)->GetMesh() != NULL)
		{
			skinnedMesh = lPose->GetNode(i)->GetMesh();
			break;
		}
	}
	
	if (skinnedMesh == nullptr)
	{
		printf("There is no skin mesh for this fbx.");
		return S_FALSE;
	}

	FbxSkin *skin = nullptr;
	int deformerCount = skinnedMesh->GetDeformerCount();
	for (int i = 0; i < deformerCount; i++)
	{
		if (skinnedMesh->GetDeformer(i) != NULL && skinnedMesh->GetDeformer(i)->Is<FbxSkin>())
		{
			skin = (FbxSkin*)skinnedMesh->GetDeformer(i);
			break;
		}
	}

	if (skin == nullptr)
	{
		printf("There is no skin for this fbx.");
		return S_FALSE;
	}

	//28 clusters for 28 joints
	int clusterCount = skin->GetClusterCount();

	for (int i = 0; i < clusterCount; i++)
	{
		FbxNode* tempLinkedNode = skin->GetCluster(i)->GetLink();

		int JOINT_INDEX = -1;
		for (int j = 0; j < joints.size(); j++)
		{
			if (joints[j].node == tempLinkedNode)
			{
				JOINT_INDEX = j;
				break;
			}
		}

		int CPindexCount = skin->GetCluster(i)->GetControlPointIndicesCount();
		double *Weight = skin->GetCluster(i)->GetControlPointWeights();
		int *CPindex = skin->GetCluster(i)->GetControlPointIndices();

		for (int j = 0; j < CPindexCount; j++)
		{

			Influence temp;
			temp.weight = Weight[j];
			temp.joint = JOINT_INDEX;
			
			control_point_influences[CPindex[j]].node.push_back(temp);
			
			std::sort(control_point_influences[CPindex[j]].node.begin(),
				control_point_influences[CPindex[j]].node.end(),
				Node_Influence_Sort);
			
			//remove the last one if more than 4
			if (control_point_influences[CPindex[j]].node.size() >= 4)
			{
				control_point_influences[CPindex[j]].node.pop_back();
			}
		}
	}
	//Static Mesh Info///////////////////////////////////////////////////////////////////////////////////////
	if (pFbxRootNode)
	{
		for (int i = 0; i < pFbxRootNode->GetChildCount(); i++)
		{
			FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);

			if (pFbxChildNode->GetNodeAttribute() == NULL)
				continue;

			FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

			if (AttributeType != FbxNodeAttribute::eMesh)
				continue;

			FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();

			FbxVector4* pVertices = pMesh->GetControlPoints();

			int vertexCounter = 0;


			for (int j = 0; j < pMesh->GetPolygonCount(); j++)
			{
				int iNumVertices = pMesh->GetPolygonSize(j);
				//VERIFY(iNumVertices == 3);

				for (int k = 0; k < iNumVertices; k++)
				{
					//Vertices
					int iControlPointIndex = pMesh->GetPolygonVertex(j, k);
					MyVertex vertex;
					vertex.pos[0] = (float)pVertices[iControlPointIndex].mData[0];
					vertex.pos[1] = (float)pVertices[iControlPointIndex].mData[1];
					vertex.pos[2] = (float)pVertices[iControlPointIndex].mData[2];

					//Vertex Color
					//for (int l = 0; l < pMesh->GetElementVertexColorCount(); l++)
					//{
					FbxGeometryElementVertexColor* leVtxc = pMesh->GetElementVertexColor(0);
					if (leVtxc)
					{
						switch (leVtxc->GetMappingMode())
						{
						default:
							break;
						case FbxGeometryElement::eByControlPoint:
							switch (leVtxc->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								vertex.vertexColor[0] = (float)leVtxc->GetDirectArray().GetAt(iControlPointIndex).mAlpha;
								vertex.vertexColor[1] = (float)leVtxc->GetDirectArray().GetAt(iControlPointIndex).mRed;
								vertex.vertexColor[2] = (float)leVtxc->GetDirectArray().GetAt(iControlPointIndex).mGreen;
								vertex.vertexColor[3] = (float)leVtxc->GetDirectArray().GetAt(iControlPointIndex).mBlue;
							}
							break;
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leVtxc->GetIndexArray().GetAt(iControlPointIndex);
								vertex.vertexColor[0] = (float)leVtxc->GetDirectArray().GetAt(id).mAlpha;
								vertex.vertexColor[1] = (float)leVtxc->GetDirectArray().GetAt(id).mRed;
								vertex.vertexColor[2] = (float)leVtxc->GetDirectArray().GetAt(id).mGreen;
								vertex.vertexColor[3] = (float)leVtxc->GetDirectArray().GetAt(id).mBlue;
							}
							break;
							default:
								break; // other reference modes not shown here!
							}
							break;

						case FbxGeometryElement::eByPolygonVertex:
						{
							switch (leVtxc->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								vertex.vertexColor[0] = (float)leVtxc->GetDirectArray().GetAt(vertexCounter).mAlpha;
								vertex.vertexColor[1] = (float)leVtxc->GetDirectArray().GetAt(vertexCounter).mRed;
								vertex.vertexColor[2] = (float)leVtxc->GetDirectArray().GetAt(vertexCounter).mGreen;
								vertex.vertexColor[3] = (float)leVtxc->GetDirectArray().GetAt(vertexCounter).mBlue;

							}
							break;
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leVtxc->GetIndexArray().GetAt(vertexCounter);
								vertex.vertexColor[0] = (float)leVtxc->GetDirectArray().GetAt(id).mAlpha;
								vertex.vertexColor[1] = (float)leVtxc->GetDirectArray().GetAt(id).mRed;
								vertex.vertexColor[2] = (float)leVtxc->GetDirectArray().GetAt(id).mGreen;
								vertex.vertexColor[3] = (float)leVtxc->GetDirectArray().GetAt(id).mBlue;
							}
							break;
							default:
								break; // other reference modes not shown here!
							}
						}
						break;
						}
					}
					else
					{
						vertex.vertexColor[0] = vertex.vertexColor[1] = vertex.vertexColor[2] = vertex.vertexColor[3] = 0.0f;
					}
					//}

					//UVs
					for (int l = 0; l < pMesh->GetElementUVCount(); ++l)
					{
						FbxGeometryElementUV* leUV = pMesh->GetElementUV(l);

						switch (leUV->GetMappingMode())
						{
						default:
							break;
						case FbxGeometryElement::eByControlPoint:
							switch (leUV->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
								vertex.uv[0] = (float)(leUV->GetDirectArray().GetAt(iControlPointIndex).mData[0]);
								vertex.uv[1] = (float)(leUV->GetDirectArray().GetAt(iControlPointIndex).mData[1]);
								break;
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leUV->GetIndexArray().GetAt(iControlPointIndex);
								vertex.uv[0] = (float)(leUV->GetDirectArray().GetAt(id).mData[0]);
								vertex.uv[1] = (float)(leUV->GetDirectArray().GetAt(id).mData[1]);
							}
							break;
							default:
								break; // other reference modes not shown here!
							}
							break;

						case FbxGeometryElement::eByPolygonVertex:
						{
							int lTextureUVIndex = pMesh->GetTextureUVIndex(j, k);
							switch (leUV->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							case FbxGeometryElement::eIndexToDirect:
							{
								vertex.uv[0] = (float)leUV->GetDirectArray().GetAt(lTextureUVIndex).mData[0];
								vertex.uv[1] = 1.0f - (float)leUV->GetDirectArray().GetAt(lTextureUVIndex).mData[1];
							}
							break;
							default:
								break; // other reference modes not shown here!
							}
						}
						break;
						}
					}

					//Normals
					if (pMesh->GetElementNormalCount() < 1)
					{
						vertex.normal[0] = 0.0f;
						vertex.normal[1] = 0.0f;
						vertex.normal[2] = 0.0f;
					}
					else
					{

						FbxGeometryElementNormal* vertexNormal = pMesh->GetElementNormal(0);

						switch (vertexNormal->GetMappingMode())
						{
						case FbxGeometryElement::eByControlPoint:
							switch (vertexNormal->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								vertex.normal[0] = -1 * (float)(vertexNormal->GetDirectArray().GetAt(iControlPointIndex).mData[0]);
								vertex.normal[1] = (float)(vertexNormal->GetDirectArray().GetAt(iControlPointIndex).mData[1]);
								vertex.normal[2] = (float)(vertexNormal->GetDirectArray().GetAt(iControlPointIndex).mData[2]);
							}
							break;
							case FbxGeometryElement::eIndexToDirect:
							{
								int index = vertexNormal->GetIndexArray().GetAt(iControlPointIndex);
								vertex.normal[0] = -1 * (float)(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
								vertex.normal[1] = (float)(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
								vertex.normal[2] = (float)(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
							}
							break;
							}
							break;

						case FbxGeometryElement::eByPolygonVertex:
							switch (vertexNormal->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								vertex.normal[0] = -1 * (float)(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
								vertex.normal[1] = (float)(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
								vertex.normal[2] = (float)(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
							}
							break;
							case FbxGeometryElement::eIndexToDirect:
							{
								int index = vertexNormal->GetIndexArray().GetAt(vertexCounter);
								vertex.normal[0] = -1 * (float)(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
								vertex.normal[1] = (float)(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
								vertex.normal[2] = (float)(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
							}
							break;

							default:
								break;
							}
							break;
						}
					}

					//Tangent
					if (pMesh->GetElementTangentCount() < 1)
					{
						vertex.tangent[0] = 0.0f;
						vertex.tangent[1] = 0.0f;
						vertex.tangent[2] = 0.0f;
					}
					else
					{
						FbxGeometryElementTangent* leTangent = pMesh->GetElementTangent(0);

						if (leTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
						{
							switch (leTangent->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								vertex.tangent[0] = -1 * (float)leTangent->GetDirectArray().GetAt(vertexCounter).mData[0];
								vertex.tangent[1] = (float)leTangent->GetDirectArray().GetAt(vertexCounter).mData[1];
								vertex.tangent[2] = (float)leTangent->GetDirectArray().GetAt(vertexCounter).mData[2];
							}
							break;
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leTangent->GetIndexArray().GetAt(vertexCounter);

								vertex.tangent[0] = -1 * (float)leTangent->GetDirectArray().GetAt(id).mData[0];
								vertex.tangent[1] = (float)leTangent->GetDirectArray().GetAt(id).mData[1];
								vertex.tangent[2] = (float)leTangent->GetDirectArray().GetAt(id).mData[2];
							}
							break;
							default:
								break;
							}
						}
					}

					//Binormal
					if (pMesh->GetElementBinormalCount() < 1)
					{
						vertex.binormal[0] = 0.0f;
						vertex.binormal[1] = 0.0f;
						vertex.binormal[2] = 0.0f;
					}
					else
					{
						FbxGeometryElementBinormal* leBinormal = pMesh->GetElementBinormal(0);

						if (leBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
						{
							switch (leBinormal->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								vertex.binormal[0] = -1 * (float)leBinormal->GetDirectArray().GetAt(vertexCounter).mData[0];
								vertex.binormal[1] = (float)leBinormal->GetDirectArray().GetAt(vertexCounter).mData[1];
								vertex.binormal[2] = (float)leBinormal->GetDirectArray().GetAt(vertexCounter).mData[2];
							}
							break;
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leBinormal->GetIndexArray().GetAt(vertexCounter);

								vertex.binormal[0] = -1 * (float)leBinormal->GetDirectArray().GetAt(id).mData[0];
								vertex.binormal[1] = (float)leBinormal->GetDirectArray().GetAt(id).mData[1];
								vertex.binormal[2] = (float)leBinormal->GetDirectArray().GetAt(id).mData[2];
							}
							break;
							default:
								break;
							}
						}
					}

					vertex.joints[0] = control_point_influences[iControlPointIndex].node[0].joint;
					vertex.joints[1] = control_point_influences[iControlPointIndex].node[1].joint;
					vertex.joints[2] = control_point_influences[iControlPointIndex].node[2].joint;
					vertex.joints[3] = control_point_influences[iControlPointIndex].node[3].joint;
					
					vertex.weights[0] = control_point_influences[iControlPointIndex].node[0].weight;
					vertex.weights[1] = control_point_influences[iControlPointIndex].node[1].weight;
					vertex.weights[2] = control_point_influences[iControlPointIndex].node[2].weight;
					vertex.weights[3] = control_point_influences[iControlPointIndex].node[3].weight;
					
					float sum = vertex.weights[0] + vertex.weights[1] + vertex.weights[2] + vertex.weights[3];
					for (int i = 0; i < 4; i++)
					{
						vertex.weights[i] /= sum;
					}

					pOutVertexVector->push_back(vertex);
					vertexCounter++;
				}
			}
		}
	}


	return S_OK;
}

FBXLIB_API FbxManager * FBX::create_and_import(const char * fbx_file_path, FbxScene *& IScene)
{
	// Initialize the SDK manager. This object handles all our memory management.
	FbxManager* lSdkManager = FbxManager::Create();
	// Create the IO settings object.
	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);
	// Create an importer using the SDK manager.
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
	// Use the first argument as the filename for the importer.
	if (!lImporter->Initialize(fbx_file_path, -1, lSdkManager->GetIOSettings())) {
		//printf("Call to FbxImporter::Initialize() failed.\n");
		//printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
		return nullptr;
	}
	// Create a new scene so that it can be populated by the imported file.
	IScene = FbxScene::Create(lSdkManager, "imported_scene");
	// Import the contents of the file into the scene.
	lImporter->Import(IScene);
	lImporter->Destroy();
	return lSdkManager;
}
