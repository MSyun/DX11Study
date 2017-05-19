// �f���Q�[�g
// 2016.12.30	�v���O�����쐬
// author		SyunMizuno

#pragma once


#include	"IDelegate.h"
#include	<functional>


namespace MSLib {

	template<typename Return = void, typename... Args>
	class	Delegate : public	IDelegate<Args...> {
	private:
		std::function<Return(Args...)>	m_Func;

	public:
		Delegate();
		virtual ~Delegate();

		/* �o�^�֐����s	*/
		virtual void Invoke(Args... args);

		/* ���g�Ɠ������`�F�b�N */
		bool CheckSame(std::function<Return(Args...)> func);

		/* �֐��̐ݒ� */
		void Set(std::function<Return(Args...)> func);

		/* �쐬 */
		static IDelegate<Args...>* Create(std::function<Return(Args...)> func);
	};


#include	"Delegate.inl"

};