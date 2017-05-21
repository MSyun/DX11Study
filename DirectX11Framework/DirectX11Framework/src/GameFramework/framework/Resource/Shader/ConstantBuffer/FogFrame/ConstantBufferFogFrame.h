// シェーダフレーム用コンスタントバッファー
// 2017.05.21	: プログラム作成
// author		: SyunMizuno


#pragma once


#include	"../Base/ConstantBuffer.h"


namespace MSLib {
	namespace ShaderCollection {

		struct FOG_FRAME_CONSTANT_BUFFER {
			float4	vEye;
			float4	vFog;
			float4	vFogColor;
			float	fEnd;
		};

		class ConstantBufferFogFrame : public	ConstantBuffer {
		private:
			FOG_FRAME_CONSTANT_BUFFER m_frame;

		public:
			ConstantBufferFogFrame(int resourceNum);
			virtual ~ConstantBufferFogFrame();

			void Set() override;

			void EyePos(const float4& eye);
			void Fog(const float4& fog);
			void FogColor(const float4& fogColor);
			void End(const float& end);

			virtual bool Create() override;
		};

	}
}