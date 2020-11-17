
Texture2D	g_texture		: register( t0 );
#define Sp2D(name) SamplerState name##_sampler
#define g_colorSampler  g_colorTexture##_sampler
#define g_normalSampler  g_normalTexture##_sampler
#define g_sampler  g_texture##_sampler
Sp2D	(g_texture)		: register( s0 );


struct PS_Input
{
	float4 Pos		: SV_POSITION;
	linear centroid float4 Color		: COLOR;
	linear centroid float2 UV		: TEXCOORD0;
};


float4 PS( const PS_Input Input ) : SV_Target
{
	float4 Output = Input.Color * g_texture	.Sample(g_sampler, Input.UV);

	//if(Output.a <= 0.0f) discard;

	return Output;
}



#define MOD fmod
#define FRAC frac
#define LERP lerp


#define C_LINEAR linear
#define C_CENTROID centroid


struct VS_Input
{
	float3 Pos		: ATTRIB0;
	float4 Color		: ATTRIB1;
	float4 Normal		: ATTRIB2;
	float4 Tangent		: ATTRIB3;
	float2 UV1		: ATTRIB4;
	float2 UV2		: ATTRIB5;
	float4 CustomData1 : ATTRIB6;
	//$C_IN2$
};

struct VS_Output
{
	float4 Position		: SV_POSITION;
	C_LINEAR C_CENTROID float4 VColor		: COLOR;
	C_LINEAR C_CENTROID float2 UV1		: TEXCOORD0;
	C_LINEAR C_CENTROID float2 UV2		: TEXCOORD1;
	float3 WorldP	: TEXCOORD2;
	float3 WorldN : TEXCOORD3;
	float3 WorldT : TEXCOORD4;
	float3 WorldB : TEXCOORD5;
	float2 ScreenUV : TEXCOORD6;
	float4 CustomData1 : TEXCOORD7;
	//$C_OUT2$
};

cbuffer VSConstantBuffer : register(b0) {

float4x4 mCamera		: register(c0);
float4x4 mProj			: register(c4);
float4 mUVInversed		: register(c8);
float4 predefined_uniform : register(c9);
float4 cameraPosition : register(c10);

float4 efk_uniform_323 : register(c11);
float4 efk_uniform_497 : register(c12);
float4 efk_uniform_676 : register(c13);
float4 efk_uniform_1184 : register(c14);
float4 efk_uniform_1501 : register(c15);
float4 efk_uniform_1504 : register(c16);
float4 efk_uniform_1507 : register(c17);
};
Texture2D efk_texture_266_texture : register(t0);
SamplerState efk_texture_266_texture_sampler : register(s0);
Texture2D efk_texture_276_texture : register(t1);
SamplerState efk_texture_276_texture_sampler : register(s1);
Texture2D efk_texture_289_texture : register(t2);
SamplerState efk_texture_289_texture_sampler : register(s2);
Texture2D background_texture : register(t3);
SamplerState background_texture_sampler : register(s3);


float2 GetUV(float2 uv)
{
	uv.y = mUVInversed.x + mUVInversed.y * uv.y;
	return uv;
}

float2 GetUVBack(float2 uv)
{
	uv.y = mUVInversed.z + mUVInversed.w * uv.y;
	return uv;
}



VS_Output main( const VS_Input Input )
{
	VS_Output Output = (VS_Output)0;
	float3 worldPos = Input.Pos;
	float3 worldNormal = (Input.Normal - float3(0.5, 0.5, 0.5)) * 2.0;
	float3 worldTangent = (Input.Tangent - float3(0.5, 0.5, 0.5)) * 2.0;
	float3 worldBinormal = cross(worldNormal, worldTangent);
	float3 objectScale = float3(1.0, 1.0, 1.0);

	// UV
	float2 uv1 = Input.UV1;
	float2 uv2 = Input.UV2;
	//uv1.y = mUVInversed.x + mUVInversed.y * uv1.y;
	//uv2.y = mUVInversed.x + mUVInversed.y * uv2.y;

	// NBT
	Output.WorldN = worldNormal;
	Output.WorldB = worldBinormal;
	Output.WorldT = worldTangent;

	float3 pixelNormalDir = worldNormal;
	float4 vcolor = Input.Color;
float4 customData1 = Input.CustomData1;
Output.CustomData1 = customData1.xyzw;


float2 val0=efk_uniform_1507.xy;
float4 val1_CompMask=float4(val0.x,val0.y, 0.0, 1.0);
float val1=val1_CompMask.x;
float2 val2=uv1;
float4 val4 = efk_texture_276_texture.SampleLevel(efk_texture_276_texture_sampler,GetUV(val2),0);
float val5=efk_uniform_323.x;
float val6=predefined_uniform.x;
float val7=efk_uniform_497.x;
float val8=0.0;
float2 val9=float2(val8,val7);
float2 val10=(val9*float2(val6,val6));
float2 val11=efk_uniform_1501.xy;
float2 val12=(val11*val2);
float2 val13=(val12+val10);
float4 val15 = efk_texture_289_texture.SampleLevel(efk_texture_289_texture_sampler,GetUV(val13),0);
float4 val16=(val15*float4(val5,val5,val5,val5));
float4 val17_CompMask=val16;
float2 val17=val17_CompMask.xy;
float2 val18=efk_uniform_1504.xy;
float2 val19=(val18*val2);
float val20=efk_uniform_676.x;
float val21=0.0;
float2 val22=float2(val21,val20);
float2 val23=(val22*float2(val6,val6));
float2 val24=(val23+val19);
float2 val25=(val24+val17);
float4 val27 = efk_texture_266_texture.SampleLevel(efk_texture_266_texture_sampler,GetUV(val25),0);
float4 val28=(val27*val4);
float4 val29=(val28+val4);
float4 val30=customData1.xyzw;
float4 val31_CompMask=val30;
float val31=val31_CompMask.w;
float4 val32=(float4(val31,val31,val31,val31)*val29);
float4 val33=(val32-float4(val1,val1,val1,val1));
float val34=efk_uniform_1184.x;
float4 val35_CompMask=float4(val0.x,val0.y, 0.0, 1.0);
float val35=val35_CompMask.y;
float4 val36=(val32-float4(val35,val35,val35,val35));
float4 val37=ceil(val36);
float4 val38=(val30*val37);
float4 val39=(val38*float4(val34,val34,val34,val34));
float4 val40=(val39+val30);
float3 normalDir = float3(0.5,0.5,1.0);
float3 tempNormalDir = ((normalDir -float3 (0.5, 0.5, 0.5)) * 2.0);
pixelNormalDir = tempNormalDir.x * worldTangent + tempNormalDir.y * worldBinormal + tempNormalDir.z * worldNormal;
float3 worldPositionOffset = float3(0.0,0.0,0.0);
float3 baseColor = float3(0.0,0.0,0.0);
float3 emissive = float3(val40.x,val40.y,val40.z);
float metallic = float(0.5);
float roughness = float(0.5);
float ambientOcclusion = float(1.0);
float opacity = float(1.0);
float opacityMask = val33.x;
float refraction = float(0.0);




	worldPos = worldPos + worldPositionOffset;

	float4 cameraPos = mul(mCamera, float4(worldPos, 1.0));
	cameraPos = cameraPos / cameraPos.w;
	Output.Position = mul(mProj, cameraPos);

	Output.WorldP = worldPos;
	Output.VColor = Input.Color;
	Output.UV1 = uv1;
	Output.UV2 = uv2;
	Output.ScreenUV = Output.Position.xy / Output.Position.w;
	Output.ScreenUV.xy = float2(Output.ScreenUV.x + 1.0, 1.0 - Output.ScreenUV.y) * 0.5;

	return Output;
}

