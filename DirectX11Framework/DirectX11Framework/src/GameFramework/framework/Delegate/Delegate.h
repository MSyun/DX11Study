// �f���Q�[�g
// 2016.12.30	�v���O�����쐬
// author		SyunMizuno

#pragma once


#include	"IDelegate.h"
#include	<functional>

template<typename Return = void, typename... Args>
class	Delegate : public	IDelegate<Args...> {
private:
#pragma region variable

	// �֐��|�C���^
	std::function<Return(Args...)>	m_Func;

#pragma endregion

public:
#pragma region method

	Delegate() {}
	virtual ~Delegate() {}

	// �o�^�֐����s
	virtual void Invoke(Args... args) {
		if(m_Func)
			m_Func(args...);
	}

	// ���g�Ɠ������`�F�b�N
	bool CheckSame(std::function<Return(Args...)> func) {
		if (m_Func == func)
			return true;

		return false;
	}

	// �֐��̐ݒ�
	void Set(std::function<Return(Args...)> func) {
		m_Func = func;
	}

	// �쐬
	static IDelegate<Args...>* Create(std::function<Return(Args...)> func) {
		Delegate<Return, Args...>* dele = new Delegate<Return, Args...>;
		dele->Set(func);
		return dele;
	}

#pragma endregion
};