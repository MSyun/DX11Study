//////////////////////////////////////////////////////////////
// �Z�[�u�p�t�@�N�g���N���X
// 2016. 12. 27	�v���O�����쐬
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