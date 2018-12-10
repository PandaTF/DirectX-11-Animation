#pragma once
#include "defines.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class LoadModel
{
public:
	LoadModel();
	~LoadModel();

	bool InitializeModel(const char* filename);
	void Release();

	SimpleVertex* getModelContent();
	unsigned int* getModelIndices();
	int getNumOfVertices();
	int getNumOfIndices();

	bool hasAnimation();

	std::vector<Joint>& GetModelAnimationJoint() { return model_Animation_Joint; }
	clip* GetModelAnimationClip() { return &model_Animation_Clip; }

private:
	//std::vector<SimpleVertex> modelContent;
	SimpleVertex * modelContent;
	unsigned int * modelIndices;
	int numOfVertices;
	int numOfIndices;

	//Animation Variables
	std::vector<Joint> model_Animation_Joint;
	clip model_Animation_Clip;
};