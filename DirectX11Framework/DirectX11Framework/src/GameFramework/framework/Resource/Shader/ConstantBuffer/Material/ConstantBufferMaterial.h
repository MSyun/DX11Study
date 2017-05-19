// シェーダマテリアル用コンスタントバッファー
// 2017.05.15	: プログラム作成
// author		: SyunMizuno

#pragma once


#include	"../Base/ConstantBuffer.h"


namespace MSLib {
	namespace ShaderCollection {
		namespace Buffer {

			struct MATERIAL_CONSTANT_BUFFER {
				// Lambert
				float4	Diffuse;	// r.g.b拡散反射光	: wアルファ値
				float4	Ambient;	// r.g.b環境光		: wアルファ値
				float4	Emissive;	// r.g.b放射光		: wアルファ値

				// Phong
				float4	Specular;	// r.g.b鏡面反射光	: w光沢
			};

			class ConstantBufferMaterial : public	ConstantBuffer {
			private:
				MATERIAL_CONSTANT_BUFFER m_material;

			public:
				ConstantBufferMaterial();
				virtual ~ConstantBufferMaterial();

				void EndPass() override;

				void Diffuse(const float3& diffuse);
				void Ambient(const float3& ambient);
				void Emissive(const float3& emissive);
				void Alpha(const float alpha);
				void Specular(const float3& specular);
				void Shininess(const float shininess);

				//protected:
				virtual bool Create() override;
			};
		}
	}
}