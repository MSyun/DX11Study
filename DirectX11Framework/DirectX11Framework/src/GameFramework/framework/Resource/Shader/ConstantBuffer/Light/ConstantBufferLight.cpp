// シェーダライト用コンスタントバッファー
// 2017.05.15	: プログラム作成
// author		: SyunMizuno

#include	"ConstantBufferLight.h"
#include	"../../../../Graphic/Graphics.h"
#include	"../../../../Utility/Math/MathUtility.h"


namespace MSLib {
	namespace ShaderCollection {
		namespace Buffer {

			ConstantBufferLight::ConstantBufferLight() :
				ConstantBuffer(3)
			{
			}

			ConstantBufferLight::~ConstantBufferLight()
			{
			}

			void ConstantBufferLight::EndPass() {
				auto context = Graphics::GetDevice();
				memcpy_s(pData.pData, pData.RowPitch, (void*)(&m_light), sizeof(m_light));
				context->Unmap(m_pBuffer, 0);

				context->VSSetConstantBuffers(m_ResourceNumber, 1, &m_pBuffer);
				context->PSSetConstantBuffers(m_ResourceNumber, 1, &m_pBuffer);
			}

			void ConstantBufferLight::Diffuse(const float3& diffuse) {
				m_light.Diffuse.r = diffuse.r;
				m_light.Diffuse.g = diffuse.g;
				m_light.Diffuse.b = diffuse.b;
			}

			void ConstantBufferLight::Ambient(const float3& ambient) {
				m_light.Ambient.r = ambient.r;
				m_light.Ambient.g = ambient.g;
				m_light.Ambient.b = ambient.b;
			}

			void ConstantBufferLight::Specular(const float3& specular) {
				m_light.Specular.r = specular.r;
				m_light.Specular.g = specular.g;
				m_light.Specular.b = specular.b;
			}

			void ConstantBufferLight::Alpha(const float alpha) {
				float a = Clamp(alpha, 0.0f, 1.0f);
				m_light.Diffuse.a = a;
				m_light.Ambient.a = a;
				m_light.Specular.a = a;
			}

			void ConstantBufferLight::Direction(const float4& direction) {
				m_light.Direction = direction;
			}

			bool ConstantBufferLight::Create() {
				if (!CreateConstantBuffer(
					&m_pBuffer,
					sizeof(LIGHT_CONSTANT_BUFFER)))
					return false;

				return true;
			}

		}
	}
}