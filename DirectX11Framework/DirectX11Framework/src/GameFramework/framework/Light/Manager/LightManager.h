// ライトマネージャクラス
// 2016. 5.17	:	プログラム作成
// author		:	SyunMizuno

#pragma once


#include	"../Light.h"
#include	"../../Singleton/Singleton.h"
#include	<vector>


namespace MSLib {

	class LightManager : public	Singleton<LightManager> {
	private:
		std::vector<Light*>	m_aLight;

	public:
		LightManager();
		virtual ~LightManager();

		void Set();
		void Add(Light* light);
		bool Delete(Light* light);
		Light* Get(const std::string& Name);
	};

	LightManager* GetLightManager();

};