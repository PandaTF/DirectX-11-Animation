#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define WRITE_BINARY 1
#define READ_BINARY 1

struct MyVertex
{
	float pos[3];
	float uv[2];
	float normal[3];

	float vertexColor[4];
	float tangent[3];
	float binormal[3];

	int joints[4];
	float weight[4];
};

struct myMatrix
{
	double x1, x2, x3, x4;
	double y1, y2, y3, y4;
	double z1, z2, z3, z4;
	double w1, w2, w3, w4;
};

struct Keyframe
{
	double time;
	std::vector<myMatrix> translateMatrx;
};

struct Joint
{
	int mParentIndex;
	myMatrix myMatrix;
};

struct clip
{
	bool hasAnimation;
	double duration = 0.0f;
	std::vector<Keyframe> frame;
};


struct TEST
{
	int index;
	int joints[4];
	float weight[4];
};

using func_ptr_get_poly_count = int(*)(const char*);
using func_ptr_get_scene_vertex = HRESULT(*)(const char*, std::vector<MyVertex>*, std::vector<Joint>*, clip*);

int main()
{
#if WRITE_BINARY
	bool result;
	//FBX
	std::vector<MyVertex> FBX_vector_vertex;
	std::vector<Joint> FBX_animation_joint;
	clip FBX_animation_clip;

	HMODULE dll_module = LoadLibrary(L"FBXLIB.dll");
	func_ptr_get_poly_count FBX_GetPolyCount = (func_ptr_get_poly_count)GetProcAddress(dll_module, "get_scene_poly_count");
	func_ptr_get_scene_vertex FBX_GetSceneContent = (func_ptr_get_scene_vertex)GetProcAddress(dll_module, "get_scene_content");

	//std::string filename = "../Engine_1_project/Resources/Fbx/Idle.fbx";
	std::string filename = "../Engine_1_project/Resources/Fbx/Run.fbx";

	int polyCount = 0;
	polyCount = FBX_GetPolyCount(filename.c_str());
	result = FBX_GetSceneContent(filename.c_str(), &FBX_vector_vertex, &FBX_animation_joint, &FBX_animation_clip);

	std::vector<TEST> test;
	for (int i = 0; i < FBX_vector_vertex.size(); i++)
	{
		if (FBX_vector_vertex[i].joints[0] != -1)
		{
			TEST temp;
			temp.index = i;
			for (int j = 0; j < 4; j++) {
				temp.joints[j] = FBX_vector_vertex[i].joints[j];
				temp.weight[j] = FBX_vector_vertex[i].weight[j];
			}
			test.push_back(temp);
		}
	}

	//int x = 7;
	//
	//std::ofstream o("text.dat", std::ios_base::binary);
	//o.write(reinterpret_cast<char*>(&x), sizeof(int));
	//o.write(reinterpret_cast<char*>(&x), sizeof(int));
	//o.close();

	//int z = 0;
	//int w = 0;
	//std::ifstream in("text.dat", std::ios_base::binary);
	//in.read(reinterpret_cast<char*>(&z), sizeof(int));
	//in.read(reinterpret_cast<char*>(&w), sizeof(int));
	//std::cout << z << std::endl << w << std::endl;
	//in.close();


	//WRITING MODEL INTO BINARY FILE
	//std::ofstream o("Idle.dat", std::ios_base::binary);
	std::ofstream o("Run.dat", std::ios_base::binary);
	//num of vertex
	unsigned int numOfVertex_write = polyCount * 3;
	//record num of vertex
	o.write(reinterpret_cast<char*>(&numOfVertex_write), sizeof(unsigned int));
	//writing...
	for (unsigned int i = 0; i < numOfVertex_write; i++)
	{
		//coordinate
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].pos[0]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].pos[1]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].pos[2]), sizeof(float));
		//texture coordinate
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].uv[0]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].uv[1]), sizeof(float));
		//normal
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].normal[0]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].normal[1]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].normal[2]), sizeof(float));
		//vertex color
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].vertexColor[0]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].vertexColor[1]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].vertexColor[2]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].vertexColor[3]), sizeof(float));
		//Tangent
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].tangent[0]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].tangent[1]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].tangent[2]), sizeof(float));
		//Binormal
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].binormal[0]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].binormal[1]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].binormal[2]), sizeof(float));
		//Joints Index
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].joints[0]), sizeof(int));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].joints[1]), sizeof(int));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].joints[2]), sizeof(int));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].joints[3]), sizeof(int));
		//Weight
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].weight[0]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].weight[1]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].weight[2]), sizeof(float));
		o.write(reinterpret_cast<char*>(&FBX_vector_vertex[i].weight[3]), sizeof(float));
	}

	o.write(reinterpret_cast<char*>(&FBX_animation_clip.hasAnimation), sizeof(bool));
	if (FBX_animation_clip.hasAnimation)
	{
		o.write(reinterpret_cast<char*>(&FBX_animation_clip.duration), sizeof(double));

		int numKeyframe = (int)FBX_animation_clip.frame.size();
		o.write(reinterpret_cast<char*>(&numKeyframe), sizeof(int));
		for (int i = 0; i < numKeyframe; i++)
		{
			o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].time), sizeof(double));

			int numMatrix = (int)FBX_animation_clip.frame[i].translateMatrx.size();
			o.write(reinterpret_cast<char*>(&numMatrix), sizeof(int));

			for (int j = 0; j < numMatrix; j++)
			{
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].x1), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].x2), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].x3), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].x4), sizeof(double));

				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].y1), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].y2), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].y3), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].y4), sizeof(double));

				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].z1), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].z2), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].z3), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].z4), sizeof(double));

				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].w1), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].w2), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].w3), sizeof(double));
				o.write(reinterpret_cast<char*>(&FBX_animation_clip.frame[i].translateMatrx[j].w4), sizeof(double));
			}
		}

		int numJoint = FBX_animation_joint.size();
		o.write(reinterpret_cast<char*>(&numJoint), sizeof(int));
		for (int i = 0; i < numJoint; i++)
		{
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].mParentIndex), sizeof(int));
		
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.x1), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.x2), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.x3), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.x4), sizeof(double));
		
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.y1), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.y2), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.y3), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.y4), sizeof(double));
		
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.z1), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.z2), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.z3), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.z4), sizeof(double));
		
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.w1), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.w2), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.w3), sizeof(double));
			o.write(reinterpret_cast<char*>(&FBX_animation_joint[i].myMatrix.w4), sizeof(double));
		}
	}
	//close
	o.close();
#endif

#if READ_BINARY
	//READING BINARY INTO VECTOR
	//std::ifstream in("Idle.dat", std::ios_base::binary);
	std::ifstream in("Run.dat", std::ios_base::binary);
	//num of vertex
	int numOfVertex_read = 0;
	//read num of vertex
	in.read(reinterpret_cast<char*>(&numOfVertex_read), sizeof(int));
	//create container
	std::vector<MyVertex> modelVec;
	std::vector<Joint> model_Animation_Joint;
	clip model_animation_clip;
	//reading...
	for (int i = 0; i < numOfVertex_read; i++)
	{
		MyVertex temp;
		in.read(reinterpret_cast<char*>(&temp.pos[0]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.pos[1]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.pos[2]), sizeof(float));

		in.read(reinterpret_cast<char*>(&temp.uv[0]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.uv[1]), sizeof(float));
		
		in.read(reinterpret_cast<char*>(&temp.normal[0]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.normal[1]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.normal[2]), sizeof(float));

		in.read(reinterpret_cast<char*>(&temp.vertexColor[0]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.vertexColor[1]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.vertexColor[2]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.vertexColor[3]), sizeof(float));

		in.read(reinterpret_cast<char*>(&temp.tangent[0]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.tangent[1]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.tangent[2]), sizeof(float));

		in.read(reinterpret_cast<char*>(&temp.binormal[0]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.binormal[1]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.binormal[2]), sizeof(float));

		in.read(reinterpret_cast<char*>(&temp.joints[0]), sizeof(int));
		in.read(reinterpret_cast<char*>(&temp.joints[1]), sizeof(int));
		in.read(reinterpret_cast<char*>(&temp.joints[2]), sizeof(int));
		in.read(reinterpret_cast<char*>(&temp.joints[3]), sizeof(int));

		in.read(reinterpret_cast<char*>(&temp.weight[0]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.weight[1]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.weight[2]), sizeof(float));
		in.read(reinterpret_cast<char*>(&temp.weight[3]), sizeof(float));

		modelVec.push_back(temp);
	}


	//Reading animation
	in.read(reinterpret_cast<char*>(&model_animation_clip.hasAnimation), sizeof(bool));

	if (model_animation_clip.hasAnimation)
	{
		in.read(reinterpret_cast<char*>(&model_animation_clip.duration), sizeof(double));

		int numKeyframe;
		in.read(reinterpret_cast<char*>(&numKeyframe), sizeof(int));
		for (int i = 0; i < numKeyframe; i++)
		{
			Keyframe tempKeyframe;
			in.read(reinterpret_cast<char*>(&tempKeyframe.time), sizeof(double));
			int numMatrix;
			in.read(reinterpret_cast<char*>(&numMatrix), sizeof(int));
			for (int j = 0; j < numMatrix; j++)
			{
				myMatrix tempMatrix;
				in.read(reinterpret_cast<char*>(&tempMatrix.x1), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.x2), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.x3), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.x4), sizeof(double));

				in.read(reinterpret_cast<char*>(&tempMatrix.y1), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.y2), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.y3), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.y4), sizeof(double));

				in.read(reinterpret_cast<char*>(&tempMatrix.z1), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.z2), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.z3), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.z4), sizeof(double));

				in.read(reinterpret_cast<char*>(&tempMatrix.w1), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.w2), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.w3), sizeof(double));
				in.read(reinterpret_cast<char*>(&tempMatrix.w4), sizeof(double));

				tempKeyframe.translateMatrx.push_back(tempMatrix);
			}

			model_animation_clip.frame.push_back(tempKeyframe);
		}

		int numJoint;
		in.read(reinterpret_cast<char*>(&numJoint), sizeof(int));
		for (int i = 0; i < numJoint; i++)
		{
			Joint tempJoint;
			in.read(reinterpret_cast<char*>(&tempJoint.mParentIndex), sizeof(int));
		
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.x1), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.x2), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.x3), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.x4), sizeof(double));
		
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.y1), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.y2), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.y3), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.y4), sizeof(double));
		
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.z1), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.z2), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.z3), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.z4), sizeof(double));
		
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.w1), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.w2), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.w3), sizeof(double));
			in.read(reinterpret_cast<char*>(&tempJoint.myMatrix.w4), sizeof(double));
		
			model_Animation_Joint.push_back(tempJoint);
		}
	}

	in.close();

	//display number of vertex in binary file
	std::cout << numOfVertex_read << std::endl;

	//display data on screen
	for (int i = 0; i < numOfVertex_read; i++)
	{
		std::cout << "Polygon " << i << " :" << std::endl;
		std::cout << "Position " << std::endl;
		std::cout << modelVec[i].pos[0] << " " << modelVec[i].pos[1] << " " << modelVec[i].pos[2] << std::endl;
		std::cout << "UV " << std::endl;
		std::cout << modelVec[i].uv[0] << " " << modelVec[i].uv[1] << std::endl;
		std::cout << "Normal " << std::endl;
		std::cout << modelVec[i].normal[0] << " " << modelVec[i].normal[1] << " " << modelVec[i].normal[2] << std::endl;
		std::cout << "Vertex Color " << std::endl;
		std::cout << modelVec[i].vertexColor[0] << " " << modelVec[i].vertexColor[1] << " " << modelVec[i].vertexColor[2] << " " << modelVec[i].vertexColor[3] << std::endl;
		std::cout << "Tangent  " << std::endl;
		std::cout << modelVec[i].tangent[0] << " " << modelVec[i].tangent[1] << " " << modelVec[i].tangent[2] << std::endl;
		std::cout << "Binormal  " << std::endl;
		std::cout << modelVec[i].binormal[0] << " " << modelVec[i].binormal[1] << " " << modelVec[i].binormal[2] << std::endl;
		std::cout << "Joint Indices  " << std::endl;
		std::cout << modelVec[i].joints[0] << " " << modelVec[i].joints[1] << " " << modelVec[i].joints[2] << modelVec[i].joints[3] << std::endl;
		std::cout << "Weight  " << std::endl;
		std::cout << modelVec[i].weight[0] << " " << modelVec[i].weight[1] << " " << modelVec[i].weight[2] << " " << modelVec[i].weight[3] << std::endl;
	}


	if (model_animation_clip.hasAnimation)
	{
		std::cout << "FBX has animation" << std::endl;
	
		std::cout << "Animation Clip Info:" << std::endl;
		std::cout << "Clip duration: " << model_animation_clip.duration << std::endl;
		for (int i = 0; i < model_animation_clip.frame.size(); i++)
		{
			std::cout << "Keyframe No. " << i << " :" << std::endl;
			std::cout << "time: " << model_animation_clip.frame[i].time << std::endl << std::endl;;
		
			for (int j = 0; j < model_animation_clip.frame[i].translateMatrx.size(); j++)
			{
				std::cout << "Matrix No. " << j << " :" << std::endl;
				std::cout << model_animation_clip.frame[i].translateMatrx[j].x1 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].x2 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].x3 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].x4 << std::endl;
		
				std::cout << model_animation_clip.frame[i].translateMatrx[j].y1 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].y2 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].y3 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].y4 << std::endl;
		
				std::cout << model_animation_clip.frame[i].translateMatrx[j].z1 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].z2 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].z3 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].z4 << std::endl;
		
				std::cout << model_animation_clip.frame[i].translateMatrx[j].w1 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].w2 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].w3 << " " <<
					model_animation_clip.frame[i].translateMatrx[j].w4 << std::endl;
		
				std::cout << std::endl;
			}
		}
		
		std::cout << std::endl << std::endl;
	
		std::cout << "Animation Joint Info: " << std::endl;
		for (int i = 0; i < model_Animation_Joint.size(); i++)
		{
			std::cout << "Joint No. " << i << " : " << std::endl;
			std::cout << "Joint Parent Index: " << model_Animation_Joint[i].mParentIndex << std::endl;
		
			std::cout << model_Animation_Joint[i].myMatrix.x1 << " " <<
				model_Animation_Joint[i].myMatrix.x2 << " " <<
				model_Animation_Joint[i].myMatrix.x3 << " " <<
				model_Animation_Joint[i].myMatrix.x4 << std::endl;
		
			std::cout << model_Animation_Joint[i].myMatrix.y1 << " " <<
				model_Animation_Joint[i].myMatrix.y2 << " " <<
				model_Animation_Joint[i].myMatrix.y3 << " " <<
				model_Animation_Joint[i].myMatrix.y4 << std::endl;
		
			std::cout << model_Animation_Joint[i].myMatrix.z1 << " " <<
				model_Animation_Joint[i].myMatrix.z2 << " " <<
				model_Animation_Joint[i].myMatrix.z3 << " " <<
				model_Animation_Joint[i].myMatrix.z4 << std::endl;
		
			std::cout << model_Animation_Joint[i].myMatrix.w1 << " " <<
				model_Animation_Joint[i].myMatrix.w2 << " " <<
				model_Animation_Joint[i].myMatrix.w3 << " " <<
				model_Animation_Joint[i].myMatrix.w4 << std::endl;
		}
	}
	else
	{
		std::cout << "FBX doesn't has animation" << std::endl;
	}
#endif

	system("pause");
	return 0;
}