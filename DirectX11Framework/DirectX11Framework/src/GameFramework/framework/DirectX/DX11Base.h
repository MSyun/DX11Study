// DirectX11用ベースクラス
// 2016. 4.15	:	プログラム作成
// author		:	SyunMizuno

#pragma once


#include	"DXBase.h"
#include	<d3d11.h>
#include	<D3DX11.h>


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dCompiler.lib")



class	DX11Base	:	public	IDXBase {
protected:
#pragma region variable

	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pDeviceContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pRenderTargetView;
	ID3D11DepthStencilView*	m_pDepthStencilView;
	ID3D11Texture2D*		m_pDepthStencil;
	ID3D11RasterizerState*	m_pRasterizerState;

	///////////////////////////////////////
	// 一時的
	ID3D11InputLayout*	m_pVertexLayout;
	ID3D11VertexShader*	m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;
	ID3D11Buffer*		m_pConstantBuffer;

	ID3D11Buffer*		m_pVertexBuffer;

	ID3D11SamplerState*	m_pSampleLinear;
	ID3D11ShaderResourceView*	m_pTexture;
	///////////////////////////////////////

#pragma endregion

public:
#pragma region method

	explicit DX11Base(Application* app);
	virtual ~DX11Base();

	/* 初期化
	// return	: S_OK. 成功、E_FAIL. 失敗
	*/
	virtual HRESULT Init();

	/* ステップ関数
	// return	: S_OK. 成功、E_FAIL. 失敗
	*/
	virtual HRESULT Step();

	/* 終了処理
	// return	: S_OK. 成功、E_FAIL. 失敗
	*/
	virtual HRESULT Release();

#pragma endregion

private:
#pragma region conceal method

	virtual HRESULT InvalidateDeviceObjects() { return S_OK; };	// OnLostDevice
	virtual HRESULT RestoreDeviceObjects() { return S_OK; };	// OnResetDevice

	/* デバイスとスワップチェーンの作成
	// return	: S_OK. 成功、E_FAIL. 失敗
	*/
	virtual HRESULT CreateDeviceSwapChain();

	/* RenderTargetViewの作成
	// return	: S_OK. 成功、E_FAIL. 失敗
	*/
	virtual HRESULT CreateRenderTargetView();

	/* 深度ステンシルビューの作成
	// return	: S_OK. 成功、E_FAIL. 失敗
	*/
	virtual HRESULT CreateDepthStencilView();

	/* ビューポートの設定 */
	virtual void CreateViewport();

	/* ラスタライズの設定 */
	virtual void CreateRasterize();

	/* シェーダの作成 */
	virtual void CreateShader();

	virtual void CreatePolygon();

	virtual void Update();
	virtual void Draw();

#pragma endregion
};