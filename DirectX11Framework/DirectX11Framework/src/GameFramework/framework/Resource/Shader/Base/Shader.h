// シェーダ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno


#pragma once


#include	"../../Base/IResource.h"
#include	"../../../Convert/Convert.h"



class Shader	:	public	IResource {
private:
	struct SIMPLESHADER_CONSTANT_BUFFER {
		Matrix	mWorld;
		Matrix	mWVP;
		Vector4	vLightDir;
		Vector4	vDiffuse;
		Vector4	vEye;
	};


	ID3D11InputLayout*	m_pVertexLayout;
	ID3D11VertexShader*	m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;

	ID3D11Buffer*		m_pConstantBuffer;

public:
	Shader();
	virtual ~Shader();

	bool Create(const string name) override;
	void Delete() override;

	ID3D11InputLayout* GetVertexLayout() { return m_pVertexLayout; }
	ID3D11VertexShader* GetVertexShader() { return m_pVertexShader; }
	ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }
	ID3D11Buffer* GetConstantBuffer() { return m_pConstantBuffer; }

private:
	/* 頂点シェーダ作成
	// fileName	: ファイル名
	*/
	bool CreateVertexShader(const string fileName);

	/* ピクセルシェーダ作成
	// fileName	: ファイル名
	*/
	bool CreatePixelShader(const string fileName);

	/* 頂点インプットレイアウト作成
	// pCompiled	: 頂点ブロブ
	*/
	bool CreateInputLayout(ID3DBlob* pCompiled);

	/* コンスタントバッファー作成 */
	bool CreateConstantBuffer();
};