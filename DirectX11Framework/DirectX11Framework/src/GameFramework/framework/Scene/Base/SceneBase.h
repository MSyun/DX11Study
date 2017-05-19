///////////////////////////////////////////////////////////////
// シーンベースクラス
// author		SyunMizuno
// 2015.12.05	プログラム作成
// 2016. 1. 3	ちょっち改変
///////////////////////////////////////////////////////////////

#pragma once

/*
	memo	:
		シーンはこのクラスを継承すること
		コンストラクタ、デストラクタでInit,Releaseを呼び出さないこと
*/

namespace MSLib {

	class SceneBase {
	private:
		bool m_bMakeFlg;	// Initが呼び出されたか

	protected:
		// リソース系はここ
		virtual bool Init() = 0;
		virtual void Release() = 0;

	public:
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual bool ReStart() { return true; }

		virtual bool InitMain() { m_bMakeFlg = true;	if (!Init()) { return false; } return true; }
		virtual void ReleaseMain() { m_bMakeFlg = false;	Release(); }

		SceneBase() { m_bMakeFlg = false; }
		virtual ~SceneBase() {}
		bool GetMakeFlg(void) { return m_bMakeFlg; }	// SceneManagerクラスで使用
	};

}