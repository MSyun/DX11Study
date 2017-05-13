// ゲーム用DirectX11
// 2016. 5. 9	:	プログラム作成
// author		:	SyunMizuno


#include	"GameDirectX11Base.h"
#include	"../framework/Input/Input.h"
#include	"../DelayFunction/Collection/DelayFunctionCollection.h"
#include	"../framework/Graphic/Graphics.h"



/*									//
//			コンストラクタ			//
//									*/
GameDirectX11Base::GameDirectX11Base(Application* app) :
	DX11Base(app),
	m_pCurScene(nullptr),
	m_pSceneManager(nullptr),
	m_pTexManager(nullptr),
	m_pMeshManager(nullptr),
	m_pShaderManager(nullptr)
{
}


/*									//
//			デストラクタ			//
//									*/
GameDirectX11Base::~GameDirectX11Base() {
	Release();
}


/*									//
//				ステップ			//
//									*/
HRESULT GameDirectX11Base::Step() {
	Time::Update();
	Input::Update();
	Update();
	Draw();

	return S_OK;
}


/*									//
//				解放				//
//									*/
HRESULT GameDirectX11Base::Release() {
	if (FAILED(ReleaseGame())) {
		Debug::LogError("ゲームの解放処理に失敗しました");
		return E_FAIL;
	}

	if (FAILED(DX11Base::Release())) {
		Debug::LogError("ゲームの解放処理に失敗しました");
		return E_FAIL;
	}

	return S_OK;
}


/*									//
//			アプリの解放			//
//									*/
HRESULT GameDirectX11Base::ReleaseApp() {
	SAFE_DELETE(m_pShaderManager);
	SAFE_DELETE(m_pMeshManager);
	SAFE_DELETE(m_pTexManager);
	SAFE_DELETE(m_pSceneManager);

	return S_OK;
}


/*									//
//				初期化				//
//									*/
HRESULT GameDirectX11Base::Init() {
	if (FAILED(DX11Base::Init())) {
		Debug::LogError("ゲームの初期化処理に失敗しました");
		return E_FAIL;
	}

	if (FAILED(InitGame())) {
		Debug::LogError("ゲームの初期化処理に失敗しました");
		return E_FAIL;
	}

	return S_OK;
}


/*									//
//			アプリの初期化			//
//									*/
HRESULT GameDirectX11Base::InitApp() {
	Input::Init(m_pApp->GetHWND());

	m_pSceneManager = new SceneManagerWins;
	m_pTexManager = new ResourceManager<Texture>;
	m_pMeshManager = new ResourceManager<Mesh>;
	m_pShaderManager = new ResourceManager<Shader>;

	return S_OK;
}


/*									//
//				更新				//
//									*/
void GameDirectX11Base::Update() {
	m_pCurScene = m_pSceneManager->GetScene();
	if (m_pCurScene)
		m_pCurScene->Update();
	DelayFunctionCollection::Update();
}


/*									//
//				描画				//
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