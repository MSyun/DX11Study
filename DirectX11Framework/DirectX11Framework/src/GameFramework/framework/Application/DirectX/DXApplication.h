//////////////////////////////////////////////////////////////
// 2016. 2. 7	�v���O�����쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once

#include	"../Application.h"
#include	"../../DirectX/DXBase.h"


class	DXApplication : public	Application {
protected:
#pragma region variable

	IDXBase*	m_pDXObj;	// DirectX�p�I�u�W�F�N�g

#pragma endregion

public:
#pragma region method

	/* �R���X�g���N�^
	// width	:	�E�B���h�E�̉���
	// height	:	�E�B���h�E�̏c��
	// bwnd		:	�E�B���h�E�̊m�F
	*/
	DXApplication(
		int width = 600,
		int height = 480,
		bool bwnd = true);

	/* �f�X�g���N�^ */
	virtual ~DXApplication();

	/* DirectX�̃I�u�W�F�N�g��ݒ�
	// _obj	:	DirectX�I�u�W�F�N�g
	*/
	void RegistDXObj(IDXBase* _obj) { m_pDXObj = _obj; }

	/* ���[�J���p�E�B���h�E�v���V�[�W���[
	// hWnd		:	�E�B���h�E�n���h��
	// msg		:	���b�Z�[�W
	// wParam	:	�p�����[�^
	// lParam	:	�p�����[�^
	*/
	virtual LRESULT LocalWindowProc(
		HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);

#pragma endregion

protected:
#pragma region conceal method

	// �E�C���h�E�N���X�̕ύX
	virtual void PreMainWnd();
	// �A�v���P�[�V�����̏�����
	virtual bool Initialize();
	// ���b�Z�[�W���[�v
	virtual void Loop();
	// �A�v���P�[�V�����I������
	virtual void ReleaseApp();

#pragma endregion
};