
struct VSIn
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
	float3 tangent : TANGENT;
	int4 bindex : BONEINDEX;
	float4 bweight : WEIGHT;
	float4x4 WorldMat  : MATRIX;    // ワールド変換行列
  uint InstID : SV_InstanceID; // インスタンスID
};

struct VSOut
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
	float4 worldPos : POSITION;
};

Texture2D g_AlbedoTex : register(t0);
SamplerState g_samLinear : register(s0);

cbuffer Scene  : register(b0)
{
	float4x4 worldViewProjMatrix;
	float4x4 worldViewMatrix;
};


VSOut VSMain(VSIn vsIn)
{
	VSOut output;
	
	float4 pos = 1.0f;
	float4 normal = 0.0f;
	pos.xyz = vsIn.pos;
	normal.xyz = vsIn.normal;

	output.pos = mul(pos, (vsIn.WorldMat));	
	output.pos = mul(output.pos, (worldViewProjMatrix));
	
	output.normal = mul(vsIn.normal.xyz, ((float3x3)(vsIn.WorldMat)));
	output.uv = vsIn.uv;
	output.worldPos = mul(pos, vsIn.WorldMat);
	output.worldPos = output.worldPos;
	return output;
}

float4 PSMain(VSOut vsOut) : SV_TARGET
{
	float4 albedoMap = g_AlbedoTex.Sample(g_samLinear, (float2)(vsOut.uv));
	return albedoMap;
}