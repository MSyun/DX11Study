// �J�����}�l�[�W���[
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno


#include	"CameraManager.h"
#include	"../../Debug/Debug.h"


/*									//
//			�R���X�g���N�^			//
//									*/
CameraManager::CameraManager() :
	m_bHelper(true),
	m_CurCameraName("")
{
	m_MapCamera.clear();
	SetHelper(m_bHelper);
}


/*									//
//			�f�X�g���N�^			//
//									*/
CameraManager::~CameraManager() {
	if (!m_bHelper)		return;

	auto it = m_MapCamera.begin();

	//while (it != m_MapCamera.end()) {
	//	SAFE_DELETE(it->second);
	//	++it;
	//}

	// �v�f���
	m_MapCamera.clear();
}


/*									//
//			�J�������쐬			//
//									*/
Camera* CameraManager::Create(const string Name) {
	if (m_MapCamera.end() != m_MapCamera.find(Name)) {
		Debug::Log("�J������ : " + Name + " �͂��łɐ�������Ă��܂�");
		return Get(Name);
	}

	Camera* camera = new Camera;
	camera->SetName(Name);
	m_MapCamera.insert(pair<string, Camera*>(Name, camera));

	return camera;
}


/*									//
//			�J�����̍폜			//
//									*/
bool CameraManager::Delete(const string Name) {
	//----- ������
	auto it = m_MapCamera.find(Name);

	if (it == m_MapCamera.end()) {
		Debug::Log("�J������ : " + Name + " �͓o�^����Ă��Ȃ����ߍ폜�ł��܂���");
		return false;
	}

	SAFE_DELETE(it->second);

	m_MapCamera.erase(Name);

	return true;
}


/*									//
//			�J�����̎擾			//
//									*/
Camera* CameraManager::Get(const string Name) {
	auto it = m_MapCamera.find(Name);

	if (it == m_MapCamera.end()) {
		return Create(Name);
	}

	return it->second;
}


/*									//
//			�J�����̐ݒ�			//
//									*/
bool CameraManager::Set(const string Name) {
	if (Name.empty()) {
		Debug::LogError("�J�����̖��O������܂���");
		return false;
	}

	Camera* camera = Get(Name);
	if (!camera) {
		Debug::LogError("�J������ : " + Name + " �͑��݂��܂���ł���");
		return false;
	}

	camera->Set();
	m_CurCameraName = Name;
	return true;
}


/*									//
//		�Ō�Ɏg�p�������̂��擾	//
//									*/
Camera* CameraManager::CurrentCamera() {
	return Get(m_CurCameraName);
}

/* �Ǘ��I�u�W�F�N�g�������ō폜���邩�ݒ� */
void CameraManager::SetHelper(bool helper) {
	string swit = (helper ? "ON" : "OFF");
	Debug::Log("CameraManager�̕⏕�@�\ �F " + swit);

	m_bHelper = helper;
}


/*									//
//			�}�l�[�W���̎擾		//
//									*/
CameraManager* GetCameraManager() {
	return CameraManager::Instance();
}