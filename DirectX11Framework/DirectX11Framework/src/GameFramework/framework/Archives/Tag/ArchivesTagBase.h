// タグアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
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