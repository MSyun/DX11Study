#pragma once



/*									//
//			コンストラクタ			//
//									*/
template<typename Return = void, typename... Args>
Delegate<Return, Args...>::Delegate() {

}


/*									//
//			デストラクタ			//
//									*/
template<typename Return = void, typename... Args>
Delegate<Return, Args...>::~Delegate() {

}


/*									//
//			登録関数実行			//
//									*/
template<typename Return = void, typename... Args>
void Delegate<Return, Args...>::Invoke(Args... args) {
	if (m_Func)
		m_Func(args...);
}


/*									//
//		自身と同じかチェック		//
//									*/
template<typename Return = void, typename... Args>
bool Delegate<Return, Args...>::CheckSame(std::function<Return(Args...)> func) {
	if (m_Func == func)
		return true;

	return false;
}


/*									//
//				関数の設定			//
//									*/
template<typename Return = void, typename... Args>
void Delegate<Return, Args...>::Set(std::function<Return(Args...)> func) {
	m_Func = func;
}


/*									//
//				作成				//
//									*/
template<typename Return = void, typename... Args>
IDelegate<Args...>* Delegate<Return, Args...>::Create(std::function<Return(Args...)> func) {
	Delegate<Return, Args...>* dele = new Delegate<Return, Args...>;
	dele->Set(func);
	return dele;
}