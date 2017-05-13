// デリゲート
// 2016.12.30	プログラム作成
// author		SyunMizuno

#pragma once


#include	"IDelegate.h"
#include	<functional>

template<typename Return = void, typename... Args>
class	Delegate : public	IDelegate<Args...> {
private:
#pragma region variable

	// 関数ポインタ
	std::function<Return(Args...)>	m_Func;

#pragma endregion

public:
#pragma region method

	Delegate();
	virtual ~Delegate();

	/* 登録関数実行	*/
	virtual void Invoke(Args... args);

	/* 自身と同じかチェック */
	bool CheckSame(std::function<Return(Args...)> func);

	/* 関数の設定 */
	void Set(std::function<Return(Args...)> func);

	/* 作成 */
	static IDelegate<Args...>* Create(std::function<Return(Args...)> func);

#pragma endregion
};


#include	"Delegate.inl"