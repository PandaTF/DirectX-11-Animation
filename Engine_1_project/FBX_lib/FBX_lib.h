// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FBXLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FBXLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FBXLIB_EXPORTS
#define FBXLIB_API __declspec(dllexport)
#else
#define FBXLIB_API __declspec(dllimport)
#endif
#include "FBX_Helper.h"

extern "C"
{
	namespace FBX
	{
		struct MyVertex
		{
			float pos[3];
			float uv[2];
			float normal[3];

			float vertexColor[4];
			float tangent[3];
			float binormal[3];

			int	  joints[4];
			float weights[4];
		};

		struct myMatrix
		{
			double x1, x2, x3, x4;
			double y1, y2, y3, y4;
			double z1, z2, z3, z4;
			double w1, w2, w3, w4;
			/*

			void operator=(FbxAMatrix matrix)
			{
				x1 = matrix[0][0];
				x1 = matrix[0][1];
				x1 = matrix[0][2];
				x1 = matrix[0][3];

				x1 = matrix[1][0];
				x1 = matrix[1][1];
				x1 = matrix[1][2];
				x1 = matrix[1][3];

				x1 = matrix[2][0];
				x1 = matrix[2][1];
				x1 = matrix[2][2];
				x1 = matrix[2][3];

				x1 = matrix[3][0];
				x1 = matrix[3][1];
				x1 = matrix[3][2];
				x1 = matrix[3][3];
			}

			void operator=(FbxMatrix matrix)
			{
				x1 = matrix[0][0];
				x1 = matrix[0][1];
				x1 = matrix[0][2];
				x1 = matrix[0][3];

				x1 = matrix[1][0];
				x1 = matrix[1][1];
				x1 = matrix[1][2];
				x1 = matrix[1][3];

				x1 = matrix[2][0];
				x1 = matrix[2][1];
				x1 = matrix[2][2];
				x1 = matrix[2][3];

				x1 = matrix[3][0];
				x1 = matrix[3][1];
				x1 = matrix[3][2];
				x1 = matrix[3][3];
			}*/
		};

		struct Keyframe
		{
			double time;
			std::vector<myMatrix> translateMatrix;
		};

		struct Joint
		{
			int mParentIndex;
			myMatrix mGlobalBindPoseInverse;
		};

		struct fbx_Joint
		{
			FbxNode *node;
			int parentIndex = -1;
		};

		struct clip
		{
			bool hasAnimation;
			double duration = 0.0f;
			std::vector<Keyframe> frame;
		};

		const int MAX_INFLUENCES = 4;

		struct Influence
		{
			int joint;
			float weight;
		};

		struct Node_Influence
		{
			std::vector<Influence> node;
		};

		std::vector<Node_Influence> control_point_influences;

		int num_control_points_in_mesh = 0;

		bool Node_Influence_Sort(Influence lhs, Influence rhs);

		FBXLIB_API int get_scene_poly_count(const char* fbx_file_path);

		FBXLIB_API HRESULT get_scene_content(const char* fbx_file_path, std::vector<MyVertex>* pOutVertexVector, std::vector<Joint> *pOutAnimationJoint, clip* animationClip);

		FBXLIB_API FbxManager* create_and_import(const char* fbx_file_path, FbxScene*& IScene);
	}
}
