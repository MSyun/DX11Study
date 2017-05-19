// イベント関数
// 2016.12.30	プログラム作成
// author		SyunMizuno

#pragma once

#include	<list>
#include	"../Delegate/Delegate.h"


/*
	// 引数無しのクラスメンバ
	AddListener(std::bind(&Class::method, this));
	AddListener(std::bind(&Class::method, this, 5));
	// 引数ありのクラスメンバ
	AddListener(std::bind(&Class::method, this, std::placeholders::_1));
	AddListener([=](int i) {this->method(i);});
	// グローバルな関数
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

		/* 関数を登録
		// func	: 登録する関数
		*/
		void AddListener(std::function<void(Args...)> func);

		/* 関数を開放
		// func	: 解放する関数
		*/
		void RemoveListener(std::function<void(Args...)> func);

		/* 登録済みの関数をすべて開放 */
		void RemoveAllListener();

		/* 登録済み関数の個数を返す */
		int GetListenerCount();

		/* 登録済みの関数を実行
		// args	: 関数に渡す引数
		*/
		void Invoke(Args... args);
	};


#include	"CPPEvent.inl"

};