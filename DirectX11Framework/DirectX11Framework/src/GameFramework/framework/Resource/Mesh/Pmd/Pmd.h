// PMD���b�V��
// 2017.05.10	: �v���O�����쐬
// author		: SyunMizuno



#pragma once

#include	<Windows.h>
#include	"../../../Convert/Convert.h"
#include	<vector>


class Pmd {
public:
#pragma pack(push, 1)
	// �w�b�_�[
	struct t_header {
		unsigned char magic[3];
		float version;
		unsigned char model_name[20];
		unsigned char comment[256];
	};
	t_header header;

	// ���_���X�g
	unsigned long vert_count;
	struct t_vertex {
		Vector3 pos;
		Vector3 normal_vec;
		Vector2 uv;
		unsigned short bone_num[2];	// �{�[���ԍ�
		unsigned char bone_weight;	// �{�[���E�F�C�g
		unsigned char edge_flag;	// 0:�ʏ�A1:�G�b�W����
	};
	t_vertex* vertex;

	// �ʒ��_���X�g
	unsigned long face_vert_count;
	unsigned short* face_vert_index;

	// �}�e���A��
	unsigned long material_count;	// �ގ���
	struct t_material {
		Vector3 diffuse;
		float alpha;
		float specularity;
		Vector3 specular;	// ����F
		Vector3 ambient;	// ���F
		unsigned char toon_index;	// toon??.bmp // 0.bmp:0xFF, 1(01).bmp:0x00 �c 10.bmp:0x09
		unsigned char edge_flag;	// �֊s�A�e
		unsigned int face_vert_count;	// �ʒ��_�� // �C���f�b�N�X�ɕϊ�����ꍇ�́A�ގ�0���珇�ɉ��Z
		char texfile_name[20];	// �e�N�X�`���t�@�C�����܂��̓X�t�B�A�t�@�C���� //20�o�C�g���肬��܂Ŏg����i�I�[��0x00�͂Ȃ��Ă�����)
	};
	t_material* material;	// �ގ��f�[�^

	///////////////////////////////////////
	// �{�[�����
	unsigned char bone_count;	// �{�[����
	struct t_bone {
		char bone_name[20];
		WORD parent_bone_index;	// �e�{�[���ԍ��i�Ȃ��ꍇ��0xFFFF)
		WORD tail_pos_bone_index;	// tail�ʒu�̃{�[���ԍ�(�`�F�[�����[�̏ꍇ��0�˕⑫2) // �e : �q�� 1 : ���Ȃ̂ŁA��Ɉʒu���ߗp
		// 0:��]�A1:��]�ƈړ��A2:IK�A3:�s���A4:IK�e�����A5:��]�e�����A6:IK�ڑ���A7:��\��
		byte bone_type;	// �{�[���̎��
		WORD ik_parent_bone_index;	// IK�{�[���ԍ��i�e��IK�{�[���B�Ȃ��ꍇ��0)
		Vector3 bone_head_pos;	// x,y,z	// �{�[���̃w�b�h�̈ʒu
	};
	t_bone* bone;

	//////////////////////////////////////
	// IK���
	struct t_ik {
		unsigned short bone_index;	// IK�{�[���ԍ�
		unsigned short target_bone_index;	// IK�^�[�Q�b�g�{�[���ԍ� // IK�{�[�����ŏ��ɐڑ�����{�[��
		unsigned char chain_length;	// IK�`�F�[���̒����i�q�̐��j
		unsigned short interations;	// �ċA���Z�� // IK�l1
		float control_weight;	// IK�̉e���x
		std::vector<unsigned short> child_bone_index;	// [ik_chain_length] IK�e�����̃{�[���ԍ�
	};
#pragma pack(pop)

	Pmd(const std::string filename);
	~Pmd();
};