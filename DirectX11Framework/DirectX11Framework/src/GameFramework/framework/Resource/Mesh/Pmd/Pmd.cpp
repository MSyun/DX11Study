// PMD���b�V��
// 2017.05.10	: �v���O�����쐬
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
			// �w�b�_�[�ǂݍ���
			fread(&header, sizeof(struct t_header), 1, hFP);

			// ���_���ǂݍ���
			fread(&vert_count, sizeof(vert_count), 1, hFP);

			// ���_�f�[�^�ǂݍ���
			vertex = new t_vertex[vert_count];
			fread(vertex, sizeof(t_vertex), vert_count, hFP);

			// �ʒ��_���X�g�ǂݍ���
			fread(&face_vert_count, sizeof(face_vert_count), 1, hFP);

			// �ʒ��_���X�g�f�[�^�ǂݍ���
			face_vert_index = new unsigned short[face_vert_count];
			fread(face_vert_index, 2, face_vert_count, hFP);

			// �}�e���A����
			fread(&material_count, sizeof(material_count), 1, hFP);

			// �ʃf�[�^�ǂݍ���
			material = new t_material[material_count];
			fread(material, sizeof(t_material), material_count, hFP);

			fclose(hFP);
		} else {
			Debug::LogError("File���J���܂���");
		}
	}

	Pmd::~Pmd() {
		SAFE_DELETE_ARRAY(material);
		SAFE_DELETE_ARRAY(face_vert_index);
		SAFE_DELETE_ARRAY(vertex);
	}

}