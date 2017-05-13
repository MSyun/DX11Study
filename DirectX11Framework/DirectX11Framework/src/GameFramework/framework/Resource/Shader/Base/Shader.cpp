// シェーダ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno


#include	"Shader.h"
#include	<tchar.h>
#include	<D3DX11.h>
#include	"../../../Utility/System/SystemUtility.h"



Shader::Shader() :
	m_pVertexShader(nullptr),
	m_pPixelShader(nullptr)
{

}

Shader::~Shader() {

}

bool Shader::Create(const string name) {
	if (!CreateVertexShader(name))
		return false;

	if (!CreatePixelShader(name))
		return false;

	if (!CreateConstantBuffer())
		return false;

	return true;
}

void Shader::Delete() {
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pVertexLayout);
}


/*									//
//			頂点シェーダ作成		//
//									*/
bool Shader::CreateVertexShader(const string fileName) {
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	HRESULT hr;

	hr = D3DX11CompileFromFile(
		fileName.c_str(),
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		0,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL);
	if (FAILED(hr)) {
		MessageBox(0, (LPCTSTR)pErrors->GetBufferPointer(), _T("ERROR"), MB_OK);
		goto MISS;
	}
	SAFE_RELEASE(pErrors);

	hr = GetDevice()->CreateVertexShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&m_pVertexShader);
	if (FAILED(hr)) {
		MessageBox(0, "バーテックスシェーダ作成失敗", _T("ERROR"), MB_OK);
		goto MISS;
	}

	if (!CreateInputLayout(pCompiledShader))
		goto MISS;

	SAFE_RELEASE(pCompiledShader);

	return true;


MISS:
	SAFE_RELEASE(pCompiledShader);
	SAFE_RELEASE(pErrors);

	return false;
}


/*									//
//	頂点インプットレイアウト作成	//
//									*/
bool Shader::CreateInputLayout(ID3DBlob* pCompiled) {
	// 頂点インプットレイアウトを定義
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL",		0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	24,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	// 頂点インプットレイアウトを作成
	HRESULT hr = GetDevice()->CreateInputLayout(
		layout,
		numElements,
		pCompiled->GetBufferPointer(),
		pCompiled->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))
		return false;

	return true;
}


/*									//
//		ピクセルシェーダ作成		//
//									*/
bool Shader::CreatePixelShader(const string fileName) {
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	HRESULT hr;

	hr = D3DX11CompileFromFile(
		fileName.c_str(),
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		0,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL);
	if (FAILED(hr)) {
		MessageBox(0, (LPCTSTR)pErrors->GetBufferPointer(), _T("ERROR"), MB_OK);
		goto MISS;
	}
	SAFE_RELEASE(pErrors);

	hr = GetDevice()->CreatePixelShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&m_pPixelShader);
	if (FAILED(hr)) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, "ピクセルシェーダ作成失敗", _T("ERROR"), MB_OK);
		goto MISS;
	}
	SAFE_RELEASE(pCompiledShader);

	return true;


MISS:
	SAFE_RELEASE(pCompiledShader);
	SAFE_RELEASE(pErrors);

	return false;
}


/*									//
//	コンスタントバッファー作成		//
//									*/
bool Shader::CreateConstantBuffer() {
	D3D11_BUFFER_DESC cbuffer;
	cbuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbuffer.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cbuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbuffer.MiscFlags = 0;
	cbuffer.StructureByteStride = 0;
	cbuffer.Usage = D3D11_USAGE_DYNAMIC;

	HRESULT hr = GetDevice()->CreateBuffer(&cbuffer, NULL, &m_pConstantBuffer);
	if (FAILED(hr))
		return false;

	return true;
}