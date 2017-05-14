// バーテックスシェーダ
// 2017.05.14	: プログラム作成
// author		: SyunMizuno


#include	"VertexShader.h"
#include	"../../../Base/IResource.h"
#include	"../../Base/Shader.h"
#include	"../../../../Utility/System/SystemUtility.h"
#include	"../../../../Graphic/Graphics.h"


namespace ShaderCollection {
	VertexShader::VertexShader(
		LPCSTR pFileName,
		LPCSTR pFunction,
		LPCSTR pVersion)
	{
		if (!VS::CreateVertexShader(
			pFileName,
			pFunction,
			pVersion,
			&m_pVertexShader,
			&m_pInputLayout))
			return;

		m_FileName = pFileName;
		m_Function = pFunction;
		m_Version = pVersion;
	}

	VertexShader::~VertexShader() {
		SAFE_RELEASE(m_pVertexShader);
		SAFE_RELEASE(m_pInputLayout);
	}

	void VertexShader::Begin() {
		auto context = GetGraphics()->GetDevice();
		context->VSSetShader(m_pVertexShader, nullptr, 0);
		context->IASetInputLayout(m_pInputLayout);
	}

	void VertexShader::End() {
		auto context = GetGraphics()->GetDevice();
		context->VSSetShader(nullptr, nullptr, 0);
		context->IASetInputLayout(nullptr);
	}

	namespace VS {
		/*									//
		//			頂点シェーダ作成		//
		//									*/
		bool CreateVertexShader(
			LPCSTR pFileName,
			LPCSTR pFunction,
			LPCSTR pVersion,
			ID3D11VertexShader** ppVertexShader,
			ID3D11InputLayout** ppInputLayout)
		{
			ID3DBlob* pBlob = nullptr;
			HRESULT hr;

			if (!CompileFromFileToBlob(
				pFileName,
				pFunction,
				pVersion,
				&pBlob))
				goto MISS;

			hr = IResource::GetDevice()->CreateVertexShader(
				pBlob->GetBufferPointer(),
				pBlob->GetBufferSize(),
				nullptr,
				ppVertexShader);
			if (FAILED(hr)) {
				MessageBox(0, "バーテックスシェーダ作成失敗", ("ERROR"), MB_OK);
				goto MISS;
			}

			if (!CreateInputLayout(pBlob, ppInputLayout))
				goto MISS;

			SAFE_RELEASE(pBlob);

			return true;


		MISS:
			SAFE_RELEASE(pBlob);

			return false;
		}


		/*									//
		//	頂点インプットレイアウト作成	//
		//									*/
		bool CreateInputLayout(
			ID3DBlob* pCompiled,
			ID3D11InputLayout** ppInputLayout) {
			// 頂点インプットレイアウトを定義
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
				{ "NORMAL",		0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
				{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	24,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
			};
			UINT numElements = sizeof(layout) / sizeof(layout[0]);

			// 頂点インプットレイアウトを作成
			HRESULT hr = IResource::GetDevice()->CreateInputLayout(
				layout,
				numElements,
				pCompiled->GetBufferPointer(),
				pCompiled->GetBufferSize(),
				ppInputLayout);
			if (FAILED(hr))
				return false;

			return true;
		}
	}
}