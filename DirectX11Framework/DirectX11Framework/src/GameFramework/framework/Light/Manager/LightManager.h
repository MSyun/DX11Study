// ライトマネージャクラス
// 2016. 5.17	:	プログラム作成
// author		:	SyunMizuno

#pragma once


#include	"../Light.h"
#include	"../../Singleton/Singleton.h"
#include	<map>


namespace MSLib {

	class LightManager : public	Singleton<LightManager> {
	private:
		map<string, Light*>	m_MapLight;
		bool	m_bHelper;

	public:
		LightManager();
		virtual ~LightManager();

		void Set();
		Light* Create(const string& Name);
		bool Delete(const string& Name);
		Light* Get(const string& Name);
		void SetHelper(bool helper);
	};

	LightManager* GetLightManager();

};