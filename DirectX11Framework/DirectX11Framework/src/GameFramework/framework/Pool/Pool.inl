#pragma once


template<typename obj, typename key>
Pool<obj, key>::Pool() {
	m_Map.clear();
}


template<typename obj, typename key>
Pool<obj, key>::~Pool() {

}


template<typename obj, typename key>
void Pool<obj, key>::Add(obj _Obj, key _Key) {
	m_Map.insert(pair<obj, key>(_Obj, _Key));
}


template<typename obj, typename key>
obj* Pool<obj, key>::Get(key _Key) {
	obj* Obj = new obj;

	return Obj;
}


template<typename obj, typename key>
void Pool<obj, key>::Release(key _Key) {

}