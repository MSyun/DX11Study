// �V�F�[�_�}�e���A���p�R���X�^���g�o�b�t�@�[
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno

#pragma once


#include	"../Base/ConstantBuffer.h"


namespace MSLib {
	namespace ShaderCollection {
		namespace Buffer {

			struct MATERIAL_CONSTANT_BUFFER {
				// Lambert
				float4	Diffuse;	// r.g.b�g�U���ˌ�	: w�A���t�@�l
				float4	Ambient;	// r.g.b����		: w�A���t�@�l
				float4	Emissive;	// r.g.b���ˌ�		: w�A���t�@�l

				// Phong
				float4	Specular;	// r.g.b���ʔ��ˌ�	: w����
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