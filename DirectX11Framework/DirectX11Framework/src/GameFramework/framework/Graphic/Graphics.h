// �O���t�B�b�N
// 2017. 4.24	�v���O�����쐬
// author	:	SyunMizuno


#pragma once


#include	<D3DX11.h>
#include	"IGraphics/IGraphics.h"
#include	"../Singleton/Singleton.h"
#include	"Blend/GraphicBlend.h"



class Graphics	:	public	IGraphics,	public	Singleton<Graphics> {
private:
	static ID3D11DeviceContext*	m_pDeviceContext;
	static GraphicBlend m_Blend;

public:
	Graphics();
	virtual ~Graphics();

	static ID3D11DeviceContext* GetDevice();
	static void SetDevice(ID3D11DeviceContext* _dev);

	// �u�����h��ݒ�
	static void SetBlend(BlendType type);

	// ���߂�ݒ�
	static void SetAlphaEnable(const bool alpha);

//#pragma region Z Enable
//	// Z�o�b�t�@���g�p���邩�ݒ�
//	virtual void SetZEnable(bool flg);
//	// Z�o�b�t�@�̐ݒ���擾
//	// true. �g�p�� : false. ���g�p
//	virtual bool GetZEnable();
//#pragma endregion
//
//#pragma region Wrap Mode
//	// Wrap�̐ݒ�
//	virtual void SetWrapMode(_eWrapMode mode, _eWrapVec vec = WRAPVEC_UV);
//	// Wrap�̎擾
//	virtual _eWrapMode GetWrapMode(_eWrapVec vec);
//#pragma endregion
//
//#pragma region Cull Mode
//	// Culling�̐ݒ�
//	virtual void SetCullMode(_eCullMode mode);
//	// Culling�̎擾
//	virtual _eCullMode GetCullMode();
//#pragma endregion
//
//
//private:
//	// Wrap���琔���֕ύX
//	DWORD WrapModeToNum(_eWrapMode mode);
//	// ��������Wrap�֕ύX
//	_eWrapMode NumToWrapMode(DWORD num);
};


inline Graphics* GetGraphics() {
	return Graphics::Instance();
}