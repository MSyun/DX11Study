// �V�F�[�_�A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace ArchivesCollection {

	class ArchivesShaderBase : public	IArchivesType<string> {
	public:
		ArchivesShaderBase();
		virtual ~ArchivesShaderBase();

	protected:
		virtual void Create() override;
	};

}