// メッシュアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#include	"ArchivesMeshBase.h"


namespace ArchivesCollection {

	ArchivesMeshBase::ArchivesMeshBase() {
		Create();
	}

	ArchivesMeshBase::~ArchivesMeshBase() {
	}

	void ArchivesMeshBase::Create() {
//		Add("Player", "data/MESH/ruby/ruby.x");
		Add("Watch", "data/Mesh/Watch/Watch.pmd");
		Add("Miku", "data/Mesh/miku1/初音ミク_アノマロver.pmd");
	}

}