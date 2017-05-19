// Windows用SceneManagerクラス
// 2015.12.15	プログラム作成
// 2016.01.26	vectorからmapへ変更
// 2016.01.28	読み込み率追加
// 改変者		SyunMizuno

#pragma once

#include	"../Base/SceneBase.h"
#include	"../Manager/SceneManager.h"
#include	<Windows.h>
#include	<process.h>


namespace MSLib {

	class SceneManagerWin : public	SceneManagerBase {
	protected:
		SceneBase*		m_Loading;		// ロードシーン
		int				m_nLoadingFlag;	// ロードフラグ。
		HANDLE			m_hThread;		// スレッドハンドル
		bool			m_bLoadSuc;		// ロードの成功
		unsigned int	m_uLoadWaitTime;// ロード中スレッドを開始するまでのウェイト
		unsigned char	m_uLoadRate;	// 読み込み率
		bool			m_bLoadKey;		// 読み込み終了確認
		bool			m_bLoadEndAfter;// 読み込み後のシーン遷移確認

	public:
		SceneManagerWin();
		~SceneManagerWin();
		void Release(void);

		void SetLoadingFlag(int flag) { m_nLoadingFlag = flag; }
		void SetLoadSuc(bool Success) { m_bLoadSuc = Success; }
		void SetLoadWait(unsigned int time) { m_uLoadWaitTime = time; }
		void SetLoadRate(unsigned char _rate) { m_uLoadRate = _rate; }
		unsigned char GetLoadRate(void) { return m_uLoadRate; }
		// 読み込み終了確認（true. 読み込み成功 : false. 読み込み中
		bool CheckLoadingEnd() { return !m_bLoadKey; }
		// 読み込み終了
		void LoadingEnd() { m_bLoadEndAfter = true; }

		// シーンの追加
		bool RegistLoadingScene(SceneBase* pScene);
		template<typename T> bool RegistLoadingSceneMakeInstance(void) { T *data = new T; return RegistLoadingScene(data); }
		void DeleteLoadingScene(void);

		SceneBase* GetScene(void);

	protected:
		bool ChangeLoadScene(SceneBase* pScene);
		void PopLoadScene(void);
		bool PushLoadScene(SceneBase* pScene);
	};

	class SceneManagerWins : public	SceneManagerWin, public	Singleton<SceneManagerWins> {};

	// これで使用しやすくなる
	inline SceneManagerWins* GetSceneManagerWins(void) {
		return SceneManagerWins::Instance();
	}

}