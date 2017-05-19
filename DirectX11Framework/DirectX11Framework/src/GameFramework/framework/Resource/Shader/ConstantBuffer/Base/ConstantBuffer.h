// �V�F�[�_�p�R���X�^���g�o�b�t�@�[
// 2017.05.14	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	<d3d11.h>
#include	"../../../../Convert/Convert.h"


namespace MSLib {
	namespace ShaderCollection {
		namespace Buffer {

			class ConstantBuffer {
			protected:
				int m_ResourceNumber;
				ID3D11Buffer*	m_pBuffer;

				D3D11_MAPPED_SUBRESOURCE pData;

			public:
				ConstantBuffer(int resourceNum = -1);
				virtual ~ConstantBuffer();

				//		void Update(const void* srcPtr);
				virtual void BeginPass();
				virtual void EndPass() = 0;

				virtual bool Create() = 0;
			};


			/* �R���X�^���g�o�b�t�@�[�쐬
			// ppBuffer	:
			// size		:
			*/
			bool CreateConstantBuffer(
				ID3D11Buffer** ppBuffer,
				size_t size);

		}
	}
}