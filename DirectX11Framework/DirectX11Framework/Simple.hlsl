// グローバル
cbuffer global {
	matrix g_mWVP;
	float4 g_PolyColor;
};

// バーテックスシェーダ
float4 VS(float4 Pos : POSITION) : SV_POSITION{
	Pos = mul(Pos, g_mWVP);

	return Pos;
}

// ピクセルシェーダ
float4 PS(float4 Pos : SV_POSITION) : SV_Target{
	return g_PolyColor;
}