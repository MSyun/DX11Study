// デリゲート
// 2016.12.30	プログラム作成
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

		/* 登録関数実行	*/
		virtual void Invoke(Args... args);

		/* 自身と同じかチェック */
		bool CheckSame(std::function<Return(Args...)> func);

		/* 関数の設定 */
		void Set(std::function<Return(Args...)> func);

		/* 作成 */
		static IDelegate<Args...>* Create(std::function<Return(Args...)> func);
	};


#include	"Delegate.inl"

};