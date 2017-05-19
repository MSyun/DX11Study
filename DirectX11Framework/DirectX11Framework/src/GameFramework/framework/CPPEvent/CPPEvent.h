// �C�x���g�֐�
// 2016.12.30	�v���O�����쐬
// author		SyunMizuno

#pragma once

#include	<list>
#include	"../Delegate/Delegate.h"


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

namespace MSLib {

	template<typename... Args>
	class CPPEvent {
	private:
		std::list<IDelegate<Args...>*>	m_lstListener;

	public:
		CPPEvent();
		virtual ~CPPEvent();

		/* �֐���o�^
		// func	: �o�^����֐�
		*/
		void AddListener(std::function<void(Args...)> func);

		/* �֐����J��
		// func	: �������֐�
		*/
		void RemoveListener(std::function<void(Args...)> func);

		/* �o�^�ς݂̊֐������ׂĊJ�� */
		void RemoveAllListener();

		/* �o�^�ς݊֐��̌���Ԃ� */
		int GetListenerCount();

		/* �o�^�ς݂̊֐������s
		// args	: �֐��ɓn������
		*/
		void Invoke(Args... args);
	};


#include	"CPPEvent.inl"

};