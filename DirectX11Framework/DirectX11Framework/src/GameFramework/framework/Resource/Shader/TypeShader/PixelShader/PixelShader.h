// �s�N�Z���V�F�[�_
// 2017.05.14	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	<d3d11.h>
#include	"../ITypeShader.h"


namespace ShaderCollection {
	class PixelShader	:	public	ITypeShader {
	private:
		ID3D11PixelShader*	m_pPixelShader;

	public:
		PixelShader(
			LPCSTR pFileName,
			LPCSTR pFunction,
			LPCSTR pVersion);
		virtual ~PixelShader();

		void Begin() override;
		void End() override;
	};

	namespace PS {
		/* �s�N�Z���V�F�[�_�쐬
		// pFileName		: �t�@�C����
		// pFunction		: �֐�
		// pVersion			: �o�[�W����
		// ppPixelShader	: �s�N�Z���V�F�[�_
		// return			: true. ���� , false. ���s
		*/
		bool CreatePixelShader(
			LPCSTR pFileName,
			LPCSTR pFunction,
			LPCSTR pVersion,
			ID3D11PixelShader** ppPixelShader);
	}
}