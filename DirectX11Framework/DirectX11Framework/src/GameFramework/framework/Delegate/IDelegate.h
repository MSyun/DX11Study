// デリゲートインターフェース
// 2016.12.30	プログラム作成
// author		SyunMizuno

#pragma once


namespace MSLib {

	template<typename... Args>
	class IDelegate {
	public:
		IDelegate() {}
		virtual ~IDelegate() {}

		// 実行関数
		virtual void Invoke(Args...) = 0;
	};

};