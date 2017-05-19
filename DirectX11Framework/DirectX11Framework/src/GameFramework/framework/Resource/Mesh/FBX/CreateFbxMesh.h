// ���b�V��
// 2017.05. 2	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	"../../Base/IResource.h"
#include	<fbxsdk.h>
#include	"../../Texture/Texture.h"
#include	<vector>
#include	"../../../Convert/Convert.h"
#include	"Analyzer/UVAnalyzer.h"
#include	"Analyzer/MaterialAnalyzer.h"


namespace MSLib {

	class CreateFbxMesh {
	protected:
#pragma region variable

		typedef struct _VERTEX_INFO {
			Vector3 vVertex;
			Vector3 vNormal;
			Vector2 vUV;
		} VERTEX_INFO;

		typedef struct _MATERIAL_INFO {
			Vector4	vDiffuse;
			Vector4	vAmbient;
			Vector4	vSpecular;
			Vector4	vEmissive;
			float	fPower;
		} MATERIAL_INFO;

		typedef struct _POLYGON_INFO {
			TCHAR MaterialName[512];
			MATERIAL_INFO* Material;
			TCHAR TexturePath[512];
			Texture* Texture;

			int VertexNum;			// ���_��
			int* VertexIndex;		// ���_�C���f�b�N�X
			VERTEX_INFO* Vertexes;	// ���_���
		} POLYGON_INFO;

		string					m_MeshName;
		UINT*					m_Indexes;		// �C���f�b�N�X�o�b�t�@
		UINT					m_IndexCount;	// �C���f�b�N�X�o�b�t�@��
		ID3D11Buffer*			m_VertexBuffer;	// ���_�o�b�t�@
		ID3D11Buffer*			m_IndexBuffer;	// �C���f�b�N�X�o�b�t�@
		vector<POLYGON_INFO>	m_Polygon;

		int m_PolygonNum;		// ���|���S����
		int m_PolygonVertexNum;	// ���|���S�����_�C���f�b�N�X��
		int* m_IndexAry;		// ��̒��g

		int m_ControlNum;		// �R���g���[���_�̐�
		Vector4* m_vControlAry;	// �R���g���[���_�z��

		int m_NormalNum;
		Vector4* m_pNormalAry;

		vector<UVAnalyzer*> m_UV;

		int m_MaterialNum;
		vector<MaterialAnalyzer*> m_Material;

#pragma endregion

	public:
#pragma region method

		CreateFbxMesh();
		virtual ~CreateFbxMesh();

		/* ���\�[�X���쐬
		// name	: �t�@�C���f�B���N�g��
		*/
		bool Create(const string name);

		/* ���\�[�X���폜 */
		void Delete();

#pragma endregion

	private:
		void RecursiveNode(FbxNode* pNode);
		void MeshAnalyze(FbxMesh* pMesh);
		void AnalyzeCoordinate(FbxMesh* pMesh);
		void AnalyzeNormal(FbxMesh* pMesh);
		void AnalyzeUV(FbxMesh* pMesh);
		void AnalyzeMaterial(FbxMesh* pMesh);
	};

}