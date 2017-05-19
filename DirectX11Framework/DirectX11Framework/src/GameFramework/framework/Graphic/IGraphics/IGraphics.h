// �O���t�B�b�N�C���^�[�t�F�[�X
// 2017. 2.23	�v���O�����쐬
// 2017. 3.26	�@�\�̒ǉ�
// author		SyunMizuno

#pragma once

#include	"../../Convert/Convert.h"

/*
	Memo	:
		Graphics�֘A�͓K�X�ǉ����Čp�����邱��
*/


namespace MSLib {

	typedef enum {
		WRAPMODE_WRAP = 0,
		WRAPMODE_CLAMP,
	} _eWrapMode;

	typedef enum {
		WRAPVEC_U = 0,
		WRAPVEC_V,
		WRAPVEC_UV,
	} _eWrapVec;

	typedef enum {
		CULLMODE_NONE = 0,
		CULLMODE_FRONT,
		CULLMODE_BACK,
	} _eCullMode;


	__interface IGraphics {
public:
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
	};

};