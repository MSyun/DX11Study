// �T�E���h�A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace MSLib {
	namespace ArchivesCollection {

		class ArchivesSoundBase : public	IArchivesType<std::string> {
		public:
			ArchivesSoundBase();
			virtual ~ArchivesSoundBase();

		protected:
			virtual void Create() override;
		};

	};
};