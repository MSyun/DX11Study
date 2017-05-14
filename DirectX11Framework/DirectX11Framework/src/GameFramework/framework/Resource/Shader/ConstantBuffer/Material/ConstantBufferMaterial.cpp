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
			m_material.Diffuse.x = diffuse.x;
			m_material.Diffuse.y = diffuse.y;
			m_material.Diffuse.z = diffuse.z;
		}

		void ConstantBufferMaterial::Ambient(const float3& ambient) {
			m_material.Ambient.x = ambient.x;
			m_material.Ambient.y = ambient.y;
			m_material.Ambient.z = ambient.z;
		}

		void ConstantBufferMaterial::Emissive(const float3& emissive) {
			m_material.Emissive.x = emissive.x;
			m_material.Emissive.y = emissive.y;
			m_material.Emissive.z = emissive.z;
		}

		void ConstantBufferMaterial::Alpha(const float alpha) {
			float a = Clamp(alpha, 0.0f, 1.0f);
			m_material.Diffuse.a = a;
			m_material.Ambient.a = a;
			m_material.Emissive.a = a;
		}

		void ConstantBufferMaterial::Specular(const float3& specular) {
			m_material.Specular.x = specular.x;
			m_material.Specular.y = specular.y;
			m_material.Specular.z = specular.z;
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