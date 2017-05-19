// シェーダアーカイブ用ベース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#pragma once

#include	"../Base/IArchivesType.h"


namespace MSLib {
	namespace ArchivesCollection {

		class ArchivesShaderBase : public	IArchivesType<std::string> {
		public:
			ArchivesShaderBase();
			virtual ~ArchivesShaderBase();

		protected:
			virtual void Create() override;
		};

	};
};