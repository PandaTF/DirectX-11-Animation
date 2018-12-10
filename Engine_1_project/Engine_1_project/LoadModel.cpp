#include "LoadModel.h"

LoadModel::LoadModel()
{
	modelContent = nullptr;
	numOfVertices = 0;
}

LoadModel::~LoadModel()
{
	Release();
}

bool LoadModel::InitializeModel(const char * filename)
{
	if (modelContent)
	{
		Release();
	}

	std::ifstream in(filename, std::ios_base::binary);

	in.read(reinterpret_cast<char*>(&numOfVertices), sizeof(int));
	numOfIndices = numOfVertices;
	modelContent = new SimpleVertex[numOfVertices];
	modelIndices = new unsigned int[numOfVertices];

	for (int i = 0; i < numOfVertices; i++)
	{
		SimpleVertex temp;
		in.read(reinterpret_cast<char*>(&modelContent[i].Pos.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].Pos.y), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].Pos.z), sizeof(float));

		in.read(reinterpret_cast<char*>(&modelContent[i].texCoord.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].texCoord.y), sizeof(float));

		in.read(reinterpret_cast<char*>(&modelContent[i].Normal.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].Normal.y), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].Normal.z), sizeof(float));

		in.read(reinterpret_cast<char*>(&modelContent[i].vertexColor.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].vertexColor.y), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].vertexColor.z), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].vertexColor.w), sizeof(float));

		in.read(reinterpret_cast<char*>(&modelContent[i].tangent.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].tangent.y), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].tangent.z), sizeof(float));

		in.read(reinterpret_cast<char*>(&modelContent[i].binormal.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].binormal.y), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].binormal.z), sizeof(float));

		in.read(reinterpret_cast<char*>(&modelContent[i].jointIndices.x), sizeof(int));
		in.read(reinterpret_cast<char*>(&modelContent[i].jointIndices.y), sizeof(int));
		in.read(reinterpret_cast<char*>(&modelContent[i].jointIndices.z), sizeof(int));
		in.read(reinterpret_cast<char*>(&modelContent[i].jointIndices.w), sizeof(int));

		in.read(reinterpret_cast<char*>(&modelContent[i].weights.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].weights.y), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].weights.z), sizeof(float));
		in.read(reinterpret_cast<char*>(&modelContent[i].weights.w), sizeof(float));

		modelIndices[i] = i;
	}

	in.read(reinterpret_cast<char*>(&model_Animation_Clip.hasAnimation), sizeof(bool));


	if (model_Animation_Clip.hasAnimation)
	{	
		in.read(reinterpret_cast<char*>(&model_Animation_Clip.duration), sizeof(double));

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

			if (i == 0)
			{
				//ignore the bindpose
				continue;
			}
			model_Animation_Clip.frame.push_back(tempKeyframe);
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

		model_Animation_Clip.duration -= model_Animation_Clip.duration * model_Animation_Clip.frame[0].time;
		double tempTime = model_Animation_Clip.frame[0].time;
		model_Animation_Clip.frame[0].time = 0.0f;
		for (int i = 1; i < model_Animation_Clip.frame.size(); i++)
		{
			model_Animation_Clip.frame[i].time -= tempTime;
		}
	}

	in.close();

	return true;
}

void LoadModel::Release()
{
	numOfVertices = 0;
	if (modelContent)
	{
		delete modelContent;
		modelContent = 0;
	}
}

SimpleVertex* LoadModel::getModelContent()
{
	return modelContent;
}

unsigned int * LoadModel::getModelIndices()
{
	return modelIndices;
}

int LoadModel::getNumOfVertices()
{
	return numOfVertices;
}

int LoadModel::getNumOfIndices()
{
	return numOfIndices;
}

bool LoadModel::hasAnimation()
{
	return model_Animation_Clip.hasAnimation;
}
