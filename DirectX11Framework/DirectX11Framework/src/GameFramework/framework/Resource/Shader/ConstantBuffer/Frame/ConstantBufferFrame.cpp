// シェーダフレーム用コンスタントバッファー
// 2017.05.16	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBufferFrame.h"

#include	"../../../../Graphic/Graphics.h"
#include	"../../../../Utility/Math/MathUtility.h"


namespace ShaderCollection {
	namespace Buffer {

		ConstantBufferFrame::ConstantBufferFrame() :
			ConstantBuffer(0)
		{
		}

		ConstantBufferFrame::~ConstantBufferFrame()
		{
		}

		void ConstantBufferFrame::EndPass() {
			auto context = Graphics::GetDevice();
			memcpy_s(pData.pData, pData.RowPitch, (void*)(&m_frame), sizeof(m_frame));
			context->Unmap(m_pBuffer, 0);

			context->VSSetConstantBuffers(m_ResourceNumber, 1, &m_pBuffer);
			context->PSSetConstantBuffers(m_ResourceNumber, 1, &m_pBuffer);
		}

		void ConstantBufferFrame::EyePos(const float4 eye) {
			m_frame.vEye = eye;
		}

		bool ConstantBufferFrame::Create(D3D11_BUFFER_DESC* desc) {
			if (!CreateConstantBuffer(
				desc,
				&m_pBuffer,
				sizeof(FRAME_CONSTANT_BUFFER)))
				return false;

			return true;
		}

	}
}