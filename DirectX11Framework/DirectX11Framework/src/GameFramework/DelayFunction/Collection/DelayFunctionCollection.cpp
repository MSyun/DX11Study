//	�x���^�֐��Ǘ��N���X
// 2017. 3.22	�v���O�����쐬
// author		SyunMizuno


#include	"DelayFunctionCollection.h"
#include	"../../framework/Debug/Debug.h"
#include	"../../framework/Utility/System/SystemUtility.h"


std::vector<DelayFunction*> DelayFunctionCollection::m_aCollection;


/*									//
//			�R���X�g���N�^			//
//									*/
DelayFunctionCollection::DelayFunctionCollection() {

}


/*									//
//			�f�X�g���N�^			//
//									*/
DelayFunctionCollection::~DelayFunctionCollection() {
	AllDelete();
}


/*									//
//				�ǉ�				//
//									*/
void DelayFunctionCollection::Add(DelayFunction* func) {
	if (!func) {
		Debug::LogError("DelayFunctionCollection::Add : Null Instances");
	}
	m_aCollection.push_back(func);
}


/*									//
//				�X�V				//
//									*/
void DelayFunctionCollection::Update() {
	for (auto it = m_aCollection.begin(); it != m_aCollection.end(); ) {
		if ((*it)->TimeMate()) {
			SAFE_DELETE(*it);
			it = m_aCollection.erase(it);
			continue;
		}
		++it;
	}
}


/*									//
//			�S�v�f�폜				//
//									*/
void DelayFunctionCollection::AllDelete() {
	for (auto it = m_aCollection.begin(); it != m_aCollection.end(); ++it) {
		SAFE_DELETE(*it);
	}
	m_aCollection.clear();
}