#pragma once



/*									//
//			�R���X�g���N�^			//
//									*/
template<typename Return = void, typename... Args>
Delegate<Return, Args...>::Delegate() {

}


/*									//
//			�f�X�g���N�^			//
//									*/
template<typename Return = void, typename... Args>
Delegate<Return, Args...>::~Delegate() {

}


/*									//
//			�o�^�֐����s			//
//									*/
template<typename Return = void, typename... Args>
void Delegate<Return, Args...>::Invoke(Args... args) {
	if (m_Func)
		m_Func(args...);
}


/*									//
//		���g�Ɠ������`�F�b�N		//
//									*/
template<typename Return = void, typename... Args>
bool Delegate<Return, Args...>::CheckSame(std::function<Return(Args...)> func) {
	if (m_Func == func)
		return true;

	return false;
}


/*									//
//				�֐��̐ݒ�			//
//									*/
template<typename Return = void, typename... Args>
void Delegate<Return, Args...>::Set(std::function<Return(Args...)> func) {
	m_Func = func;
}


/*									//
//				�쐬				//
//									*/
template<typename Return = void, typename... Args>
IDelegate<Args...>* Delegate<Return, Args...>::Create(std::function<Return(Args...)> func) {
	Delegate<Return, Args...>* dele = new Delegate<Return, Args...>;
	dele->Set(func);
	return dele;
}