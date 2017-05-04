//////////////////////////////////////////////////////////////
// セーブ用ファクトリクラス
// 2016. 12. 27	プログラム作成
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#include	"SaveFactory.h"



ISaveObjBase* SaveFactory::Create(int classID) {
	ISaveObjBase* Obj = nullptr;

	switch (classID) {
	default:
		break;
	};

	return Obj;
}