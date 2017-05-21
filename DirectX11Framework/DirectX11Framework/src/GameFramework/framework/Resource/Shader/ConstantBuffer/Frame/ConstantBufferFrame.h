// �V�F�[�_�t���[���p�R���X�^���g�o�b�t�@�[
// 2017.05.16	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	"../Base/ConstantBuffer.h"


namespace MSLib {
	namespace ShaderCollection {

		struct FRAME_CONSTANT_BUFFER {
			float4	vEye;
		};

		class ConstantBufferFrame : public	ConstantBuffer {
		private:
			FRAME_CONSTANT_BUFFER m_frame;

		public:
			ConstantBufferFrame(int resourceNum);
			virtual ~ConstantBufferFrame();

			void Set() override;

			void EyePos(const float4& eye);

			virtual bool Create() override;
		};

	}
}