// �^�O�A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace ArchivesCollection {

	class ArchivesTagBase : public	IArchivesType<unsigned char> {
	public:
		ArchivesTagBase();
		virtual ~ArchivesTagBase();

	protected:
		virtual void Create() override;
	};

}