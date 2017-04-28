// �e�N�X�`��
// 2017.04.24	: �v���O�����쐬
// author		: SyunMizuno


#include	"Texture.h"
#include	"../../Utility/System/SystemUtility.h"



/*									//
//			�R���X�g���N�^			//
//									*/
Texture::Texture() :
	m_pSampleLinear(nullptr),
	m_pTexture(nullptr)
{
	SetDefaultInfo();
}


/*									//
//			�f�X�g���N�^			//
//									*/
Texture::~Texture() {
	Delete();
}


/*									//
//			���\�[�X���쐬			//
//									*/
bool Texture::Create(const string name) {
	Delete();

	// �e�N�X�`���\�쐬
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		GetDevice(),
		name.c_str(),
		NULL,
		NULL,
		&m_pTexture,
		NULL);
	if (SUCCEEDED(hr))
		return true;

	return false;
}


/*									//
//			���\�[�X���폜			//
//									*/
void Texture::Delete() {
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSampleLinear);
}


/*									//
//			����ݒ�				//
//									*/
void Texture::SetInfo(const D3D11_SAMPLER_DESC& samp) {
	m_Sampler.AddressU = samp.AddressU;
	m_Sampler.AddressV = samp.AddressV;
	m_Sampler.AddressW = samp.AddressW;
	for(int i = 0; i < 4; ++ i)
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
//		�f�t�H���g�̏���ݒ�		//
//									*/
void Texture::SetDefaultInfo() {
	ZeroMemory(&m_Sampler, sizeof(D3D11_SAMPLER_DESC));
	m_Sampler.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	m_Sampler.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	m_Sampler.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	m_Sampler.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GetDevice()->CreateSamplerState(&m_Sampler, &m_pSampleLinear);
}


/*									//
//		�T���v���[�X�e�[�g���擾	//
//									*/
ID3D11SamplerState* Texture::GetSample() const {
	return m_pSampleLinear;
}


/*									//
//		�e�N�X�`���[���擾			//
//									*/
ID3D11ShaderResourceView* Texture::GetTexture() const {
	return m_pTexture;
}