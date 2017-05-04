// DirectX11用ベースクラス
// 2016. 4.15	:	プログラム作成
// author		:	SyunMizuno


#include	"DX11Base.h"
#include	"../Screen/Screen.h"
#include	"../Utility/System/SystemUtility.h"
#include	"../Resource/Base/IResource.h"
#include	"../Graphic/Graphics.h"

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
	Vector4	vDiffuse;
	Vector4	vEye;
};

Vector4 g_Light = Vector4(0.0f, 0.5f, -1.0f, 0.0f);


///////////////////////

/*									//
//			コンストラクタ			//
//									*/
DX11Base::DX11Base(Application* app) :
	IDXBase(app),
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


void DX11Base::CreateShader() {
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	ID3D11Device* device = IResource::GetDevice();

	// ブロブからバーテックスシェーダ作成
	HRESULT hr;
	hr = D3DX11CompileFromFile(
		"Phong.hlsl",
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

	hr = device->CreateVertexShader(
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
	hr = device->CreateInputLayout(
		layout,
		numElements,
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))	return;

	// ブロブからピクセルシェーダ作成
	hr = D3DX11CompileFromFile(
		"Phong.hlsl",
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
	hr = device->CreatePixelShader(
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

	hr = device->CreateBuffer(&cb, NULL, &m_pConstantBuffer);
	if (FAILED(hr))	return;
}


void DX11Base::CreatePolygon() {
	HRESULT hr;
	ID3D11Device* device = IResource::GetDevice();

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
	hr = device->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (FAILED(hr))	return;

	// バーテックスバッファーをセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Graphics::GetDevice()->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&stride,
		&offset);
	g_Light.normalize();

	m_pTexture = GetResourceManager<Texture>()->Create("Sprite.jpg");
	m_pCamera = NEW Camera;
//	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/x-wing.fbx");
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

	Matrix mWorld;
	// ワールドトランスフォーム（絶対座標変換）
	static float an = 0.0f;
	an += (1.0f / 1000.0f);
	MatrixRotationY(&mWorld, an);

	// カメラ
	m_pCamera->Set();
	Vector3 pos = m_pCamera->GetTransform()->GetPos();

	// 使用するシェーダの登録
	context->VSSetShader(m_pVertexShader, NULL, 0);
	context->PSSetShader(m_pPixelShader, NULL, 0);
	// シェーダのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	HRESULT hr;
	hr = context->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		cb.mWorld = mWorld;
		MatrixTranspose(&cb.mWorld, &cb.mWorld);
		// ワールド、カメラ、射影行列を渡す
		Matrix m = mWorld * m_pCamera->GetView() * m_pCamera->GetProj();
		MatrixTranspose(&m, &m);
		cb.mWVP = m;
		// カラーを渡す
		cb.vDiffuse = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		// ライトベクトルを渡す
		cb.vLightDir = g_Light;
		// カメラの位置（視点）をシェーダに渡す
		cb.vEye = Vector4(pos.x, pos.y, pos.z, 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		context->Unmap(m_pConstantBuffer, 0);
	}
	// このコンスタントバッファーを使うシェーダの登録
	context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	context->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// 頂点インプットレイアウトをセット
	context->IASetInputLayout(m_pVertexLayout);
	// プリミティブ・トポロジーをセット
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ―をシェーダに渡す
	auto samp = m_pTexture->GetSample();
	auto tex = m_pTexture->GetTexture();
	context->PSSetSamplers(0, 1, &samp);
	context->PSSetShaderResources(0, 1, &tex);

	// プリミティブをレンダリング
	context->Draw(4, 0);

	m_pSwapChain->Present(0, 0);
}


/*									//
//				終了処理			//
//									*/
HRESULT DX11Base::Release() {
	SAFE_DELETE(m_pCamera);

	SAFE_RELEASE(m_pRasterizerState);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout);

	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDepthStencil);
	SAFE_RELEASE(m_pDepthStencilView);

	return S_OK;
}