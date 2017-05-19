// サウンドアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
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