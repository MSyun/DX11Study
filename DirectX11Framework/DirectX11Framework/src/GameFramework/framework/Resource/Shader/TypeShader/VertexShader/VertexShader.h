// バーテックスシェーダ
// 2017.05.14	: プログラム作成
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
		/* 頂点シェーダ作成
		// pFileName		: ファイル名
		// pFunction		: 関数
		// pVersion			: バージョン
		// ppVertexShader	: 頂点シェーダ
		// ppInputLayout	: 入力レイアウト
		// return			: true. 成功 , false. 失敗
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