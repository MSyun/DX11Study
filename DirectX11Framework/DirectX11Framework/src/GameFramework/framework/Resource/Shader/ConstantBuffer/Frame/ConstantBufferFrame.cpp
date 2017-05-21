// シェーダフレーム用コンスタントバッファー
// 2017.05.16	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBufferFrame.h"
#include	"../../../../Graphic/Graphics.h"


namespace MSLib {
	namespace ShaderCollection {

		ConstantBufferFrame::ConstantBufferFrame(int resourceNum) :
			ConstantBuffer(resourceNum)
		{
		}

		ConstantBufferFrame::~ConstantBufferFrame()
		{
		}

		void ConstantBufferFrame::Set() {
			auto context = Graphics::GetDevice();
			m_pBuffer->Update((void*)&m_frame);
			auto buf = m_pBuffer->buf();

			context->VSSetConstantBuffers(m_ResourceNumber, 1, &buf);
			context->PSSetConstantBuffers(m_ResourceNumber, 1, &buf);
		}

		void ConstantBufferFrame::EyePos(const float4& eye) {
			m_frame.vEye = eye;
		}

		bool ConstantBufferFrame::Create() {
			m_pBuffer = new Buffer(sizeof(FRAME_CONSTANT_BUFFER));

			return true;
		}

	}
}