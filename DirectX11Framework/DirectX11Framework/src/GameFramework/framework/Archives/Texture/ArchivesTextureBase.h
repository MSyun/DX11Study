// テクスチャアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
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