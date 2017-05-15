// カメラマネージャー
// 2017.05.15	: プログラム作成
// author		: SyunMizuno


#pragma once


#include	<map>
#include	<string>
#include	"../Camera.h"
#include	"../../Singleton/Singleton.h"


class CameraManager	:	public	Singleton<CameraManager> {
protected:
	map<string, Camera*>	m_MapCamera;
	bool	m_bHelper;

	string m_CurCameraName;

public:
	CameraManager();
	virtual ~CameraManager();

	/* 作成
	// Name	:	生成するカメラの名前
	// return	: 生成したカメラのオブジェクト
	*/
	Camera* Create(const string Name);

	/* 削除
	// Name	:	削除するカメラの名前
	// return	:	true. 成功、false. 失敗
	*/
	bool Delete(const string Name);

	/* 取得
	// Name	:	取得するカメラの名前
	// return	:	対応したカメラのインスタンス
	*/
	Camera* Get(const string Name);

	/* セット
	// Name	:	設定するカメラの名前
	// return	:	true. 成功、false. 失敗
	*/
	bool Set(const string Name);

	/* 最後に使用したものを取得
	// return	:	対応したカメラのインスタンス
	*/
	Camera* CurrentCamera();

	/* 管理オブジェクトを自動で削除するか設定 */
	void SetHelper(bool helper);
};

CameraManager* GetCameraManager();