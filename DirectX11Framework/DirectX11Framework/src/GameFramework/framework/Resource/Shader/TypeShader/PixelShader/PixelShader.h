// ピクセルシェーダ
// 2017.05.14	: プログラム作成
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
		/* ピクセルシェーダ作成
		// pFileName		: ファイル名
		// pFunction		: 関数
		// pVersion			: バージョン
		// ppPixelShader	: ピクセルシェーダ
		// return			: true. 成功 , false. 失敗
		*/
		bool CreatePixelShader(
			LPCSTR pFileName,
			LPCSTR pFunction,
			LPCSTR pVersion,
			ID3D11PixelShader** ppPixelShader);
	}
}