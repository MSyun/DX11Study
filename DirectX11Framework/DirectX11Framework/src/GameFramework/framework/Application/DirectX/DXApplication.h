//////////////////////////////////////////////////////////////
// 2016. 2. 7	プログラム作成
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once

#include	"../Application.h"
#include	"../../DirectX/DXBase.h"


namespace MSLib {

	class	DXApplication : public	Application {
	protected:
		IDXBase*	m_pDXObj;	// DirectX用オブジェクト

	public:
		/* コンストラクタ
		// width	:	ウィンドウの横幅
		// height	:	ウィンドウの縦幅
		// bwnd		:	ウィンドウの確認
		*/
		DXApplication(
			int width = 600,
			int height = 480,
			bool bwnd = true);

		/* デストラクタ */
		virtual ~DXApplication();

		/* DirectXのオブジェクトを設定
		// _obj	:	DirectXオブジェクト
		*/
		void RegistDXObj(IDXBase* _obj) { m_pDXObj = _obj; }

		/* ローカル用ウィンドウプロシージャー
		// hWnd		:	ウィンドウハンドル
		// msg		:	メッセージ
		// wParam	:	パラメータ
		// lParam	:	パラメータ
		*/
		virtual LRESULT LocalWindowProc(
			HWND hWnd,
			UINT msg,
			WPARAM wParam,
			LPARAM lParam);

	protected:
		// ウインドウクラスの変更
		virtual void PreMainWnd();
		// アプリケーションの初期化
		virtual bool Initialize();
		// メッセージループ
		virtual void Loop();
		// アプリケーション終了処理
		virtual void ReleaseApp();
	};

};