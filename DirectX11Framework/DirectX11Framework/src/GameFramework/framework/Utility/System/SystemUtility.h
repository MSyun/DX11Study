//	システム系の便利
// 2016.12. 29	プログラム作成
// Author		SyunMizuno

#pragma once


#include	<Windows.h>

namespace MSLib {

#define	SAFE_DELETE(p)			{ if(p){delete p; p = nullptr;} }
#define	SAFE_DELETE_ARRAY(p)	{ if(p){delete [] p; p = nullptr;} }
#define	SAFE_RELEASE(p)			{ if(p){p->Release(); p = nullptr;} }

}