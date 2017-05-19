// DirectX11用ベースクラス
// 2016. 4.15	:	プログラム作成
// author		:	SyunMizuno

#pragma once


#include	"DXBase.h"
#include	<d3d11.h>
#include	<D3DX11.h>



namespace MSLib {

	class	DX11Base : public	IDXBase {
	protected:
		IDXGISwapChain*			m_pSwapChain;
		ID3D11RenderTargetView*	m_pRenderTargetView;
		ID3D11DepthStencilView*	m_pDepthStencilView;
		ID3D11Texture2D*		m_pDepthStencil;
		ID3D11RasterizerState*	m_pRasterizerState;

	public:
		explicit DX11Base(Application* app);
		virtual ~DX11Base();

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

	protected:
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

		virtual HRESULT InitApp();
		virtual HRESULT ReleaseApp();

		virtual void Update();
		virtual void Draw();
	};

};