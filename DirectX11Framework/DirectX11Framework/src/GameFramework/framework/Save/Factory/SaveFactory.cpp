//////////////////////////////////////////////////////////////
// セーブ用ファクトリクラス
// 2016. 12. 27	プログラム作成
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#include	"SaveFactory.h"


namespace MSLib {

	ISaveObjBase* SaveFactory::Create(int classID) {
		ISaveObjBase* Obj = nullptr;

		switch (classID) {
		case 0:
			break;

		default:
			break;
		};

		return Obj;
	}

}