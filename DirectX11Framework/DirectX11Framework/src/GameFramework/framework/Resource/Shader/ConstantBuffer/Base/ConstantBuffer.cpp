// シェーダ用コンスタントバッファー
// 2017.05.14	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBuffer.h"
#include	"../../../../Graphic/Graphics.h"
#include	"../../../Base/IResource.h"
#include	"../../../../Utility/System/SystemUtility.h"
#include	"../../../../Debug/Debug.h"


namespace MSLib {
	namespace ShaderCollection {

		ConstantBuffer::ConstantBuffer(int resourceNum) :
			m_ResourceNumber(resourceNum),
			m_pBuffer(nullptr)
		{
		}

		ConstantBuffer::~ConstantBuffer() {
			SAFE_DELETE(m_pBuffer);
		}


		/*									//
		//		コンスタントバッファー作成	//
		//									*/
		bool CreateConstantBuffer(
			ID3D11Buffer** ppBuffer,
			size_t size)
		{
			D3D11_BUFFER_DESC desc;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth = size;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;
			desc.Usage = D3D11_USAGE_DEFAULT;

			HRESULT hr = IResource::GetDevice()->CreateBuffer(&desc, nullptr, ppBuffer);
			if (FAILED(hr))
				return false;

			return true;
		}


		Buffer::Buffer(size_t size) :
			m_pBuffer(nullptr)
		{
			size = size % 16 ? size + 16 - (size % 16) : size;
			CreateConstantBuffer(
				&m_pBuffer,
				size);
			m_size = size;
		}

		Buffer::~Buffer() {
			SAFE_RELEASE(m_pBuffer);
		}

		void Buffer::Update(const void* pSrc) {
			auto context = Graphics::GetDevice();
			context->UpdateSubresource(m_pBuffer, 0, nullptr, pSrc, 0, 0);
		}

	}
}