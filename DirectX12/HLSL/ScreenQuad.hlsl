struct vs_in
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD;
};

struct vs_out
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

Texture2D g_AlbedoTex : register(t0);
SamplerState g_samLinear : register(s0);

vs_out  VSMAIN(vs_in vIn)
{
	vs_out vOut;
	vOut.position = vIn.position;
	vOut.texcoord = vIn.texcoord;
	return vIn;
}

float4 PSMAIN(vs_out vIn)
{
    return g_AlbedoTex.Sample(g_samLinear, (float2) (vsOut.uv));
}