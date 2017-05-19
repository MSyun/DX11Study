// メッシュアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#include	"ArchivesMeshBase.h"


namespace MSLib {
	namespace ArchivesCollection {

		ArchivesMeshBase::ArchivesMeshBase() {
			Create();
		}

		ArchivesMeshBase::~ArchivesMeshBase() {
		}

		void ArchivesMeshBase::Create() {
			//		Add("Player", "data/MESH/ruby/ruby.x");
			Add("Watch", "data/Mesh/Watch/Watch.pmd");
			Add("Miku", "data/Mesh/miku/kio_miku_20111121.pmd");
			Add("Miku1", "data/Mesh/miku1/初音ミク_アノマロver.pmd");
			Add("Miku2", "data/Mesh/miku2/初音ミク@七葉1052式.pmd");
		}

	};
};