// DirectX11�p�x�[�X�N���X
// 2016. 4.15	:	�v���O�����쐬
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
	// �ꎞ�I
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

	/* ������
	// return	: S_OK. �����AE_FAIL. ���s
	*/
	virtual HRESULT Init();

	/* �X�e�b�v�֐�
	// return	: S_OK. �����AE_FAIL. ���s
	*/
	virtual HRESULT Step();

	/* �I������
	// return	: S_OK. �����AE_FAIL. ���s
	*/
	virtual HRESULT Release();

#pragma endregion

private:
#pragma region conceal method

	virtual HRESULT InvalidateDeviceObjects() { return S_OK; };	// OnLostDevice
	virtual HRESULT RestoreDeviceObjects() { return S_OK; };	// OnResetDevice

	/* �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	// return	: S_OK. �����AE_FAIL. ���s
	*/
	virtual HRESULT CreateDeviceSwapChain();

	/* RenderTargetView�̍쐬
	// return	: S_OK. �����AE_FAIL. ���s
	*/
	virtual HRESULT CreateRenderTargetView();

	/* �[�x�X�e���V���r���[�̍쐬
	// return	: S_OK. �����AE_FAIL. ���s
	*/
	virtual HRESULT CreateDepthStencilView();

	/* �r���[�|�[�g�̐ݒ� */
	virtual void CreateViewport();

	/* ���X�^���C�Y�̐ݒ� */
	virtual void CreateRasterize();

	/* �V�F�[�_�̍쐬 */
	virtual void CreateShader();

	virtual void CreatePolygon();

	virtual void Update();
	virtual void Draw();

#pragma endregion
};