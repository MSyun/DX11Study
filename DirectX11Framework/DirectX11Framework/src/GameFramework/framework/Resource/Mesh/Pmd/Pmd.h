// PMDメッシュ
// 2017.05.10	: プログラム作成
// author		: SyunMizuno



#pragma once

#include	<Windows.h>
#include	"../../../Convert/Convert.h"
#include	<vector>


class Pmd {
public:
#pragma pack(push, 1)
	// ヘッダー
	struct t_header {
		unsigned char magic[3];
		float version;
		unsigned char model_name[20];
		unsigned char comment[256];
	};
	t_header header;

	// 頂点リスト
	unsigned long vert_count;
	struct t_vertex {
		Vector3 pos;
		Vector3 normal_vec;
		Vector2 uv;
		unsigned short bone_num[2];	// ボーン番号
		unsigned char bone_weight;	// ボーンウェイト
		unsigned char edge_flag;	// 0:通常、1:エッジ無効
	};
	t_vertex* vertex;

	// 面頂点リスト
	unsigned long face_vert_count;
	unsigned short* face_vert_index;

	// マテリアル
	unsigned long material_count;	// 材質数
	struct t_material {
		Vector3 diffuse;
		float alpha;
		float specularity;
		Vector3 specular;	// 光沢色
		Vector3 ambient;	// 環境色
		unsigned char toon_index;	// toon??.bmp // 0.bmp:0xFF, 1(01).bmp:0x00 … 10.bmp:0x09
		unsigned char edge_flag;	// 輪郭、影
		unsigned int face_vert_count;	// 面頂点数 // インデックスに変換する場合は、材質0から順に加算
		char texfile_name[20];	// テクスチャファイル名またはスフィアファイル名 //20バイトぎりぎりまで使える（終端の0x00はなくても動く)
	};
	t_material* material;	// 材質データ

	///////////////////////////////////////
	// ボーン情報
	unsigned char bone_count;	// ボーン数
	struct t_bone {
		char bone_name[20];
		WORD parent_bone_index;	// 親ボーン番号（ない場合は0xFFFF)
		WORD tail_pos_bone_index;	// tail位置のボーン番号(チェーン末端の場合は0⇒補足2) // 親 : 子は 1 : 多なので、主に位置決め用
		// 0:回転、1:回転と移動、2:IK、3:不明、4:IK影響下、5:回転影響下、6:IK接続先、7:非表示
		byte bone_type;	// ボーンの種類
		WORD ik_parent_bone_index;	// IKボーン番号（影響IKボーン。ない場合は0)
		Vector3 bone_head_pos;	// x,y,z	// ボーンのヘッドの位置
	};
	t_bone* bone;

	//////////////////////////////////////
	// IK情報
	struct t_ik {
		unsigned short bone_index;	// IKボーン番号
		unsigned short target_bone_index;	// IKターゲットボーン番号 // IKボーンが最初に接続するボーン
		unsigned char chain_length;	// IKチェーンの長さ（子の数）
		unsigned short interations;	// 再帰演算回数 // IK値1
		float control_weight;	// IKの影響度
		std::vector<unsigned short> child_bone_index;	// [ik_chain_length] IK影響下のボーン番号
	};
#pragma pack(pop)

	Pmd(const std::string filename);
	~Pmd();
};