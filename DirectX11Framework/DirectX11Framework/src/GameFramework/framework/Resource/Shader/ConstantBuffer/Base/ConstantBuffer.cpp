// シェーダ用コンスタントバッファー
// 2017.05.14	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBuffer.h"
#include	"../../../../Graphic/Graphics.h"
#include	"../../../Base/IResource.h"
#include	"../../../../Utility/System/SystemUtility.h"



namespace ShaderCollection {
	namespace Buffer {

		ConstantBuffer::ConstantBuffer() :
			m_pBuffer(nullptr)
		{
//			Create();
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

		void ConstantBuffer::EndPass() {
			auto context = Graphics::GetDevice();
			memcpy_s(pData.pData, pData.RowPitch, (void*)(&m_type), sizeof(m_type));
			context->Unmap(m_pBuffer, 0);

			context->VSSetConstantBuffers(0, 1, &m_pBuffer);
			context->PSSetConstantBuffers(0, 1, &m_pBuffer);
		}

		SIMPLESHADER_CONSTANT_BUFFER* ConstantBuffer::GetSetting() {
			return &m_type;
		}

		bool ConstantBuffer::Create() {
			if (!CreateConstantBuffer(
				&m_pBuffer,
				sizeof(SIMPLESHADER_CONSTANT_BUFFER)))
				return false;

			return true;
		}


		/*									//
		//	コンスタントバッファー作成		//
		//									*/
		bool CreateConstantBuffer(
			ID3D11Buffer** ppBuffer,
			size_t size)
		{
			D3D11_BUFFER_DESC cbuffer;
			cbuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbuffer.ByteWidth = size;
			cbuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbuffer.MiscFlags = 0;
			cbuffer.StructureByteStride = 0;
			cbuffer.Usage = D3D11_USAGE_DYNAMIC;

			HRESULT hr = IResource::GetDevice()->CreateBuffer(&cbuffer, nullptr, ppBuffer);
			if (FAILED(hr))
				return false;

			return true;
		}
	}
}