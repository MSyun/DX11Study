//////////////////////////////////////////////////////////////
// セーブ用ファクトリクラス
// 2016. 12. 27	プログラム作成
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once


#include	"../Obj/SaveObjBase.h"


namespace MSLib {

	typedef enum {
		SAVE_FACT_MAX,
	}_SAVE_FACTORY;


	class SaveFactory {
	public:
		SaveFactory() {}
		virtual ~SaveFactory() {}
		static ISaveObjBase* Create(int classID);
	};

}