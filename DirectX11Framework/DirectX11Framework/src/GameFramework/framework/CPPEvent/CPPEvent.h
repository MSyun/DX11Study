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

	CPPEvent() {};
	virtual ~CPPEvent() {
		RemoveAllListener();
	};

	// �֐���o�^
	void AddListener(function<void(Args...)> func) {
		m_lstListener.push_back(Delegate<void, Args...>::Create(func));
	};

	// �֐����J��
	void RemoveListener(function<void(Args...)> func) {
		for (auto it = m_lstListener.begin(); it != m_lstListener.end(); ++it) {
			if (!(*it)->CheckSame(func))
				continue;

			delete (*it);
			(*it) = NULL;
			return;
		}
	}

	// �o�^�ς݂̊֐������ׂĊJ��
	void RemoveAllListener() {
		for (auto it = m_lstListener.begin(); it != m_lstListener.end(); ++it) {
			delete *it;
			*it = NULL;
		}
		m_lstListener.clear();
	};

	// �֐��̌���Ԃ�
	int GetListenerCount() {
		return m_lstListener.size();
	};

	// �o�^�ς݂̊֐������s
	void Invoke(Args... args) {
		for (auto it = m_lstListener.begin(); it != m_lstListener.end(); ++it) {
			(*it)->Invoke(args...);
		}
	};

#pragma endregion
};