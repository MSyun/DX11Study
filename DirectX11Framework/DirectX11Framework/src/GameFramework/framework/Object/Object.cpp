// オブジェクトクラス
// 2016. 4.29	プログラム作成
// Author		SyunMizuno


#include	"Object.h"



Object::Object() :
	m_Name("GameObject"),
	m_uTag(0),
	m_bOperate(false),
	m_bIsActive(true),
	m_bDontDestroy(false),
	m_bDestroy(false),
	m_bInit(false)
{
	//m_onDestroyEvent = new CPPEvent<>;
}


Object::~Object() {
	//SAFE_DELETE(m_onDestroyEvent);
}


void Object::UpdateAll() {
	if (!m_bInit) {
		Init();
		m_bInit = true;
	}
}


void Object::DrawAll() {

}

void Object::LateDrawAll() {

}


#pragma region Operate
void Object::ChangeOperate() {
	m_bOperate ^= true;
	if (m_bOperate)
		OnOperate();
}

void Object::SetOperate(const bool flg) {
	m_bOperate = flg;
	if (m_bOperate)
		OnOperate();
}

bool Object::GetOperate() {
	return m_bOperate;
}
#pragma endregion


#pragma region Name
void Object::SetName(const string name) {
	m_Name = name;
}

string Object::GetName() {
	return m_Name;
}
#pragma endregion


#pragma region Tag
void Object::SetTag(byte tag) {
	m_uTag = tag;
}
byte Object::GetTag() {
	return m_uTag;
}
#pragma endregion


#pragma region Active
void Object::SetActive(bool active) {
	if (!m_bIsActive && active)
		OnActive();
	m_bIsActive = active;
}
bool Object::GetActive() {
	return m_bIsActive;
}
#pragma endregion


#pragma region Destroy
void Object::Destroy() {
	m_bDestroy = true;
}
bool Object::GetDestroy() {
	return m_bDestroy;
}
void Object::OnDestroy() {
	//m_onDestroyEvent->Invoke();
}
//CPPEvent<>* Object::GetOnDestroy() {
//	return m_onDestroyEvent;
//}
#pragma endregion


#pragma region DontDestroyOnLoad
void Object::DontDestroyOnLoad() {
	m_bDontDestroy = true;
}
bool Object::GetDontDestroy() {
	return m_bDontDestroy;
}
#pragma endregion


void Object::Input() {

}

void Object::Init() {

}

void Object::Update() {

}

void Object::LateUpdate() {

}

void Object::Draw() {

}

void Object::LateDraw() {

}

void Object::OnActive() {

}

void Object::OnOperate() {

}