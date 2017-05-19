//	�V�X�e���n�֗̕�
// 2016.12. 29	�v���O�����쐬
// Author		SyunMizuno

#pragma once


#include	<Windows.h>

namespace MSLib {

#define	SAFE_DELETE(p)			{ if(p){delete p; p = nullptr;} }
#define	SAFE_DELETE_ARRAY(p)	{ if(p){delete [] p; p = nullptr;} }
#define	SAFE_RELEASE(p)			{ if(p){p->Release(); p = nullptr;} }

}