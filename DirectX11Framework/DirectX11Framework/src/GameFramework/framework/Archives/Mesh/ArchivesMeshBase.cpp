// ���b�V���A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"ArchivesMeshBase.h"


namespace ArchivesCollection {

	ArchivesMeshBase::ArchivesMeshBase() {
		Create();
	}

	ArchivesMeshBase::~ArchivesMeshBase() {
	}

	void ArchivesMeshBase::Create() {
//		Add("Player", "data/MESH/ruby/ruby.x");
		Add("Watch", "data/Mesh/Watch/Watch.pmd");
		Add("Miku", "data/Mesh/miku1/�����~�N_�A�m�}��ver.pmd");
	}

}