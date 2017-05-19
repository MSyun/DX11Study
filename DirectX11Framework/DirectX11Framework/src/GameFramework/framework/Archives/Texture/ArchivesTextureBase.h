// �e�N�X�`���A�[�J�C�u�p�x�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace MSLib {
	namespace ArchivesCollection {

		class ArchivesTextureBase : public	IArchivesType<std::string> {
		public:
			ArchivesTextureBase();
			virtual ~ArchivesTextureBase();

		protected:
			virtual void Create() override;
		};

	};
};