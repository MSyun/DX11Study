//////////////////////////////////////////////////////////////
// 2016. 2. 7	プログラム作成
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once


#include	<Windows.h>
#include	"../Application/Application.h"


namespace MSLib {

	/*							//
	//		DirectX用ベース		//
	//							*/
	class	IDXBase {
	protected:
		Application*	m_pApp;

	public:
		explicit IDXBase(Application* app) : m_pApp(app) {}
		virtual ~IDXBase() {};

		// 初期化
		virtual HRESULT Init() { return S_OK; };

		// ステップ関数
		virtual HRESULT Step() = 0;

		// 終了処理
		virtual HRESULT Release() { return S_OK; }

		virtual HRESULT ChangeWindowSize() { return S_OK; }	// サイズの変更
		virtual void ChangeDisplayMode() {}	// モードの変更

	protected:
		virtual HRESULT InvalidateDeviceObjects() { return S_OK; };	// OnLostDevice
		virtual HRESULT RestoreDeviceObjects() { return S_OK; };	// OnResetDevice
	};

};