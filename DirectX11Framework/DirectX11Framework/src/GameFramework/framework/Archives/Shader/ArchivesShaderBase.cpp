// シェーダアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#include	"ArchivesShaderBase.h"


namespace ArchivesCollection {

	ArchivesShaderBase::ArchivesShaderBase() {
		Create();
	}

	ArchivesShaderBase::~ArchivesShaderBase() {
	}

	void ArchivesShaderBase::Create() {
		Add("Default/Phong", "Phong.hlsl");
	}

}