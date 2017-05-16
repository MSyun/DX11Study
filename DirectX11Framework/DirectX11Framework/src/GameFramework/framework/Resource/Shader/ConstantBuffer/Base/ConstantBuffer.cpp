// シェーダ用コンスタントバッファー
// 2017.05.14	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBuffer.h"
#include	"../../../../Graphic/Graphics.h"
#include	"../../../Base/IResource.h"
#include	"../../../../Utility/System/SystemUtility.h"



namespace ShaderCollection {
	namespace Buffer {

		ConstantBuffer::ConstantBuffer(int resourceNum) :
			m_pBuffer(nullptr),
			m_ResourceNumber(resourceNum)
		{
		}

		ConstantBuffer::~ConstantBuffer() {
			SAFE_RELEASE(m_pBuffer);
		}

		//	void ConstantBuffer::Update(const void* srcPtr) {
		//		Graphics::GetDevice()->UpdateSubresource(
		//			m_pBuffer,
		//			0,
		//			nullptr,
		////			srcPtr,
		//			&m_type,
		//			0,
		//			0);
		//		Graphics::GetDevice()->VSSetConstantBuffers(0, 1, &m_pBuffer);
		//		Graphics::GetDevice()->PSSetConstantBuffers(0, 1, &m_pBuffer);
		//	}

		void ConstantBuffer::BeginPass() {
			Graphics::GetDevice()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		}


		/*									//
		//		コンスタントバッファー作成	//
		//									*/
		bool CreateConstantBuffer(
			D3D11_BUFFER_DESC* desc,
			ID3D11Buffer** ppBuffer,
			size_t size)
		{
			desc->BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc->ByteWidth = size;
			desc->CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc->MiscFlags = 0;
			desc->StructureByteStride = 0;
			desc->Usage = D3D11_USAGE_DYNAMIC;

			HRESULT hr = IResource::GetDevice()->CreateBuffer(desc, nullptr, ppBuffer);
			if (FAILED(hr))
				return false;

			return true;
		}
	}
}