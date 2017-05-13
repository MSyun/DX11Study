// メッシュ
// 2017.05. 2	: プログラム作成
// author		: SyunMizuno


#include	"CreateFbxMesh.h"
#include	"../../../Debug/Debug.h"
#include	"../../../Utility/System/SystemUtility.h"


/*									//
//			コンストラクタ			//
//									*/
CreateFbxMesh::CreateFbxMesh() :
	m_Indexes(nullptr),
	m_IndexCount(0),
	m_VertexBuffer(nullptr),
	m_IndexBuffer(nullptr)
{
	m_MeshName.clear();
	m_Polygon.clear();
}

/*									//
//			デストラクタ			//
//									*/
CreateFbxMesh::~CreateFbxMesh() {
	Delete();
}


/*									//
//			リソースを作成			//
//									*/
bool CreateFbxMesh::Create(const string name) {
	Delete();

	// 読み込み
	FbxManager* manager = FbxManager::Create();
	FbxImporter* impoter = FbxImporter::Create(manager, "");
	if (!impoter->Initialize(name.c_str())) {
		Debug::LogError("読み込み失敗");
		return false;
	}
	FbxScene* scene = FbxScene::Create(manager, "");
	impoter->Import(scene);
	impoter->Destroy();

	// 
	FbxNode* pRootNode = scene->GetRootNode();
	RecursiveNode(pRootNode);

	return true;
}


/*									//
//			リソースを削除			//
//									*/
void CreateFbxMesh::Delete() {
	m_MeshName.clear();
	SAFE_DELETE_ARRAY(m_Indexes);
	m_IndexCount = 0;
	SAFE_RELEASE(m_VertexBuffer);
	SAFE_RELEASE(m_IndexBuffer);
	for (auto it = m_Polygon.begin(); it != m_Polygon.end(); ++it) {
		SAFE_DELETE((*it).Material);
		SAFE_DELETE((*it).Texture);
	}

	SAFE_DELETE_ARRAY(m_IndexAry);
}


void CreateFbxMesh::RecursiveNode(FbxNode* pNode) {
	FbxNodeAttribute* pAttr = pNode->GetNodeAttribute();
	if (pAttr) {
		FbxNodeAttribute::EType type = pAttr->GetAttributeType();
		switch (type) {
		case FbxNodeAttribute::eNull:
			break;

		case FbxNodeAttribute::eMesh:
			MeshAnalyze((FbxMesh*)pAttr);	// メッシュを作成
			break;

		case FbxNodeAttribute::eCamera:
			//		GetCamera(pAttr);
			break;
		}
	}

	int childNodeNum = pNode->GetChildCount();
	for (int i = 0; i < childNodeNum; ++ i) {
		FbxNode* pChild = pNode->GetChild(i);

		RecursiveNode(pChild);
	}
}


void CreateFbxMesh::MeshAnalyze(FbxMesh* pMesh) {
	m_MeshName = pMesh->GetName();					// メッシュ名
	m_PolygonNum = pMesh->GetPolygonCount();			// 総ポリゴン数
	m_PolygonVertexNum = pMesh->GetPolygonVertexCount();	// ポリゴン頂点インデックス数
	m_IndexAry = NEW int[m_PolygonVertexNum];		// ポリゴン頂点インデックス配列
	memcpy(m_IndexAry, pMesh->GetPolygonVertices(), sizeof(int) * m_PolygonVertexNum);

	// ポリゴンの設定
	for (int i = 0; i < m_PolygonNum; ++i) {
		POLYGON_INFO* polygon = NEW POLYGON_INFO;
		polygon->VertexNum = pMesh->GetPolygonSize(i);	// ポリゴンの頂点数
		polygon->Vertexes = NEW VERTEX_INFO[polygon->VertexNum];
		polygon->VertexIndex = NEW int[polygon->VertexNum];
		// 頂点の設定
		for (int n = 0; n < polygon->VertexNum; ++n) {
			// ポリゴンiを構成するn番目の頂点のインデックス番号
			polygon->VertexIndex[n] = pMesh->GetPolygonVertex(i, n);
			continue;
		}
	}

	// 頂点情報の解析
	AnalyzeCoordinate(pMesh);

	// 法線の解析
	AnalyzeNormal(pMesh);

	// UVの解析
	AnalyzeUV(pMesh);

	// マテリアルの解析
	AnalyzeMaterial(pMesh);
}


void CreateFbxMesh::AnalyzeCoordinate(FbxMesh* pMesh) {
	m_ControlNum = pMesh->GetControlPointsCount();	// 頂点数
	m_vControlAry = NEW Vector4[m_ControlNum];

	// コピー
	FbxVector4* src = pMesh->GetControlPoints();		// 頂点座標配列
	for (int i = 0; i < m_ControlNum; ++i) {
		for (int n = 0; n < 4; ++n) {
			m_vControlAry[i].e[n] = (float)src[i][n];
		}
	}
}


void CreateFbxMesh::AnalyzeNormal(FbxMesh* pMesh) {
	int layerNum = pMesh->GetLayerCount();
	for (int i = 0; i < layerNum; ++i) {
		FbxLayer* layer = pMesh->GetLayer(i);
		FbxLayerElementNormal* normalElem = layer->GetNormals();
		if (!normalElem) {
			continue;
		}

		// 法線の数・インデックス
		m_NormalNum = normalElem->GetDirectArray().GetCount();
		int indexNum = normalElem->GetIndexArray().GetCount();
		m_pNormalAry = new Vector4[m_NormalNum];

		// マッピングモード・リファレンスモード取得
		FbxLayerElement::EMappingMode mappingMode = normalElem->GetMappingMode();
		FbxLayerElement::EReferenceMode refMode = normalElem->GetReferenceMode();

		if (mappingMode == FbxLayerElement::eByPolygonVertex) {
			if (refMode == FbxLayerElement::eDirect) {
				// 直接取得
				for (int n = 0; n < m_NormalNum; ++n) {
					for (int l = 0; l < 4; ++l)
						m_pNormalAry[i].e[l] = (float)normalElem->GetDirectArray().GetAt(i)[l];
				}
			}
		} else
			if (mappingMode == FbxLayerElement::eByControlPoint) {
				if (refMode == FbxLayerElement::eDirect) {
					// 直接取得
					for (int n = 0; n < m_NormalNum; ++n) {
						for (int l = 0; l < 4; ++l)
							m_pNormalAry[i].e[l] = (float)normalElem->GetDirectArray().GetAt(i)[l];
					}
				}
			}

		break;
	}
}


void CreateFbxMesh::AnalyzeUV(FbxMesh* pMesh) {
	UVAnalyzer* uvAnalyze = NEW UVAnalyzer;
	if (uvAnalyze->Analyze(pMesh)) {
		m_UV.push_back(uvAnalyze);
	}
}


void CreateFbxMesh::AnalyzeMaterial(FbxMesh* pMesh) {
	FbxNode* node = pMesh->GetNode();
	if (!node)
		return;

	// マテリアルの数
	m_MaterialNum = node->GetMaterialCount();
	if (m_MaterialNum == 0)
		return;

	// マテリアル情報を取得
	for (int i = 0; i < m_MaterialNum; ++i) {
		FbxSurfaceMaterial* material = node->GetMaterial(i);
		if (!material)	continue;

		// マテリアルの解析
		MaterialAnalyzer* matAnalyzer = new MaterialAnalyzer;
		m_Material.push_back(matAnalyzer);
		matAnalyzer->Analyze(material);
	}
}