// �o�[�e�b�N�X�V�F�[�_
// 2017.05.14	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	<d3d11.h>
#include	"../ITypeShader.h"


namespace ShaderCollection {
	class VertexShader	:	public	ITypeShader {
	private:
		ID3D11VertexShader*	m_pVertexShader;
		ID3D11InputLayout*	m_pInputLayout;

	public:
		VertexShader(
			LPCSTR pFileName,
			LPCSTR pFunction,
			LPCSTR pVersion);
		virtual ~VertexShader();

		void Begin() override;
		void End() override;
	};

	namespace VS {
		/* ���_�V�F�[�_�쐬
		// pFileName		: �t�@�C����
		// pFunction		: �֐�
		// pVersion			: �o�[�W����
		// ppVertexShader	: ���_�V�F�[�_
		// ppInputLayout	: ���̓��C�A�E�g
		// return			: true. ���� , false. ���s
		*/
		bool CreateVertexShader(
			LPCSTR pFileName,
			LPCSTR pFunction,
			LPCSTR pVersion,
			ID3D11VertexShader** ppVertexShader,
			ID3D11InputLayout** ppInputLayout);

		bool CreateInputLayout(
			ID3DBlob* pCompiled,
			ID3D11InputLayout** ppInputLayout);
	}
}