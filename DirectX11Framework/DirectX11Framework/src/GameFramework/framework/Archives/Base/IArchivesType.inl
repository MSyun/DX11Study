// アーカイブ用インターフェース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#include	<typeinfo>


template<typename T>
IArchivesType<T>::IArchivesType() {
	Create();
}

template<typename T>
IArchivesType<T>::~IArchivesType() {
}

template<typename T>
T IArchivesType<T>::Find(const string name) {
	auto it = m_Archives.find(name);
	if (it == m_Archives.end()) {
		T val = 0;
		return val;
	}
	return it->second;
}

template<typename T>
void IArchivesType<T>::Add(string key, T regist) {
	m_Archives.insert(pair<string, T>(key, regist));
}