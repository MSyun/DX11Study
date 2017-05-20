// カメラマネージャー
// 2017.05.15	: プログラム作成
// author		: SyunMizuno


#include	"CameraManager.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	CameraManager::CameraManager() :
		m_CurCameraName("")
	{
		Debug::Log("CameraManager を作成");
		m_aCamera.resize(3);
		m_aCamera.clear();
	}


	CameraManager::~CameraManager() {
		Debug::Log("CameraManager を削除");
		m_aCamera.clear();
	}


	/*									//
	//				追加				//
	//									*/
	void CameraManager::Add(Camera* camera) {
		if (!camera) {
			Debug::LogError("カメラの実態がありません");
			return;
		}

		m_aCamera.push_back(camera);
	}


	/*									//
	//			カメラの削除			//
	//									*/
	bool CameraManager::Delete(Camera* camera) {
		for (auto it = m_aCamera.begin(); it != m_aCamera.end(); ++it) {
			if ((*it) == camera) {
				m_aCamera.erase(it);
				return true;
			}
		}
		Debug::LogError("CameraManager : 削除したいオブジェクトが見つかりません");
		return false;
	}


	/*									//
	//			カメラの取得			//
	//									*/
	Camera* CameraManager::Get(const std::string& Name) {
		if (Name.empty()) {
			Debug::LogError("カメラの名前がありません");
			return nullptr;
		}

		for (auto it = m_aCamera.begin(); it != m_aCamera.end(); ++it) {
			if ((*it)->GetName() == Name)
				return (*it);
		}

		return nullptr;
	}


	/*									//
	//			カメラの設定			//
	//									*/
	bool CameraManager::Set(const std::string& Name) {
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


	/*									//
	//			マネージャの取得		//
	//									*/
	CameraManager* GetCameraManager() {
		return CameraManager::Instance();
	}

};