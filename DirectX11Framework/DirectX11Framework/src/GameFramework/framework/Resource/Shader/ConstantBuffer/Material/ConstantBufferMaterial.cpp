// シェーダマテリアル用コンスタントバッファー
// 2017.05.15	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBufferMaterial.h"

#include	"../../../../Graphic/Graphics.h"
#include	"../../../../Utility/Math/MathUtility.h"


namespace ShaderCollection {
	namespace Buffer {

		ConstantBufferMaterial::ConstantBufferMaterial()
		{
		}

		ConstantBufferMaterial::~ConstantBufferMaterial()
		{
		}

		void ConstantBufferMaterial::BeginPass() {
			HRESULT hr = Graphics::GetDevice()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
			if (FAILED(hr))
				return;
		}

		void ConstantBufferMaterial::EndPass() {
			auto context = Graphics::GetDevice();
			memcpy_s(pData.pData, pData.RowPitch, (void*)(&m_material), sizeof(m_material));
			context->Unmap(m_pBuffer, 0);

			context->VSSetConstantBuffers(m_ResourceNumber, 1, &m_pBuffer);
			context->PSSetConstantBuffers(m_ResourceNumber, 1, &m_pBuffer);
		}

		void ConstantBufferMaterial::Diffuse(const float3& diffuse) {
			m_material.Diffuse.r = diffuse.r;
			m_material.Diffuse.g = diffuse.g;
			m_material.Diffuse.b = diffuse.b;
		}

		void ConstantBufferMaterial::Ambient(const float3& ambient) {
			m_material.Ambient.r = ambient.r;
			m_material.Ambient.g = ambient.g;
			m_material.Ambient.b = ambient.b;
		}

		void ConstantBufferMaterial::Emissive(const float3& emissive) {
			m_material.Emissive.r = emissive.r;
			m_material.Emissive.g = emissive.g;
			m_material.Emissive.b = emissive.b;
		}

		void ConstantBufferMaterial::Alpha(const float alpha) {
			float a = Clamp(alpha, 0.0f, 1.0f);
			m_material.Diffuse.a = a;
			m_material.Ambient.a = a;
			m_material.Emissive.a = a;
		}

		void ConstantBufferMaterial::Specular(const float3& specular) {
			m_material.Specular.r = specular.r;
			m_material.Specular.g = specular.g;
			m_material.Specular.b = specular.b;
		}

		void ConstantBufferMaterial::Shininess(const float shininess) {
			m_material.Specular.w = shininess;
		}

		bool ConstantBufferMaterial::Create() {
			if (!CreateConstantBuffer(
				&m_pBuffer,
				sizeof(SIMPLESHADER_CONSTANT_BUFFER)))
				return false;

			return true;
		}
	}
}