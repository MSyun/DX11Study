//////////////////////////////////////////////////////////////
// �Z�[�u�p�t�@�N�g���N���X
// 2016. 12. 27	�v���O�����쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#include	"SaveFactory.h"


namespace MSLib {
	namespace Save {

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
}