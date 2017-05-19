// UV解析者
// 2017.05. 4	: プログラム作成
// author		: SyunMizuno



#include	"UVAnalyzer.h"


namespace MSLib {

	UVAnalyzer::UVAnalyzer() {

	}


	UVAnalyzer::~UVAnalyzer() {

	}


	bool UVAnalyzer::Analyze(FbxMesh* mesh) {
		// メッシュに登録されているUVを格納
		int layerCount = mesh->GetLayerCount();
		for (int i = 0; i < layerCount; ++i) {
			FbxLayer* layer = mesh->GetLayer(i);
			FbxLayerElementUV* elem = layer->GetUVs();
			if (!elem)
				continue;

			// UVの数・インデックス
			int UVNum = elem->GetDirectArray().GetCount();
			int indexNum = elem->GetIndexArray().GetCount();
			m_UVInfo.Size = UVNum > indexNum ? UVNum : indexNum;
			m_UVInfo.Buffer = new Vector2[m_UVInfo.Size];

			// マッピングモード・リファレンスモード別のUV取得
			FbxLayerElement::EMappingMode	mappingMode = elem->GetMappingMode();
			FbxLayerElement::EReferenceMode	refMode = elem->GetReferenceMode();

			if (mappingMode == FbxLayerElement::eByPolygonVertex) {
				// 直接取得
				if (refMode == FbxLayerElement::eDirect) {
					for (int n = 0; n < m_UVInfo.Size; ++ n)
						for (int l = 0; l < 2; ++ l)
							m_UVInfo.Buffer[n].e[l] = (float)elem->GetDirectArray().GetAt(n)[l];
				} else
					if (refMode == FbxLayerElement::eIndexToDirect) {
						// インデックスから取得
						for (int n = 0; n < m_UVInfo.Size; ++ n) {
							int index = elem->GetIndexArray().GetAt(n);
							m_UVInfo.Buffer[n].x = (float)elem->GetDirectArray().GetAt(index)[0];
							m_UVInfo.Buffer[n].y = (float)elem->GetDirectArray().GetAt(index)[1];
						}
					}
			}

			// 現バージョンではとりあえずセカンドUV以降を格納しない事にします
			return true;
		}

		return false;
	}


	bool UVAnalyzer::Analyze(FbxLayer* layer) {
		bool isEffective = false;
		if (SetPropertyUV(layer->GetUVs(FbxLayerElement::eTextureAmbient), m_AmbientUV))	isEffective = true;
		if (SetPropertyUV(layer->GetUVs(FbxLayerElement::eTextureDiffuse), m_DiffuseUV))	isEffective = true;
		if (SetPropertyUV(layer->GetUVs(FbxLayerElement::eTextureSpecular), m_SpecularUV))	isEffective = true;
		if (SetPropertyUV(layer->GetUVs(FbxLayerElement::eTextureEmissive), m_EmissiveUV))	isEffective = true;
		return isEffective;
	}


	bool UVAnalyzer::SetPropertyUV(FbxLayerElementUV* elem, UVInfo& uvInfo) {
		if (!elem)
			return false;

		// UVの数・インデックス
		int UVNum = elem->GetDirectArray().GetCount();
		int indexNum = elem->GetIndexArray().GetCount();
		m_UVInfo.Size = UVNum > indexNum ? UVNum : indexNum;
		m_UVInfo.Buffer = new Vector2[m_UVInfo.Size];

		// マッピングモード・リファレンスモード別のUV取得
		FbxLayerElement::EMappingMode	mappingMode = elem->GetMappingMode();
		FbxLayerElement::EReferenceMode	refMode = elem->GetReferenceMode();

		if (mappingMode == FbxLayerElement::eByPolygonVertex) {
			// 直接取得
			if (refMode == FbxLayerElement::eDirect) {
				for (int n = 0; n < m_UVInfo.Size; ++ n)
					for (int l = 0; l < 2; ++ l)
						m_UVInfo.Buffer[n].e[l] = (float)elem->GetDirectArray().GetAt(n)[l];
			} else
				if (refMode == FbxLayerElement::eIndexToDirect) {
					// インデックスから取得
					for (int n = 0; n < m_UVInfo.Size; ++ n) {
						int index = elem->GetIndexArray().GetAt(n);
						m_UVInfo.Buffer[n].x = (float)elem->GetDirectArray().GetAt(index)[0];
						m_UVInfo.Buffer[n].y = (float)elem->GetDirectArray().GetAt(index)[1];
					}
				}
		}

		return true;
	}


	int UVAnalyzer::GetUVNum() const {
		return m_UVInfo.Size;
	}


	UVAnalyzer::UVInfo& UVAnalyzer::GetUVInfo() {
		return m_UVInfo;
	}

}