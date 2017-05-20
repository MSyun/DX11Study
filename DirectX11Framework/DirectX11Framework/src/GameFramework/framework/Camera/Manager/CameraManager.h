// カメラマネージャー
// 2017.05.15	: プログラム作成
// author		: SyunMizuno

#pragma once


#include	<vector>
#include	<string>
#include	"../Camera.h"
#include	"../../Singleton/Singleton.h"


namespace MSLib {

	class CameraManager : public	Singleton<CameraManager> {
	protected:
		std::vector<Camera*>	m_aCamera;

		std::string m_CurCameraName;

	public:
		CameraManager();
		virtual ~CameraManager();

		/* 追加
		// camera	: 追加したいカメラ
		*/
		void Add(Camera* camera);

		/* 削除
		// camera	:	削除するカメラ
		// return	:	true. 成功、false. 失敗
		*/
		bool Delete(Camera* camera);

		/* 取得
		// Name	:	取得するカメラの名前
		// return	:	対応したカメラのインスタンス
		*/
		Camera* Get(const std::string& Name);

		/* セット
		// Name	:	設定するカメラの名前
		// return	:	true. 成功、false. 失敗
		*/
		bool Set(const std::string& Name);

		/* 最後に使用したものを取得
		// return	:	対応したカメラのインスタンス
		*/
		Camera* CurrentCamera();
	};

	CameraManager* GetCameraManager();

};