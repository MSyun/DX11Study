// テクスチャ
// 2017.04.24	: プログラム作成
// author		: SyunMizuno

#pragma once

#include	"../Base/IResource.h"
#include	<d3dx11.h>


namespace MSLib {

	class Texture : public IResource {
	protected:
		// テクスチャの設定が入ったもの
		D3D11_SAMPLER_DESC		m_Sampler;

		// 上のを加工したもの
		ID3D11SamplerState*		m_pSampleLinear;

		// テクスチャ
		ID3D11ShaderResourceView*	m_pTexture;

	public:
		Texture();
		virtual ~Texture();

		/* リソースを作成
		// name	: ファイルディレクトリ
		*/
		bool Create(const std::string& name) override;

		/* リソースを削除 */
		void Delete() override;

		/* 情報を設定
		// samp	: サンプラーの設定
		*/
		void SetInfo(const D3D11_SAMPLER_DESC& samp);

		/* サンプルステートを取得
		// return	; サンプラー
		*/
		ID3D11SamplerState* GetSample() const;

		/* テクスチャを取得
		// return	: テクスチャ
		*/
		ID3D11ShaderResourceView* GetTexture() const;

	protected:
		/* デフォルトの情報を設定 */
		void SetDefaultInfo();
	};

}