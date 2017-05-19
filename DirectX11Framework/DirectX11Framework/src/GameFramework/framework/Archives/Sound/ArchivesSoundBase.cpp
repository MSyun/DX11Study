// サウンドアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#include	"ArchivesSoundBase.h"


namespace MSLib {
	namespace ArchivesCollection {

		ArchivesSoundBase::ArchivesSoundBase() {
			Create();
		}

		ArchivesSoundBase::~ArchivesSoundBase() {
		}

		void ArchivesSoundBase::Create() {
			//	Add("Cursor", "data/SOUND/SE/cursor.wav");
		}

	};
};