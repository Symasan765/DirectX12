struct vs_in
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct vs_out
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

Texture2D g_AlbedoTex : register(t0);
SamplerState g_samLinear : register(s0);

vs_out  VSMain(vs_in vIn)
{
	vs_out vOut;
	vOut.position = vIn.position;
	vOut.uv = vIn.uv;
    return vOut;
}

float4 PSMain(vs_out vsOut) : SV_TARGET
{
    return g_AlbedoTex.Sample(g_samLinear, (float2) (vsOut.uv));
}