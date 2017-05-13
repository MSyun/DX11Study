// グローバル

#include	"../Header/Material.hlslh"

Texture2D g_texDecal	: register(t0);
SamplerState g_samLinear	: register(s0);

cbuffer global {
	matrix m_mWorld;
	matrix m_mWVP;
	float4 m_vLightDir;
	float4 m_Diffuse = float4(1,0,0,0);
	float4 m_vEye;
};

struct VS_OUTPUT {
	float4 Pos			: SV_POSITION;
	float3 Light		: TEXCOORD0;
	float3 Normal		: TEXCOORD1;
	float3 EyeVector	: TEXCOORD2;
	float2 Tex			: TEXCOORD3;
};

// バーテックスシェーダ
VS_OUTPUT VS(
	float4 Pos		: POSITION,
	float4 Normal	: NORMAL,
	float2 Tex		: TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, m_mWVP);
	output.Normal = mul(Normal.xyz, (float3x3)m_mWorld);
	output.Light = m_vLightDir.xyz;

	float3 PosWorld = mul(Pos, m_mWorld).xyz;
	output.EyeVector = m_vEye.xyz - PosWorld;
	output.Tex = Tex;

	return output;
}

// ピクセルシェーダ
float4 PS(VS_OUTPUT input) : SV_Target{
	float3 Normal = normalize(input.Normal);
	float3 LightDir = normalize(input.Light);
	float3 ViewDir = normalize(input.EyeVector);
	float4 NL = saturate(dot(Normal, LightDir));

	float3 Reflect = normalize(2 * NL.xyz * Normal - LightDir);
	float4 specular = 2 * pow(saturate(dot(Reflect, ViewDir)), 2);

	float4 color = g_texDecal.Sample(g_samLinear, input.Tex);
	color = color + color * specular;

	return color;
}