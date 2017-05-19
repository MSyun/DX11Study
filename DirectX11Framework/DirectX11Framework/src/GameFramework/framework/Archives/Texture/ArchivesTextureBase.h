// テクスチャアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
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