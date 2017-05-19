// ピクセルシェーダ
// 2017.05.14	: プログラム作成
// author		: SyunMizuno

#include	"PixelShader.h"
#include	"../../Base/Shader.h"
#include	"../../../../Utility/System/SystemUtility.h"
#include	"../../../../Graphic/Graphics.h"


namespace MSLib {
	namespace ShaderCollection {

		PixelShader::PixelShader(
			LPCSTR pFileName,
			LPCSTR pFunction,
			LPCSTR pVersion)
		{
			if (!PS::CreatePixelShader(
				pFileName,
				pFunction,
				pVersion,
				&m_pPixelShader))
				return;

			m_FileName = pFileName;
			m_Function = pFunction;
			m_Version = pVersion;
		}

		PixelShader::~PixelShader() {
			SAFE_RELEASE(m_pPixelShader);
		}

		void PixelShader::Begin() {
			auto context = GetGraphics()->GetDevice();
			context->PSSetShader(m_pPixelShader, nullptr, 0);
		}

		void PixelShader::End() {
			auto context = GetGraphics()->GetDevice();
			context->PSSetShader(nullptr, nullptr, 0);
		}


		namespace PS {

			/*									//
			//			ピクセルシェーダ作成	//
			//									*/
			bool CreatePixelShader(
				LPCSTR pFileName,
				LPCSTR pFunction,
				LPCSTR pVersion,
				ID3D11PixelShader** ppPixelShader)
			{
				ID3DBlob* pBlob = nullptr;
				HRESULT hr;

				if (!CompileFromFileToBlob(
					pFileName,
					pFunction,
					pVersion,
					&pBlob)) {
					goto MISS;
				}

				hr = IResource::GetDevice()->CreatePixelShader(
					pBlob->GetBufferPointer(),
					pBlob->GetBufferSize(),
					nullptr,
					ppPixelShader);
				if (FAILED(hr)) {
					MessageBox(0, "ピクセルシェーダ作成失敗", ("ERROR"), MB_OK);
					goto MISS;
				}
				SAFE_RELEASE(pBlob);

				return true;


			MISS:
				SAFE_RELEASE(pBlob);

				return false;
			}

		}

	}
}