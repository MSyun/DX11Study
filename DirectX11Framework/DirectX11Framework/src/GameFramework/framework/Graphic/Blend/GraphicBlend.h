// グラフィックのブレンド
// 2017. 5.13	プログラム作成
// author	:	SyunMizuno


#pragma once

#include	<d3d11.h>


typedef enum _Graphic_Blend {
	BLEND_NORMAL,	// 通常
	BLEND_MULTI,	// 乗算
	BLEND_INV_MULTI,// 反転乗算
	BLEND_ADD,		// 加算
	BLEND_SUB,		// 減算
	BLEND_SCREEN,	// スクリーン
} BlendType;


class GraphicBlend {
private:
	static bool m_bAlpha;
	static BlendType m_Blend;

public:
	static void Set(
		BlendType type,
		ID3D11Device* device,
		ID3D11DeviceContext* context);

	static void SetAlphaEnable(
		bool alpha,
		ID3D11Device* device,
		ID3D11DeviceContext* context);

private:
	static void NormalSetting(D3D11_BLEND_DESC* pDesc);
	static void MultiSetting(D3D11_BLEND_DESC* pDesc);
	static void InverseMultiSetting(D3D11_BLEND_DESC* pDesc);
	static void AddSetting(D3D11_BLEND_DESC* pDesc);
	static void SubSetting(D3D11_BLEND_DESC* pDesc);
	static void ScreenSetting(D3D11_BLEND_DESC* pDesc);
};