// シェーダライト用コンスタントバッファー
// 2017.05.15	: プログラム作成
// author		: SyunMizuno

#pragma once


#include	"../Base/ConstantBuffer.h"


namespace ShaderCollection {
	namespace Buffer {

		struct LIGHT_CONSTANT_BUFFER {
			float4	Diffuse;	// r.g.b拡散反射光	: wアルファ値
			float4	Ambient;	// r.g.b環境光		: wアルファ値
			float4	Specular;	// r.g.b鏡面反射光	: wアルファ値
			float4	Direction;	// 方向ベクトル
		};

		class ConstantBufferLight	:	public	ConstantBuffer {
		private:
			// シェーダ内のレジスタ番号に合わせる事
			const int m_ResourceNumber = 1;
			LIGHT_CONSTANT_BUFFER m_light;

		public:
			ConstantBufferLight();
			virtual ~ConstantBufferLight();

			void BeginPass() override;
			void EndPass() override;

			void Diffuse(const float3& diffuse);
			void Ambient(const float3& ambient);
			void Specular(const float3& specular);
			void Alpha(const float alpha);
			void Direction(const float4& direction);

			virtual bool Create() override;
		};
	}
}