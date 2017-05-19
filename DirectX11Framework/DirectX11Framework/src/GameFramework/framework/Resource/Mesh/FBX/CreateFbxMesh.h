// メッシュ
// 2017.05. 2	: プログラム作成
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

			int VertexNum;			// 頂点数
			int* VertexIndex;		// 頂点インデックス
			VERTEX_INFO* Vertexes;	// 頂点情報
		} POLYGON_INFO;

		string					m_MeshName;
		UINT*					m_Indexes;		// インデックスバッファ
		UINT					m_IndexCount;	// インデックスバッファ数
		ID3D11Buffer*			m_VertexBuffer;	// 頂点バッファ
		ID3D11Buffer*			m_IndexBuffer;	// インデックスバッファ
		vector<POLYGON_INFO>	m_Polygon;

		int m_PolygonNum;		// 総ポリゴン数
		int m_PolygonVertexNum;	// 総ポリゴン頂点インデックス数
		int* m_IndexAry;		// 上の中身

		int m_ControlNum;		// コントロール点の数
		Vector4* m_vControlAry;	// コントロール点配列

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

		/* リソースを作成
		// name	: ファイルディレクトリ
		*/
		bool Create(const string name);

		/* リソースを削除 */
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