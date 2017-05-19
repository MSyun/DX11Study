// グラフィックインターフェース
// 2017. 2.23	プログラム作成
// 2017. 3.26	機能の追加
// author		SyunMizuno

#pragma once

#include	"../../Convert/Convert.h"

/*
	Memo	:
		Graphics関連は適宜追加して継承すること
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
	//	// Zバッファを使用するか設定
	//	virtual void SetZEnable(bool flg);
	//	// Zバッファの設定を取得
	//	// true. 使用中 : false. 未使用
	//	virtual bool GetZEnable();
	//#pragma endregion
	//
	//#pragma region Wrap Mode
	//	// Wrapの設定
	//	virtual void SetWrapMode(_eWrapMode mode, _eWrapVec vec = WRAPVEC_UV);
	//	// Wrapの取得
	//	virtual _eWrapMode GetWrapMode(_eWrapVec vec);
	//#pragma endregion
	//
	//#pragma region Cull Mode
	//	// Cullingの設定
	//	virtual void SetCullMode(_eCullMode mode);
	//	// Cullingの取得
	//	virtual _eCullMode GetCullMode();
	//#pragma endregion
	};

};