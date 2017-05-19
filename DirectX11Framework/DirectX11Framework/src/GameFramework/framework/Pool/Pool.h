// プール
// 2017.05.18	: プログラム作成
// author		: SyunMizuno

#pragma once

#include	<map>


namespace MSLib {

	template<typename obj, typename key>
	class Pool {
	private:
		std::map<obj, key> m_Map;

	public:
		Pool();
		virtual ~Pool();

		void Add(obj _Obj, key _Key);
		obj* Get(key _Key);
		void Release(key _Key);
	};

#include	"Pool.inl"

};