// ���b�V���A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"ArchivesMeshBase.h"


namespace MSLib {
	namespace ArchivesCollection {

		ArchivesMeshBase::ArchivesMeshBase() {
			Create();
		}

		ArchivesMeshBase::~ArchivesMeshBase() {
		}

		void ArchivesMeshBase::Create() {
			//		Add("Player", "data/MESH/ruby/ruby.x");
			Add("Watch", "data/Mesh/Watch/Watch.pmd");
			Add("Miku", "data/Mesh/miku/kio_miku_20111121.pmd");
			Add("Miku1", "data/Mesh/miku1/�����~�N_�A�m�}��ver.pmd");
			Add("Miku2", "data/Mesh/miku2/�����~�N@���t1052��.pmd");
		}

	};
};