// オブジェクトクラス
// 2016. 4.29	プログラム作成
// Author		SyunMizuno

#pragma once


#include	"../CPPEvent/CPPEvent.h"
#include	"../Utility/System/SystemUtility.h"
#include	<string>


namespace MSLib {

	class Object {
	private:
#pragma region variable

		std::string	m_Name;		// 名前
		byte		m_uTag;
		bool		m_bOperate;
		bool		m_bIsActive;
		bool		m_bDontDestroy;
		bool		m_bDestroy;
		bool		m_bInit;

		CPPEvent<>*	m_onDestroyEvent;

#pragma endregion

	public:
#pragma region method

		Object();
		virtual ~Object();

		virtual void UpdateAll();
		virtual void LateUpdateAll() = 0;
		virtual void DrawAll();
		virtual void LateDrawAll();

#pragma region Operate
		void ChangeOperate();
		void SetOperate(const bool flg);
		bool GetOperate();
#pragma endregion

#pragma region Name
		void SetName(const std::string name);
		std::string GetName();
#pragma endregion

#pragma region Tag
		void SetTag(byte tag);
		byte GetTag();
#pragma endregion

#pragma region Active
		void SetActive(bool active);
		bool GetActive();
#pragma endregion

#pragma region Destroy
		virtual void Destroy();
		bool GetDestroy();
		void OnDestroy();
		CPPEvent<>* GetOnDestroy();
#pragma endregion

#pragma region DontDestroyOnLoad
		void DontDestroyOnLoad();
		bool GetDontDestroy();
#pragma endregion

#pragma endregion

	protected:
#pragma region conceal method

		virtual void Input();
		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Draw();
		virtual void LateDraw();
		virtual void OnActive();
		virtual void OnOperate();

#pragma endregion
	};

};