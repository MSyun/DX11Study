// シェーダフレーム用コンスタントバッファー
// 2017.05.16	: プログラム作成
// author		: SyunMizuno


#pragma once


#include	"../Base/ConstantBuffer.h"


namespace MSLib {
	namespace ShaderCollection {
		namespace Buffer {

			struct FRAME_CONSTANT_BUFFER {
				float4	vEye;
			};

			class ConstantBufferFrame : public	ConstantBuffer {
			private:
				FRAME_CONSTANT_BUFFER m_frame;

			public:
				ConstantBufferFrame();
				virtual ~ConstantBufferFrame();

				void EndPass() override;

				void EyePos(const float4& eye);

				virtual bool Create() override;
			};

		}
	}
}