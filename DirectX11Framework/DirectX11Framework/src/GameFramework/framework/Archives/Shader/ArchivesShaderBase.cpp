// �V�F�[�_�A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"ArchivesShaderBase.h"


namespace ArchivesCollection {

	ArchivesShaderBase::ArchivesShaderBase() {
		Create();
	}

	ArchivesShaderBase::~ArchivesShaderBase() {
	}

	void ArchivesShaderBase::Create() {
		Add("Default/Phong", "Phong.hlsl");
	}

}