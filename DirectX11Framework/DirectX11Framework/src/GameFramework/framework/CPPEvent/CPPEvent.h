// �C�x���g�֐�
// 2016.12.30	�v���O�����쐬
// author		SyunMizuno


#pragma once

#include	<list>
#include	"../Delegate/Delegate.h"
using namespace std;


/*
	// ���������̃N���X�����o
	AddListener(std::bind(&Class::method, this));
	AddListener(std::bind(&Class::method, this, 5));
	// ��������̃N���X�����o
	AddListener(std::bind(&Class::method, this, std::placeholders::_1));
	AddListener([=](int i) {this->method(i);});
	// �O���[�o���Ȋ֐�
	AddListener(&method);
*/


template<typename... Args>
class CPPEvent {
private:
#pragma region variable

	// �֐��|�C���^���X�g
	list<IDelegate<Args...>*>	m_lstListener;

#pragma endregion

public:
#pragma region method

	CPPEvent();
	virtual ~CPPEvent();

	// �֐���o�^
	void AddListener(function<void(Args...)> func);

	// �֐����J��
	void RemoveListener(function<void(Args...)> func);

	// �o�^�ς݂̊֐������ׂĊJ��
	void RemoveAllListener();

	// �֐��̌���Ԃ�
	int GetListenerCount();

	// �o�^�ς݂̊֐������s
	void Invoke(Args... args);

#pragma endregion
};


#include	"CPPEvent.inl"