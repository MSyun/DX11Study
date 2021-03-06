
template<typename... Args>
CPPEvent<Args...>::CPPEvent() {

}


template<typename... Args>
CPPEvent<Args...>::~CPPEvent() {
	RemoveAllListener();
}


template<typename... Args>
void CPPEvent<Args...>::AddListener(std::function<void(Args...)> func) {
	m_lstListener.push_back(Delegate<void, Args...>::Create(func));
}


template<typename... Args>
void CPPEvent<Args...>::RemoveListener(std::function<void(Args...)> func) {
	for (auto it = m_lstListener.begin(); it != m_lstListener.end(); ++it) {
		if (!(*it)->CheckSame(func))
			continue;

		delete (*it);
		(*it) = nullptr;
		return;
	}
}


template<typename... Args>
void CPPEvent<Args...>::RemoveAllListener() {
	for (auto it = m_lstListener.begin(); it != m_lstListener.end(); ++it) {
		delete *it;
		*it = nullptr;
	}
	m_lstListener.clear();
}


template<typename... Args>
int CPPEvent<Args...>::GetListenerCount() {
	return m_lstListener.size();
}


template<typename... Args>
void CPPEvent<Args...>::Invoke(Args... args) {
	for (auto it = m_lstListener.begin(); it != m_lstListener.end(); ++it) {
		(*it)->Invoke(args...);
	}
}