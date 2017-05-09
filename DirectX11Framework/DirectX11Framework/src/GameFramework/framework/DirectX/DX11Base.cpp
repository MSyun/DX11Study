// DirectX11用ベースクラス
// 2016. 4.15	:	プログラム作成
// author		:	SyunMizuno


#include	"DX11Base.h"
#include	"../Screen/Screen.h"
#include	"../Utility/System/SystemUtility.h"
#include	"../Resource/Base/IResource.h"
#include	"../Graphic/Graphics.h"





/*									//
//			コンストラクタ			//
//									*/
DX11Base::DX11Base(Application* app) :
	IDXBase(app),
	m_pSwapChain(NULL),
	m_pRenderTargetView(NULL),
	m_pDepthStencilView(NULL),
	m_pDepthStencil(NULL),
	m_pRasterizerState(NULL)
{

}


/*									//
//			デストラクタ			//
//									*/
DX11Base::~DX11Base() {
	Release();
}


/*									//
//				初期化				//
//									*/
HRESULT DX11Base::Init() {
	// デバイスとスワップチェーンの作成
	if (FAILED(CreateDeviceSwapChain()))
		return E_FAIL;

	// レンダーターゲットビューの作成
	if (FAILED(CreateRenderTargetView()))
		return E_FAIL;

	// 深度ステンシルビューの作成
	if (FAILED(CreateDepthStencilView()))
		return E_FAIL;

	// レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	Graphics::GetDevice()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	// ビューポートの設定
	CreateViewport();

	// ラスタライズ設定
	CreateRasterize();

	if (FAILED(InitApp()))
		return E_FAIL;

	return S_OK;
}


/*									//
//	デバイスとスワップチェーンの作成//
//									*/
HRESULT DX11Base::CreateDeviceSwapChain() {
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Screen::GetWidth();
	sd.BufferDesc.Height = Screen::GetHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Application::GetHWND();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
	};
	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	HRESULT hr;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	for (int i = 0; i < numDriverTypes; ++ i) {
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			driverTypes[i],
			NULL,
			0,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_pSwapChain,
			&device,
			pFeatureLevel,
			&context);

		if (SUCCEEDED(hr))
			break;
	}
	IResource::SetDevice(device);
	Graphics::SetDevice(context);

	return hr;
}


/*									//
//		RenderTargetViewの作成		//
//									*/
HRESULT DX11Base::CreateRenderTargetView() {
	HRESULT hr;

	ID3D11Texture2D* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	hr = IResource::GetDevice()->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	SAFE_RELEASE(pBackBuffer);

	return hr;
}


/*									//
//		深度ステンシルビューの作成	//
//									*/
HRESULT DX11Base::CreateDepthStencilView() {
	HRESULT hr;
	ID3D11Device* device = IResource::GetDevice();

	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = Screen::GetWidth();
	descDepth.Height = Screen::GetHeight();
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	device->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil);
	hr = device->CreateDepthStencilView(m_pDepthStencil, NULL, &m_pDepthStencilView);

	return hr;
}


/*									//
//		ビューポートの設定			//
//									*/
void DX11Base::CreateViewport() {
	D3D11_VIEWPORT vp;
	vp.Width = (float)Screen::GetWidth();
	vp.Height = (float)Screen::GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	Graphics::GetDevice()->RSSetViewports(1, &vp);
}


/*									//
//		ラスタライズの設定			//
//									*/
void DX11Base::CreateRasterize() {
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = TRUE;

	IResource::GetDevice()->CreateRasterizerState(&rdc, &m_pRasterizerState);
	Graphics::GetDevice()->RSSetState(m_pRasterizerState);
}


/*									//
//			アプリの初期化			//
//									*/
HRESULT DX11Base::InitApp() {
	return S_OK;
}


/*									//
//			ステップ関数			//
//									*/
HRESULT DX11Base::Step() {
	Update();
	Draw();

	return S_OK;
}


/*									//
//				更新				//
//									*/
void DX11Base::Update() {

}


/*									//
//				描画				//
//									*/
void DX11Base::Draw() {
	float ClearColor[4] = { 0, 0, 1, 1 };
	ID3D11DeviceContext* context = Graphics::GetDevice();

	context->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	context->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);



	m_pSwapChain->Present(0, 0);
}


/*									//
//				終了処理			//
//									*/
HRESULT DX11Base::Release() {
	if (FAILED(ReleaseApp()))
		return E_FAIL;

	SAFE_RELEASE(m_pRasterizerState);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDepthStencil);
	SAFE_RELEASE(m_pDepthStencilView);

	return S_OK;
}


HRESULT DX11Base::ReleaseApp() {
	return S_OK;
}