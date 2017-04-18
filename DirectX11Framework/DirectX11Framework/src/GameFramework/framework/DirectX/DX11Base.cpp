// DirectX11用ベースクラス
// 2016. 4.15	:	プログラム作成
// author		:	SyunMizuno


#include	"DX11Base.h"
#include	"../Screen/Screen.h"
#include	"../Utility/System/SystemUtility.h"

///////////////////////
// ここから一時的
#include	"../Convert/Convert.h"
#include	<d3dcompiler.h>
#include	<tchar.h>
struct SimpleVertex {
	Point3 Pos;
	Vector3 Normal;
	Vector2 Tex;
};

struct SIMPLESHADER_CONSTANT_BUFFER {
	Matrix	mWorld;
	Matrix	mWVP;
	Vector4	vLightDir;
	Vector4	vColor;
	Vector4	vEye;
};

Vector4 g_Light = Vector4(0.0f, 0.5f, -1.0f, 0.0f);


///////////////////////

/*									//
//			コンストラクタ			//
//									*/
DX11Base::DX11Base(Application* app) :
	IDXBase(app),
	m_pDevice(NULL),
	m_pDeviceContext(NULL),
	m_pSwapChain(NULL),
	m_pRenderTargetView(NULL),
	m_pDepthStencilView(NULL),
	m_pDepthStencil(NULL),
	m_pRasterizerState(NULL),
	m_pVertexLayout(NULL),
	m_pVertexShader(NULL),
	m_pPixelShader(NULL),
	m_pConstantBuffer(NULL),
	m_pVertexBuffer(NULL)
{

}


/*									//
//			デストラクタ			//
//									*/
DX11Base::~DX11Base() {

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
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	// ビューポートの設定
	CreateViewport();

	// ラスタライズ設定
	CreateRasterize();

	// シェーダの作成
	CreateShader();

	// ポリゴンの作成
	CreatePolygon();

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

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&m_pSwapChain,
		&m_pDevice,
		pFeatureLevel,
		&m_pDeviceContext);

	return hr;
}


/*									//
//		RenderTargetViewの作成		//
//									*/
HRESULT DX11Base::CreateRenderTargetView() {
	HRESULT hr;

	ID3D11Texture2D* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	SAFE_RELEASE(pBackBuffer);

	return hr;
}


/*									//
//		深度ステンシルビューの作成	//
//									*/
HRESULT DX11Base::CreateDepthStencilView() {
	HRESULT hr;

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
	m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil);
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencil, NULL, &m_pDepthStencilView);

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
	m_pDeviceContext->RSSetViewports(1, &vp);
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

	m_pDevice->CreateRasterizerState(&rdc, &m_pRasterizerState);
	m_pDeviceContext->RSSetState(m_pRasterizerState);
}


void DX11Base::CreateShader() {
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;

	// ブロブからバーテックスシェーダ作成
	HRESULT hr;
	hr = D3DX11CompileFromFile(
		"Simple.hlsl",
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		0,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL);
	if (FAILED(hr)) {
		MessageBox(0, (LPCTSTR)pErrors->GetBufferPointer(), _T("ERROR"), MB_OK);
		return;
	}
	SAFE_RELEASE(pErrors);

	hr = m_pDevice->CreateVertexShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&m_pVertexShader);
	if (FAILED(hr)) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, "バーテックスシェーダ作成失敗", NULL, MB_OK);
		return;
	}

	// 頂点インプットレイアウトを定義
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	// 頂点インプットレイアウトを作成
	hr = m_pDevice->CreateInputLayout(
		layout,
		numElements,
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))	return;

	// ブロブからピクセルシェーダ作成
	hr = D3DX11CompileFromFile(
		"Simple.hlsl",
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		0,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL);
	if (FAILED(hr)) {
		MessageBox(0, (LPCTSTR)pErrors->GetBufferPointer(), _T("ERROR"), MB_OK);
		return;
	}
	SAFE_RELEASE(pErrors);
	hr = m_pDevice->CreatePixelShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&m_pPixelShader);
	if (FAILED(hr)) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, (LPCTSTR)pErrors->GetBufferPointer(), NULL, MB_OK);
		return;
	}
	SAFE_RELEASE(pCompiledShader);

	// コンスタントバッファ―作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	hr = m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer);
	if (FAILED(hr))	return;
}


void DX11Base::CreatePolygon() {
	HRESULT hr;

	// バーテックスバッファー作成
	SimpleVertex vertices[] = {
		Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 1),
		Vector3(-0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 0),
		Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 1),
		Vector3(0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 0),
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	hr = m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (FAILED(hr))	return;

	// バーテックスバッファーをセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&stride,
		&offset);
	g_Light.normalize();
	// テクスチャ―用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m_pDevice->CreateSamplerState(&SamDesc, &m_pSampleLinear);
	// テクスチャ―作成
	hr = D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		"sprite.jpg",
		NULL,
		NULL,
		&m_pTexture,
		NULL);
	if (FAILED(hr)) {
		return;
	}
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
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	Matrix mWorld, mView, mProj;
	// ワールドトランスフォーム（絶対座標変換）
	static float an = 0.0f;
	an += (1.0f / 1000.0f);
	MatrixRotationY(&mWorld, an);
	// ビュートランスフォーム
	Vector3 vEyePt(0.0f, 1.0f, -2.0f);
	Vector3 vLookatPt(0.0f, 0.0f, 0.0f);
	Vector3 vUpVec(0.0f, 1.0f, 0.0f);
	MatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);
	// プロジェクショントランスフォーム（射影変換）
	MatrixPerspectiveFovLH(
		&mProj,
		3.141592f/4.0f,
		(float)Screen::GetWidth()/(float)Screen::GetHeight(),
		0.1f,
		100.0f);

	// 使用するシェーダの登録
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	// シェーダのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	HRESULT hr;
	hr = m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		cb.mWorld = mWorld;
		MatrixTranspose(&cb.mWorld, &cb.mWorld);
		// ワールド、カメラ、射影行列を渡す
		Matrix m = mWorld * mView * mProj;
		MatrixTranspose(&m, &m);
		cb.mWVP = m;
		// カラーを渡す
		Vector4 vColor(1, 0, 0, 1);
		cb.vColor = vColor;
		// ライトベクトルを渡す
		cb.vLightDir = g_Light;
		// カメラの位置（視点）をシェーダに渡す
		cb.vEye = Vector4(vEyePt.x, vEyePt.y, vEyePt.z, 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	// このコンスタントバッファーを使うシェーダの登録
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// 頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	// プリミティブ・トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ―をシェーダに渡す
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	// プリミティブをレンダリング
	m_pDeviceContext->Draw(4, 0);

	m_pSwapChain->Present(0, 0);
}


/*									//
//				終了処理			//
//									*/
HRESULT DX11Base::Release() {
	SAFE_RELEASE(m_pRasterizerState);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout);

	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDepthStencil);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pDevice);

	return S_OK;
}