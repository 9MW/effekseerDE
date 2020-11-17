Texture2D	g_texture		: register(t0);
#define Sp2D(name) SamplerState name##_sampler
#define g_colorSampler  g_colorTexture##_sampler
#define g_normalSampler  g_normalTexture##_sampler
#define g_sampler  g_texture##_sampler
#define g_backSampler  g_backTexture##_sampler
Sp2D(g_texture) : register(s0);

Texture2D		g_backTexture		: register(t1);
Sp2D(g_backTexture) 			: register(s1);

cbuffer PSConstantBuffer : register(b1)
{
float4		g_scale			: register(c0);
float4 mUVInversedBack		: register(c1);
};

struct PS_Input
{
	float4 Position		: SV_POSITION;
	linear centroid float2 UV		: TEXCOORD0;
	float4 Normal		: TEXCOORD1;
	float4 Binormal		: TEXCOORD2;
	float4 Tangent		: TEXCOORD3;
	float4 Pos		: TEXCOORD4;
	linear centroid float4 Color : COLOR0;
};

float4 PS( const PS_Input Input ) : SV_Target
{
	float4 Output = g_texture.Sample(g_sampler, Input.UV);
	Output.a = Output.a * Input.Color.a;

	if(Output.a <= 0.0f) discard;

	float2 pos = Input.Pos.xy / Input.Pos.w;
		float2 posU = Input.Tangent.xy / Input.Tangent.w;
		float2 posR = Input.Binormal.xy / Input.Binormal.w;

		float xscale = (Output.x * 2.0 - 1.0) * Input.Color.x * g_scale.x;
	float yscale = (Output.y * 2.0 - 1.0) * Input.Color.y * g_scale.x;

	float2 uv = pos + (posR - pos) * xscale + (posU - pos) * yscale;

		uv.x = (uv.x + 1.0) * 0.5;
	uv.y = 1.0 - (uv.y + 1.0) * 0.5;

	uv.y = mUVInversedBack.x + mUVInversedBack.y * uv.y;

	float3 color = g_backTexture.Sample(g_backSampler, uv);
		Output.xyz = color;

	if(Output.a <= 0.0f) discard;
	
	return Output;
}