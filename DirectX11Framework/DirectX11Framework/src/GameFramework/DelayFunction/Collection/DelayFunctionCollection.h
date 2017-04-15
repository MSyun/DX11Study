//	�x���^�֐��Ǘ��N���X
// 2017. 3.22	�v���O�����쐬
// author		SyunMizuno


#pragma once

#include	"../DelayFunction.h"
#include	<vector>


class DelayFunctionCollection {
private:
	static std::vector<DelayFunction*> m_aCollection;

public:
	DelayFunctionCollection();
	virtual ~DelayFunctionCollection();

	// �ǉ�
	static void Add(DelayFunction* func);

	// ���Ԍv��
	static void Update();

	// �S�v�f�폜
	static void AllDelete();
};