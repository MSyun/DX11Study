// ���b�V���A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace ArchivesCollection {

	class ArchivesMeshBase : public	IArchivesType<string> {
	public:
		ArchivesMeshBase();
		virtual ~ArchivesMeshBase();

	protected:
		virtual void Create() override;
	};

}