// DirectX11�p�x�[�X�N���X
// 2016. 4.15	:	�v���O�����쐬
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

		/* ������
		// return	: S_OK. �����AE_FAIL. ���s
		*/
		virtual HRESULT Init() override;

		/* �X�e�b�v�֐�
		// return	: S_OK. �����AE_FAIL. ���s
		*/
		virtual HRESULT Step() override;

		/* �I������
		// return	: S_OK. �����AE_FAIL. ���s
		*/
		virtual HRESULT Release() override;

	protected:
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

		virtual HRESULT InitApp();
		virtual HRESULT ReleaseApp();

		virtual void Update();
		virtual void Draw();
	};

};