// �e�N�X�`��
// 2017.04.24	: �v���O�����쐬
// author		: SyunMizuno

#pragma once

#include	"../Base/IResource.h"
#include	<d3dx11.h>


namespace MSLib {

	class Texture : public IResource {
	protected:
		// �e�N�X�`���̐ݒ肪����������
		D3D11_SAMPLER_DESC		m_Sampler;

		// ��̂����H��������
		ID3D11SamplerState*		m_pSampleLinear;

		// �e�N�X�`��
		ID3D11ShaderResourceView*	m_pTexture;

	public:
		Texture();
		virtual ~Texture();

		/* ���\�[�X���쐬
		// name	: �t�@�C���f�B���N�g��
		*/
		bool Create(const std::string& name) override;

		/* ���\�[�X���폜 */
		void Delete() override;

		/* ����ݒ�
		// samp	: �T���v���[�̐ݒ�
		*/
		void SetInfo(const D3D11_SAMPLER_DESC& samp);

		/* �T���v���X�e�[�g���擾
		// return	; �T���v���[
		*/
		ID3D11SamplerState* GetSample() const;

		/* �e�N�X�`�����擾
		// return	: �e�N�X�`��
		*/
		ID3D11ShaderResourceView* GetTexture() const;

	protected:
		/* �f�t�H���g�̏���ݒ� */
		void SetDefaultInfo();
	};

}