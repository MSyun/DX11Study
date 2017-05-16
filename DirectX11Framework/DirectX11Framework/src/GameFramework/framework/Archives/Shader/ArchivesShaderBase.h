// シェーダアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
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