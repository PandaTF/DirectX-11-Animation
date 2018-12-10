Texture2D ObjTexture : register(t0);
Texture2D BumpMappingTexture : register(t1);
Texture2D SpecularTexture : register(t2);
SamplerState ObjSamplerState : register(s0);
SamplerState ObjSamplerState_Mirror : register(s1);

#define NUM_JOINTS 28

cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
	
    float4 mapControl;

    float4 ambient;
    float4 vLightDir[2];
    float4 vLightColor[2];
    float4 vOutputColor;

    float4 vPointLight_Color;
    float4 vPointLight_Position;
    float3 vPointLight_Attenuation;
    float vPointLight_Range;
	
    float4 cameraPosition;

    float4 specularColor;
    float specularPower;
    float3 padding1;
}

struct VS_INPUT
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float3 Norm : NORMAL;
    float2 TexCoord : TEXCOORD;

    float4 VertexColor : VERTEXCOLOR;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float3 Norm : NORMAL;
    float2 TexCoord : TEXCOORD;
	
    float4 VertexColor : VERTEXCOLOR;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;

    float3 lightPos : TEXCOORD1;

    float3 viewDirection : TEXCOORD2;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    output.Pos = input.Pos;

    output.Pos = mul(output.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

    output.Color = input.Color;

    output.Norm = normalize(mul(input.Norm, (float3x3) World));
    output.TexCoord = input.TexCoord;

    output.VertexColor = input.VertexColor;

    output.Tangent = mul(input.Tangent, (float3x3) World);
    output.Tangent = normalize(output.Tangent);
    output.Binormal = mul(input.Binormal, (float3x3) World);
    output.Binormal = normalize(output.Binormal);

    output.lightPos = mul(input.Pos, World);

    float4 worldPosition;
    worldPosition = mul(input.Pos, World);
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
    output.viewDirection = normalize(output.viewDirection);

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

    float3 finalColor = float3(0.0f, 0.0f, 0.0f);
    float3 finalAmbient = diffuse * ambient;

    float3 lightToPixelVec = vPointLight_Position.xyz - input.lightPos;

    float d = length(lightToPixelVec);

	// Calculate diffuse light color
	//Bump / Normal
    if (mapControl.x == 1.0f)
    {
        float4 normalMap = BumpMappingTexture.Sample(ObjSamplerState, input.TexCoord);
        normalMap = (normalMap * 2.0f) - 1.0f;

        input.Norm = (normalMap.x * input.Tangent) + (normalMap.y * input.Binormal) + (normalMap.z * input.Norm);

        input.Norm = normalize(input.Norm);

        //input.Tangent = normalize(input.Tangent - dot(input.Tangent, input.Norm) * input.Norm);
		//
        //float3 biTangent = cross(input.Norm, input.Tangent);
		//
        //float3x3 texSpace = float3x3(input.Tangent, biTangent, input.Norm);
		//
        //input.Norm = normalize(mul(normalMap, texSpace));
    }

    float3 lightColor = float3(0.0f, 0.0f, 0.0f);
    float lightIntensity[2];
    for (int i = 0; i < 2; i++)
    {
        float3 tempLightColor = float3(0.0f, 0.0f, 0.0f);
        tempLightColor = saturate(dot((float3) (vLightDir[i]), input.Norm) * vLightColor[i] * diffuse);
        lightIntensity[i] = saturate(dot(input.Norm, vLightDir[i].xyz));
        lightColor += tempLightColor;
    }
    
    finalAmbient = saturate(finalAmbient + lightColor);

	//Specular
    if (mapControl.y == 1.0f)
    {
        float4 specularIntensity = SpecularTexture.Sample(ObjSamplerState, input.TexCoord);

        float3 reflection[2];
        float4 specular[2];

        for (int i = 0; i < 2; i++)
        {
            reflection[i] = normalize(2 * lightIntensity[i] * input.Norm - (-1 * vLightDir[i].xyz));

            specular[i] = pow(saturate(dot(reflection[i], input.viewDirection)), specularPower);

            specular[i] = specular[i] * specularIntensity;

            finalAmbient += specular[i].xyz;
        }

        finalAmbient = saturate(finalAmbient);
    }

    if (d > vPointLight_Range)
		return float4(finalAmbient, diffuse.a);

    lightToPixelVec /= d;
	
    float howMuchLight = dot(lightToPixelVec, input.Norm);
	
	// Calculate point light color
    if (howMuchLight > 0.0f)
    {
        finalColor += howMuchLight * diffuse * vPointLight_Color;
	
        finalColor /= vPointLight_Attenuation[0] + (vPointLight_Attenuation[1] * d) + (vPointLight_Attenuation[2] * (d * d));
    }
	
    finalColor = saturate(finalColor + finalAmbient);
	
    return float4(finalColor, diffuse.a);

}


//--------------------------------------------------------------------------------------
// PSSolid - render a solid color
//--------------------------------------------------------------------------------------
float4 PSSolid(PS_INPUT input) : SV_Target
{
    if (mapControl.z == 0)
        return vOutputColor;

	return input.Color;
}

//--------------------------------------------------------------------------------------
// PSFont - render font
//--------------------------------------------------------------------------------------
float4 PSFont(PS_INPUT input) : SV_TARGET
{
    return ObjTexture.Sample(ObjSamplerState, input.TexCoord);
}