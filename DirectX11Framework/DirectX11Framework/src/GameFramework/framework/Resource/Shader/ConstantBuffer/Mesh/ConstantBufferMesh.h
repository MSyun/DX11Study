// �V�F�[�_���b�V���p�R���X�^���g�o�b�t�@�[
// 2017.05.16	: �v���O�����쐬
// author		: SyunMizuno

#pragma once


#include	"../Base/ConstantBuffer.h"


namespace MSLib {
	namespace ShaderCollection {
		namespace Buffer {

			struct MESH_CONSTANT_BUFFER {
				Matrix	World;
				Matrix	WVP;
			};

			class ConstantBufferMesh : public	ConstantBuffer {
			private:
				MESH_CONSTANT_BUFFER m_mesh;

			public:
				ConstantBufferMesh();
				virtual ~ConstantBufferMesh();

				void EndPass() override;

				void World(const Matrix& world);
				void WVP(const Matrix& wvp);

				virtual bool Create() override;
			};

		}
	}
}