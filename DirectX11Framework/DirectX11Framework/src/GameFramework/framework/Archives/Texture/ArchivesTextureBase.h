// �e�N�X�`���A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace ArchivesCollection {

	class ArchivesTextureBase : public	IArchivesType<string> {
	public:
		ArchivesTextureBase();
		virtual ~ArchivesTextureBase();

	protected:
		virtual void Create() override;
	};

}