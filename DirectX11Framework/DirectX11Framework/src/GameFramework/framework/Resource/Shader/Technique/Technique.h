// テクニック
// 2017.05.12	: プログラム作成
// author		: SyunMizuno


#pragma once


#include	"../TypeShader/VertexShader/VertexShader.h"
#include	"../TypeShader/PixelShader/PixelShader.h"


namespace MSLib {
	namespace ShaderCollection {

		template<
			class VS,
			class PS>
			class Technique {
			public:
				VertexShader*	m_pVShader;
				PixelShader*	m_pPShader;

			public:
				Technique() :
					m_pVShader(nullptr),
					m_pPShader(nullptr)
				{
					m_pVShader = new VS;
					m_pPShader = new PS;
				}
				~Technique() {
					delete m_pVShader;
					delete m_pPShader;
				}

				void Begin() {
					m_pVShader->Begin();
					m_pPShader->Begin();
				}

				void End() {
					m_pVShader->End();
					m_pPShader->End();
				}
		};

	}
}