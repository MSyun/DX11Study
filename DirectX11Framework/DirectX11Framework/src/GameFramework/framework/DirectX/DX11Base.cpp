// DirectX11�p�x�[�X�N���X
// 2016. 4.15	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"DX11Base.h"
#include	"../Screen/Screen.h"
#include	"../Utility/System/SystemUtility.h"



/*									//
//			�R���X�g���N�^			//
//									*/
DX11Base::DX11Base(Application* app) :
	IDXBase(app),
	m_pDevice(NULL),
	m_pDeviceContext(NULL),
	m_pSwapChain(NULL),
	m_pRenderTargetView(NULL),
	m_pDepthStencilView(NULL),
	m_pDepthStencil(NULL)
{

}


/*									//
//			�f�X�g���N�^			//
//									*/
DX11Base::~DX11Base() {

}


/*									//
//				������				//
//									*/
HRESULT DX11Base::Init() {
	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	if (FAILED(CreateDeviceSwapChain()))
		return E_FAIL;

	// �����_�[�^�[�Q�b�g�r���[�̍쐬
	if (FAILED(CreateRenderTargetView()))
		return E_FAIL;

	// �[�x�X�e���V���r���[�̍쐬
	if (FAILED(CreateDepthStencilView()))
		return E_FAIL;

	// �����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ƀo�C���h
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	// �r���[�|�[�g�̐ݒ�
	CreateViewport();

	// ���X�^���C�Y�ݒ�
	CreateRasterize();

	return S_OK;
}


/*									//
//	�f�o�C�X�ƃX���b�v�`�F�[���̍쐬//
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
//		RenderTargetView�̍쐬		//
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
//		�[�x�X�e���V���r���[�̍쐬	//
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
//		�r���[�|�[�g�̐ݒ�			//
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
//		���X�^���C�Y�̐ݒ�			//
//									*/
void DX11Base::CreateRasterize() {
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	ID3D11RasterizerState* pIr = NULL;
	m_pDevice->CreateRasterizerState(&rdc, &pIr);
	m_pDeviceContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);
}


/*									//
//			�X�e�b�v�֐�			//
//									*/
HRESULT DX11Base::Step() {
	Update();
	Draw();

	return S_OK;
}


/*									//
//				�X�V				//
//									*/
void DX11Base::Update() {
	
}


/*									//
//				�`��				//
//									*/
void DX11Base::Draw() {
	float ClearColor[4] = { 0, 0, 1, 1 };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	m_pSwapChain->Present(0, 0);
}


/*									//
//				�I������			//
//									*/
HRESULT DX11Base::Release() {
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDepthStencil);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pDevice);

	return S_OK;
}