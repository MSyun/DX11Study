// ���b�V��
// 2017.05. 2	: �v���O�����쐬
// author		: SyunMizuno


#include	"CreateFbxMesh.h"
#include	"../../../Debug/Debug.h"
#include	"../../../Utility/System/SystemUtility.h"


/*									//
//			�R���X�g���N�^			//
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
//			�f�X�g���N�^			//
//									*/
CreateFbxMesh::~CreateFbxMesh() {
	Delete();
}


/*									//
//			���\�[�X���쐬			//
//									*/
bool CreateFbxMesh::Create(const string name) {
	Delete();

	// �ǂݍ���
	FbxManager* manager = FbxManager::Create();
	FbxImporter* impoter = FbxImporter::Create(manager, "");
	if (!impoter->Initialize(name.c_str())) {
		Debug::LogError("�ǂݍ��ݎ��s");
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
//			���\�[�X���폜			//
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
			MeshAnalyze((FbxMesh*)pAttr);	// ���b�V�����쐬
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
	m_MeshName = pMesh->GetName();					// ���b�V����
	m_PolygonNum = pMesh->GetPolygonCount();			// ���|���S����
	m_PolygonVertexNum = pMesh->GetPolygonVertexCount();	// �|���S�����_�C���f�b�N�X��
	m_IndexAry = NEW int[m_PolygonVertexNum];		// �|���S�����_�C���f�b�N�X�z��
	memcpy(m_IndexAry, pMesh->GetPolygonVertices(), sizeof(int) * m_PolygonVertexNum);

	// �|���S���̐ݒ�
	for (int i = 0; i < m_PolygonNum; ++i) {
		POLYGON_INFO* polygon = NEW POLYGON_INFO;
		polygon->VertexNum = pMesh->GetPolygonSize(i);	// �|���S���̒��_��
		polygon->Vertexes = NEW VERTEX_INFO[polygon->VertexNum];
		polygon->VertexIndex = NEW int[polygon->VertexNum];
		// ���_�̐ݒ�
		for (int n = 0; n < polygon->VertexNum; ++n) {
			// �|���S��i���\������n�Ԗڂ̒��_�̃C���f�b�N�X�ԍ�
			polygon->VertexIndex[n] = pMesh->GetPolygonVertex(i, n);
			continue;
		}
	}

	// ���_���̉��
	AnalyzeCoordinate(pMesh);

	// �@���̉��
	AnalyzeNormal(pMesh);

	// UV�̉��
	AnalyzeUV(pMesh);

	// �}�e���A���̉��
	AnalyzeMaterial(pMesh);
}


void CreateFbxMesh::AnalyzeCoordinate(FbxMesh* pMesh) {
	m_ControlNum = pMesh->GetControlPointsCount();	// ���_��
	m_vControlAry = NEW Vector4[m_ControlNum];

	// �R�s�[
	FbxVector4* src = pMesh->GetControlPoints();		// ���_���W�z��
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

		// �@���̐��E�C���f�b�N�X
		m_NormalNum = normalElem->GetDirectArray().GetCount();
		int indexNum = normalElem->GetIndexArray().GetCount();
		m_pNormalAry = new Vector4[m_NormalNum];

		// �}�b�s���O���[�h�E���t�@�����X���[�h�擾
		FbxLayerElement::EMappingMode mappingMode = normalElem->GetMappingMode();
		FbxLayerElement::EReferenceMode refMode = normalElem->GetReferenceMode();

		if (mappingMode == FbxLayerElement::eByPolygonVertex) {
			if (refMode == FbxLayerElement::eDirect) {
				// ���ڎ擾
				for (int n = 0; n < m_NormalNum; ++n) {
					for (int l = 0; l < 4; ++l)
						m_pNormalAry[i].e[l] = (float)normalElem->GetDirectArray().GetAt(i)[l];
				}
			}
		} else
			if (mappingMode == FbxLayerElement::eByControlPoint) {
				if (refMode == FbxLayerElement::eDirect) {
					// ���ڎ擾
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

	// �}�e���A���̐�
	m_MaterialNum = node->GetMaterialCount();
	if (m_MaterialNum == 0)
		return;

	// �}�e���A�������擾
	for (int i = 0; i < m_MaterialNum; ++i) {
		FbxSurfaceMaterial* material = node->GetMaterial(i);
		if (!material)	continue;

		// �}�e���A���̉��
		MaterialAnalyzer* matAnalyzer = new MaterialAnalyzer;
		m_Material.push_back(matAnalyzer);
		matAnalyzer->Analyze(material);
	}
}