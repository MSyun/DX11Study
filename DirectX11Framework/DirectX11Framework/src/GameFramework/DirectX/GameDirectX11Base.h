// ゲーム用DirectX11
// 2016. 5. 9	:	プログラム作成
// author		:	SyunMizuno


#pragma once



#include	"../framework/DirectX/DX11Base.h"
#include	"../framework/Scene/ManagerWin/SceneManagerWin.h"
#include	"../framework/Resource/Manager/ResourceManager.h"
#include	"../framework/Resource/Texture/Texture.h"
#include	"../framework/Resource/Mesh/Mesh.h"
#include	"../framework/Resource/Shader/Base/Shader.h"
#include	"../framework/Time/Time.h"
#include	"../framework/Camera/Manager/CameraManager.h"
#include	"../framework/Object/3DObject/Manager/Object3DManager.h"
#include	"../framework/Archives/Archives.h"
#include	"../framework/Light/Manager/LightManager.h"
#include	"../framework/Sound/SoundManager.h"



namespace MSLib {

	class GameDirectX11Base : public	DX11Base {
	protected:
		Time						m_time;
		SceneBase*					m_pCurScene;
		SceneManagerWin*			m_pSceneManager;
		ResourceManager<Texture>*	m_pTexManager;
		ResourceManager<Mesh>*		m_pMeshManager;
		ResourceManager<Shader>*	m_pShaderManager;
		CameraManager*				m_pCameraManager;
		Object3DManager*			m_pObject3DManager;
		Archives					m_Archives;
		LightManager*				m_pLightManager;
		Sound::SoundManager*		m_pSoundManager;

	public:
		explicit GameDirectX11Base(Application* app);
		virtual ~GameDirectX11Base();

		/* 初期化
		// return	: S_OK. 成功、E_FAIL. 失敗
		*/
		virtual HRESULT Init() override;

		/* ステップ関数
		// return	: S_OK. 成功、E_FAIL. 失敗
		*/
		virtual HRESULT Step() override;

		/* 終了処理
		// return	: S_OK. 成功、E_FAIL. 失敗
		*/
		virtual HRESULT Release() override;

	private:
		HRESULT InvalidateDeviceObjects() final;
		virtual HRESULT InvalidateDeviceObjectsGame() { return S_OK; }
		HRESULT RestoreDeviceObjects() final;
		virtual HRESULT RestoreDeviceObjectsGame() { return S_OK; }
		virtual HRESULT InitGame() { return S_OK; }
		virtual HRESULT InitApp() final;
		virtual HRESULT ReleaseGame() { return S_OK; }
		virtual HRESULT ReleaseApp() final;
		virtual void Update() override;
		virtual void Draw() override;
	};

};