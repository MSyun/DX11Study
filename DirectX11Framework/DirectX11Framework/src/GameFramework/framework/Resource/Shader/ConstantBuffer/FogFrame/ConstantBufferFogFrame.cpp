// シェーダフレーム用コンスタントバッファー
// 2017.05.16	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBufferFogFrame.h"
#include	"../../../../Graphic/Graphics.h"


namespace MSLib {
	namespace ShaderCollection {

		ConstantBufferFogFrame::ConstantBufferFogFrame(int resourceNum) :
			ConstantBuffer(resourceNum)
		{
			m_frame.vFog = float4(1.0f, 1.0f, 1.0f, 1.0f);
			m_frame.vFogColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
			m_frame.fEnd = 100.0f;
		}

		ConstantBufferFogFrame::~ConstantBufferFogFrame()
		{
		}

		void ConstantBufferFogFrame::Set() {
			auto context = Graphics::GetDevice();
			m_pBuffer->Update((void*)&m_frame);
			auto buf = m_pBuffer->buf();

			context->VSSetConstantBuffers(m_ResourceNumber, 1, &buf);
			context->PSSetConstantBuffers(m_ResourceNumber, 1, &buf);
		}

		void ConstantBufferFogFrame::EyePos(const float4& eye) {
			m_frame.vEye = eye;
		}
		void ConstantBufferFogFrame::Fog(const float4& fog) {
			m_frame.vFog = fog;
		}
		void ConstantBufferFogFrame::FogColor(const float4& fogColor) {
			m_frame.vFogColor = fogColor;
		}
		void ConstantBufferFogFrame::End(const float& end) {
			m_frame.fEnd = end;
		}

		bool ConstantBufferFogFrame::Create() {
			m_pBuffer = new Buffer(sizeof(FOG_FRAME_CONSTANT_BUFFER));

			return true;
		}

	}
}