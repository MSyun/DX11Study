// サウンドアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace ArchivesCollection {

	class ArchivesSoundBase : public	IArchivesType<string> {
	public:
		ArchivesSoundBase();
		virtual ~ArchivesSoundBase();

	protected:
		virtual void Create() override;
	};

}