// タグアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
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