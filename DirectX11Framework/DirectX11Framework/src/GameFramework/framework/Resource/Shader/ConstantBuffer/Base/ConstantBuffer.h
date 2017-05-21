// シェーダ用コンスタントバッファー
// 2017.05.14	: プログラム作成
// author		: SyunMizuno


#pragma once


#include	<d3d11.h>
#include	"../../../../Convert/Convert.h"


namespace MSLib {
	namespace ShaderCollection {

		class Buffer;

		class ConstantBuffer {
		protected:
			// スロットの番号
			int m_ResourceNumber;
			Buffer* m_pBuffer;

		public:
			ConstantBuffer(int resourceNum);
			virtual ~ConstantBuffer();

			virtual void Set() = 0;

			virtual bool Create() = 0;
		};


		/* コンスタントバッファー作成
		// ppBuffer	:
		// size		:
		*/
		bool CreateConstantBuffer(
			ID3D11Buffer** ppBuffer,
			size_t size);


		class Buffer {
		private:
			ID3D11Buffer*	m_pBuffer;

			D3D11_MAPPED_SUBRESOURCE pData;
			size_t m_size;

		public:
			explicit Buffer(size_t size);
			~Buffer();
			void Update(const void* pSrc);

			ID3D11Buffer* buf() { return m_pBuffer; }
		};

	}
}