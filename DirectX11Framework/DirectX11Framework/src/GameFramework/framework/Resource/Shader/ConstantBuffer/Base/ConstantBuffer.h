// シェーダ用コンスタントバッファー
// 2017.05.14	: プログラム作成
// author		: SyunMizuno


#pragma once


#include	<d3d11.h>
#include	"../../../../Convert/Convert.h"


namespace ShaderCollection {
	namespace Buffer {

		struct SIMPLESHADER_CONSTANT_BUFFER {
			Matrix	mWorld;
			Matrix	mWVP;
			Vector4	vLightDir;
			Vector4	vEye;
		};


		class ConstantBuffer {
		protected:
			ID3D11Buffer*	m_pBuffer;
			SIMPLESHADER_CONSTANT_BUFFER m_type;

			D3D11_MAPPED_SUBRESOURCE pData;

		public:
			ConstantBuffer();
			virtual ~ConstantBuffer();

			//		void Update(const void* srcPtr);
			virtual void BeginPass();
			virtual void EndPass();

			SIMPLESHADER_CONSTANT_BUFFER* GetSetting();

		//protected:
			virtual bool Create();
		};


		/* コンスタントバッファー作成
		// ppBuffer	:
		// size		:
		*/
		bool CreateConstantBuffer(
			ID3D11Buffer** ppBuffer,
			size_t size);

	}
}