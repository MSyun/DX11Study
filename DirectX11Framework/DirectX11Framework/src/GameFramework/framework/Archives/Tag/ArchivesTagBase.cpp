// �^�O�A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"ArchivesTagBase.h"


namespace ArchivesCollection {

	ArchivesTagBase::ArchivesTagBase() {
		Create();
	}

	ArchivesTagBase::~ArchivesTagBase() {
	}

	void ArchivesTagBase::Create() {
		Add("Default", 0);
	}

}