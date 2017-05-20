// �Q�[���pDirectX11
// 2016. 5. 9	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"GameDirectX11Base.h"
#include	"../framework/Input/Input.h"
#include	"../DelayFunction/Collection/DelayFunctionCollection.h"
#include	"../framework/Graphic/Graphics.h"



namespace MSLib {

	/*									//
	//			�R���X�g���N�^			//
	//									*/
	GameDirectX11Base::GameDirectX11Base(Application* app) :
		DX11Base(app),
		m_pCurScene(nullptr),
		m_pSceneManager(nullptr),
		m_pTexManager(nullptr),
		m_pMeshManager(nullptr),
		m_pShaderManager(nullptr),
		m_pCameraManager(nullptr),
		m_pObject3DManager(nullptr),
		m_pLightManager(nullptr),
		m_pSoundManager(nullptr)
	{
	}


	/*									//
	//			�f�X�g���N�^			//
	//									*/
	GameDirectX11Base::~GameDirectX11Base() {
		Release();
	}


	/*									//
	//				�X�e�b�v			//
	//									*/
	HRESULT GameDirectX11Base::Step() {
		Time::Update();
		Input::Update();
		Update();
		Draw();

		return S_OK;
	}


	/*									//
	//				���				//
	//									*/
	HRESULT GameDirectX11Base::Release() {
		if (FAILED(ReleaseGame())) {
			Debug::LogError("�Q�[���̉�������Ɏ��s���܂���");
			return E_FAIL;
		}

		if (FAILED(DX11Base::Release())) {
			Debug::LogError("�Q�[���̉�������Ɏ��s���܂���");
			return E_FAIL;
		}

		return S_OK;
	}


	/*									//
	//			�A�v���̉��			//
	//									*/
	HRESULT GameDirectX11Base::ReleaseApp() {
		SAFE_DELETE(m_pSoundManager);
		SAFE_DELETE(m_pShaderManager);
		SAFE_DELETE(m_pMeshManager);
		SAFE_DELETE(m_pTexManager);
		SAFE_DELETE(m_pSceneManager);

		SAFE_DELETE(m_pObject3DManager);
		SAFE_DELETE(m_pCameraManager);
		SAFE_DELETE(m_pLightManager);


		return S_OK;
	}


	/*									//
	//				������				//
	//									*/
	HRESULT GameDirectX11Base::Init() {
		if (FAILED(DX11Base::Init())) {
			Debug::LogError("�Q�[���̏����������Ɏ��s���܂���");
			return E_FAIL;
		}

		if (FAILED(InitGame())) {
			Debug::LogError("�Q�[���̏����������Ɏ��s���܂���");
			return E_FAIL;
		}

		return S_OK;
	}


	/*									//
	//			�A�v���̏�����			//
	//									*/
	HRESULT GameDirectX11Base::InitApp() {
		Input::Init(m_pApp->GetHWND());

		m_pObject3DManager = new Object3DManager;
		m_pSceneManager = new SceneManagerWins;
		m_pTexManager = new ResourceManager<Texture>;
		m_pMeshManager = new ResourceManager<Mesh>;
		m_pShaderManager = new ResourceManager<Shader>;
		m_pCameraManager = new CameraManager;
		m_pLightManager = new LightManager;
		m_pSoundManager = new Sound::SoundManager;
		m_pSoundManager->Init(m_pApp->GetHWND());
		m_Archives.ShaderCreate<ArchivesCollection::ArchivesShaderBase>();
		m_Archives.MeshCreate<ArchivesCollection::ArchivesMeshBase>();
		m_Archives.TexCreate<ArchivesCollection::ArchivesTextureBase>();
		m_Archives.SoundCreate<ArchivesCollection::ArchivesSoundBase>();
		m_Archives.TagCreate<ArchivesCollection::ArchivesTagBase>();

		Debug::Log("�t���[�����[�g : " + to_string(Time::GetSettingFrameRate()));

		return S_OK;
	}


	/*									//
	//				�X�V				//
	//									*/
	void GameDirectX11Base::Update() {
		m_pCurScene = m_pSceneManager->GetScene();
		if (m_pCurScene)
			m_pCurScene->Update();
		DelayFunctionCollection::Update();
	}


	/*									//
	//				�`��				//
	//									*/
	void GameDirectX11Base::Draw() {
		float ClearColor[4] = { 0, 0, 1, 1 };
		ID3D11DeviceContext* context = Graphics::GetDevice();

		context->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		context->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		if (m_pCurScene)
			m_pCurScene->Draw();
		m_pSceneManager->Draw();

		m_pSwapChain->Present(0, 0);
	}


	/*									//
	//			OnLostDevice			//
	//									*/
	HRESULT GameDirectX11Base::InvalidateDeviceObjects() {
		HRESULT hr = S_OK;

		hr = Debug::InvalidateDeviceObjects();
		if (FAILED(hr))	return hr;

		hr = InvalidateDeviceObjectsGame();
		if (FAILED(hr))	return hr;

		return S_OK;
	}


	/*									//
	//			OnResetDevice			//
	//									*/
	HRESULT GameDirectX11Base::RestoreDeviceObjects() {
		HRESULT hr = S_OK;

		hr = Debug::RestoreDeviceObjects();
		if (FAILED(hr))	return hr;

		hr = RestoreDeviceObjectsGame();
		if (FAILED(hr))	return hr;

		return S_OK;
	}

};