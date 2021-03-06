// テクスチャ
// 2017.04.24	: プログラム作成
// author		: SyunMizuno

#include	"Texture.h"
#include	"../../Utility/System/SystemUtility.h"
#include	"../../Path/Path.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	Texture::Texture() :
		m_pSampleLinear(nullptr),
		m_pTexture(nullptr)
	{
		SetDefaultInfo();
	}


	Texture::~Texture() {
		Delete();
	}


	/*									//
	//			リソースを作成			//
	//									*/
	bool Texture::Create(const std::string& name) {
		Delete();

		// 拡張子を抽出
		std::string extension = Path::GetExtension(name);
		if (extension == "tga") {
			Debug::Log("拡張子が " + extension + " なので生成できません");
			return true;
		}

		if (extension == "sph") {
			Debug::Log("拡張子が " + extension + " なので生成できません");
			return true;
		}

		// テクスチャ―作成
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
			GetDevice(),
			name.c_str(),
			NULL,
			NULL,
			&m_pTexture,
			NULL);
		if (FAILED(hr))
			return false;

		return true;
	}


	/*									//
	//			リソースを削除			//
	//									*/
	void Texture::Delete() {
		SAFE_RELEASE(m_pTexture);
		SAFE_RELEASE(m_pSampleLinear);
	}


	/*									//
	//			情報を設定				//
	//									*/
	void Texture::SetInfo(const D3D11_SAMPLER_DESC& samp) {
		m_Sampler.AddressU = samp.AddressU;
		m_Sampler.AddressV = samp.AddressV;
		m_Sampler.AddressW = samp.AddressW;
		for (int i = 0; i < 4; ++ i)
			m_Sampler.BorderColor[i] = samp.BorderColor[i];
		m_Sampler.ComparisonFunc = samp.ComparisonFunc;
		m_Sampler.Filter = samp.Filter;
		m_Sampler.MaxAnisotropy = samp.MaxAnisotropy;
		m_Sampler.MaxLOD = samp.MaxLOD;
		m_Sampler.MinLOD = samp.MinLOD;
		m_Sampler.MipLODBias = samp.MipLODBias;

		GetDevice()->CreateSamplerState(&m_Sampler, &m_pSampleLinear);
	}


	/*									//
	//		デフォルトの情報を設定		//
	//									*/
	void Texture::SetDefaultInfo() {
		ZeroMemory(&m_Sampler, sizeof(D3D11_SAMPLER_DESC));
		m_Sampler.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		m_Sampler.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		m_Sampler.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		m_Sampler.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		m_Sampler.MipLODBias = 0;
		m_Sampler.MaxAnisotropy = 16;
		m_Sampler.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		m_Sampler.MinLOD = 0;
		m_Sampler.MaxLOD = D3D11_FLOAT32_MAX;

		GetDevice()->CreateSamplerState(&m_Sampler, &m_pSampleLinear);
	}


	/*									//
	//		サンプラーステートを取得	//
	//									*/
	ID3D11SamplerState* Texture::GetSample() const {
		return m_pSampleLinear;
	}


	/*									//
	//		テクスチャーを取得			//
	//									*/
	ID3D11ShaderResourceView* Texture::GetTexture() const {
		return m_pTexture;
	}

}