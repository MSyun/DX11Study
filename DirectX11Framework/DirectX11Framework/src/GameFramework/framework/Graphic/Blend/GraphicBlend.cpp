// グラフィックのブレンド
// 2017. 5.13	プログラム作成
// author	:	SyunMizuno


#include	"GraphicBlend.h"
#include	"../../Debug/Debug.h"



namespace MSLib {

	bool GraphicBlend::m_bAlpha = false;
	BlendType GraphicBlend::m_Blend = BLEND_NORMAL;


	void GraphicBlend::Set(
		BlendType type,
		ID3D11Device* device,
		ID3D11DeviceContext* context)
	{
		ID3D11BlendState* pBlendState = nullptr;
		D3D11_BLEND_DESC BlendDesc;
		ZeroMemory(&BlendDesc, sizeof(BlendDesc));

		switch (type) {
		case BLEND_NORMAL:		NormalSetting(&BlendDesc);			break;
		case BLEND_MULTI:		MultiSetting(&BlendDesc);			break;
		case BLEND_INV_MULTI:	InverseMultiSetting(&BlendDesc);	break;
		case BLEND_ADD:			AddSetting(&BlendDesc);				break;
		case BLEND_SUB:			SubSetting(&BlendDesc);				break;
		case BLEND_SCREEN:		ScreenSetting(&BlendDesc);			break;
		};

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		device->CreateBlendState(&BlendDesc, &pBlendState);
		context->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);
	}


	void GraphicBlend::SetAlphaEnable(
		bool alpha,
		ID3D11Device* device,
		ID3D11DeviceContext* context) {
		if (m_bAlpha == alpha)
			return;

		m_bAlpha = alpha;
		Set(m_Blend, device, context);
	}


#pragma region Setting
	void GraphicBlend::NormalSetting(D3D11_BLEND_DESC* pDesc) {
		pDesc->AlphaToCoverageEnable = FALSE;
		pDesc->IndependentBlendEnable = FALSE;
		pDesc->RenderTarget[0].BlendEnable = TRUE;
		pDesc->RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		pDesc->RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		pDesc->RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].SrcBlendAlpha = m_bAlpha ? D3D11_BLEND_ONE : D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_Blend = BLEND_NORMAL;
	}

	void GraphicBlend::MultiSetting(D3D11_BLEND_DESC* pDesc) {
		pDesc->AlphaToCoverageEnable = FALSE;
		pDesc->IndependentBlendEnable = FALSE;
		pDesc->RenderTarget[0].BlendEnable = TRUE;
		pDesc->RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
		pDesc->RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].SrcBlendAlpha = m_bAlpha ? D3D11_BLEND_ONE : D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_Blend = BLEND_MULTI;
	}

	void GraphicBlend::InverseMultiSetting(D3D11_BLEND_DESC* pDesc) {
		pDesc->AlphaToCoverageEnable = FALSE;
		pDesc->IndependentBlendEnable = FALSE;
		pDesc->RenderTarget[0].BlendEnable = TRUE;
		pDesc->RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
		pDesc->RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].SrcBlendAlpha = m_bAlpha ? D3D11_BLEND_ONE : D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_Blend = BLEND_INV_MULTI;
	}

	void GraphicBlend::AddSetting(D3D11_BLEND_DESC* pDesc) {
		pDesc->AlphaToCoverageEnable = FALSE;
		pDesc->IndependentBlendEnable = FALSE;
		pDesc->RenderTarget[0].BlendEnable = TRUE;
		pDesc->RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		pDesc->RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pDesc->RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].SrcBlendAlpha = m_bAlpha ? D3D11_BLEND_ONE : D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_Blend = BLEND_ADD;
	}

	void GraphicBlend::SubSetting(D3D11_BLEND_DESC* pDesc) {
		pDesc->AlphaToCoverageEnable = FALSE;
		pDesc->IndependentBlendEnable = FALSE;
		pDesc->RenderTarget[0].BlendEnable = TRUE;
		pDesc->RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		pDesc->RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pDesc->RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		pDesc->RenderTarget[0].SrcBlendAlpha = m_bAlpha ? D3D11_BLEND_ONE : D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_Blend = BLEND_SUB;
	}

	void GraphicBlend::ScreenSetting(D3D11_BLEND_DESC* pDesc) {
		pDesc->AlphaToCoverageEnable = FALSE;
		pDesc->IndependentBlendEnable = FALSE;
		pDesc->RenderTarget[0].BlendEnable = TRUE;
		pDesc->RenderTarget[0].SrcBlend = D3D11_BLEND_INV_DEST_COLOR;
		pDesc->RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pDesc->RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].SrcBlendAlpha = m_bAlpha ? D3D11_BLEND_ONE : D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		pDesc->RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		pDesc->RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_Blend = BLEND_SCREEN;
	}
#pragma endregion

};