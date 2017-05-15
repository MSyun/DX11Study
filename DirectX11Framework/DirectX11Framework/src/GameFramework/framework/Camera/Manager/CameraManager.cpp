// カメラマネージャー
// 2017.05.15	: プログラム作成
// author		: SyunMizuno


#include	"CameraManager.h"
#include	"../../Debug/Debug.h"


/*									//
//			コンストラクタ			//
//									*/
CameraManager::CameraManager() :
	m_bHelper(true),
	m_CurCameraName("")
{
	m_MapCamera.clear();
	SetHelper(m_bHelper);
}


/*									//
//			デストラクタ			//
//									*/
CameraManager::~CameraManager() {
	if (!m_bHelper)		return;

	auto it = m_MapCamera.begin();

	//while (it != m_MapCamera.end()) {
	//	SAFE_DELETE(it->second);
	//	++it;
	//}

	// 要素解放
	m_MapCamera.clear();
}


/*									//
//			カメラを作成			//
//									*/
Camera* CameraManager::Create(const string Name) {
	if (m_MapCamera.end() != m_MapCamera.find(Name)) {
		Debug::Log("カメラ名 : " + Name + " はすでに生成されています");
		return Get(Name);
	}

	Camera* camera = new Camera;
	camera->SetName(Name);
	m_MapCamera.insert(pair<string, Camera*>(Name, camera));

	return camera;
}


/*									//
//			カメラの削除			//
//									*/
bool CameraManager::Delete(const string Name) {
	//----- 初期化
	auto it = m_MapCamera.find(Name);

	if (it == m_MapCamera.end()) {
		Debug::Log("カメラ名 : " + Name + " は登録されていないため削除できません");
		return false;
	}

	SAFE_DELETE(it->second);

	m_MapCamera.erase(Name);

	return true;
}


/*									//
//			カメラの取得			//
//									*/
Camera* CameraManager::Get(const string Name) {
	auto it = m_MapCamera.find(Name);

	if (it == m_MapCamera.end()) {
		return Create(Name);
	}

	return it->second;
}


/*									//
//			カメラの設定			//
//									*/
bool CameraManager::Set(const string Name) {
	if (Name.empty()) {
		Debug::LogError("カメラの名前がありません");
		return false;
	}

	Camera* camera = Get(Name);
	if (!camera) {
		Debug::LogError("カメラ名 : " + Name + " は存在しませんでした");
		return false;
	}

	camera->Set();
	m_CurCameraName = Name;
	return true;
}


/*									//
//		最後に使用したものを取得	//
//									*/
Camera* CameraManager::CurrentCamera() {
	return Get(m_CurCameraName);
}

/* 管理オブジェクトを自動で削除するか設定 */
void CameraManager::SetHelper(bool helper) {
	string swit = (helper ? "ON" : "OFF");
	Debug::Log("CameraManagerの補助機能 ： " + swit);

	m_bHelper = helper;
}


/*									//
//			マネージャの取得		//
//									*/
CameraManager* GetCameraManager() {
	return CameraManager::Instance();
}