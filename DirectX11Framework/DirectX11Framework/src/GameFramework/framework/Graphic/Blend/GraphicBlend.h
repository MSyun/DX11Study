// �O���t�B�b�N�̃u�����h
// 2017. 5.13	�v���O�����쐬
// author	:	SyunMizuno


#pragma once

#include	<d3d11.h>


typedef enum _Graphic_Blend {
	BLEND_NORMAL,	// �ʏ�
	BLEND_MULTI,	// ��Z
	BLEND_INV_MULTI,// ���]��Z
	BLEND_ADD,		// ���Z
	BLEND_SUB,		// ���Z
	BLEND_SCREEN,	// �X�N���[��
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