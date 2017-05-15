// �V�F�[�_���C�g�p�R���X�^���g�o�b�t�@�[
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno

#pragma once


#include	"../Base/ConstantBuffer.h"


namespace ShaderCollection {
	namespace Buffer {

		struct LIGHT_CONSTANT_BUFFER {
			float4	Diffuse;	// r.g.b�g�U���ˌ�	: w�A���t�@�l
			float4	Ambient;	// r.g.b����		: w�A���t�@�l
			float4	Specular;	// r.g.b���ʔ��ˌ�	: w�A���t�@�l
			float4	Direction;	// �����x�N�g��
		};

		class ConstantBufferLight	:	public	ConstantBuffer {
		private:
			// �V�F�[�_���̃��W�X�^�ԍ��ɍ��킹�鎖
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