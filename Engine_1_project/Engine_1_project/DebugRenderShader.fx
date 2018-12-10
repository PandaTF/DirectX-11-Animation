#define NUM_JOINTS 28

cbuffer ConstantBuffer
{
    matrix World;
    matrix View;
    matrix Projection;
	
    matrix translateMatrix[NUM_JOINTS];
    float hasAnimation;
    float3 padding;
}

struct VS_INPUT
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float4 jointIndex : JOINTINDEX;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    output.Pos = input.Pos;
    if (hasAnimation)
    {
		output.Pos = mul(output.Pos, translateMatrix[input.jointIndex.x]);
    }

    output.Pos = mul(output.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

    output.Color = input.Color;

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    return input.Color;

}