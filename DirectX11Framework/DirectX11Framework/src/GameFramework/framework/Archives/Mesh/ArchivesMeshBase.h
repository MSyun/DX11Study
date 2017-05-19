// メッシュアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace MSLib {
	namespace ArchivesCollection {

		class ArchivesMeshBase : public	IArchivesType<std::string> {
		public:
			ArchivesMeshBase();
			virtual ~ArchivesMeshBase();

		protected:
			virtual void Create() override;
		};

	};
};