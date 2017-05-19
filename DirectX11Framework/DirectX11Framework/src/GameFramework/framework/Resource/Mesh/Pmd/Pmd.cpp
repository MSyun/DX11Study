// PMDメッシュ
// 2017.05.10	: プログラム作成
// author		: SyunMizuno


#include	"Pmd.h"
#include	<Windows.h>
#include	<stdio.h>
#include	"../../../Debug/Debug.h"
#include	"../../../Utility/System/SystemUtility.h"


namespace MSLib {

	Pmd::Pmd(const std::string& filename) :
		vertex(nullptr),
		face_vert_index(nullptr)
	{
		FILE* hFP;
		hFP = fopen(filename.c_str(), "rb");
		if (hFP != 0) {
			// ヘッダー読み込み
			fread(&header, sizeof(struct t_header), 1, hFP);

			// 頂点数読み込み
			fread(&vert_count, sizeof(vert_count), 1, hFP);

			// 頂点データ読み込み
			vertex = new t_vertex[vert_count];
			fread(vertex, sizeof(t_vertex), vert_count, hFP);

			// 面頂点リスト読み込み
			fread(&face_vert_count, sizeof(face_vert_count), 1, hFP);

			// 面頂点リストデータ読み込み
			face_vert_index = new unsigned short[face_vert_count];
			fread(face_vert_index, 2, face_vert_count, hFP);

			// マテリアル数
			fread(&material_count, sizeof(material_count), 1, hFP);

			// 面データ読み込み
			material = new t_material[material_count];
			fread(material, sizeof(t_material), material_count, hFP);

			fclose(hFP);
		} else {
			Debug::LogError("Fileを開けません");
		}
	}

	Pmd::~Pmd() {
		SAFE_DELETE_ARRAY(material);
		SAFE_DELETE_ARRAY(face_vert_index);
		SAFE_DELETE_ARRAY(vertex);
	}

}