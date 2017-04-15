//////////////////////////////////////////////////////////////
// 2016. 2. 7	�v���O�����쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once


#include	<Windows.h>
#include	"../Application/Application.h"


/*							//
//		DirectX�p�x�[�X		//
//							*/
class	IDXBase {
protected:
	Application*	m_pApp;

public:
	IDXBase(Application* app) : m_pApp(app) {}
	virtual ~IDXBase() {};

	// ������
	virtual HRESULT Init() { return S_OK; };

	// �X�e�b�v�֐�
	virtual HRESULT Step() = 0;

	// �I������
	virtual HRESULT Release() { return S_OK; }

	virtual HRESULT ChangeWindowSize() { return S_OK; }	// �T�C�Y�̕ύX
	virtual void ChangeDisplayMode() {}	// ���[�h�̕ύX

	// �O���t�B�b�N
	virtual void GraphicAdd() {}
	virtual void GraphicAlpha() {}
	virtual void GraphicSub() {}

protected:
	virtual HRESULT InvalidateDeviceObjects() { return S_OK; };	// OnLostDevice
	virtual HRESULT RestoreDeviceObjects() { return S_OK; };	// OnResetDevice
};