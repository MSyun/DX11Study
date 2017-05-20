// 3Dオブジェクトマネージャー
// 2016. 5.15	:	プログラム作成
// author		:	SyunMizuno

#pragma once


#include	"../Object3D.h"
#include	"../../../Singleton/Singleton.h"
#include	<list>
#include	<memory>


namespace MSLib {

	typedef struct {
		Object3D*	pObject;
	} _3DOBJECT;


	class Object3DManager : public	Singleton<Object3DManager> {
	protected:
		std::list<std::shared_ptr<Object3D>>	m_lstObject;

	public:
		Object3DManager();
		virtual ~Object3DManager();

		/* 検索 */
		Object3D* Find(const std::string& name);
		Object3D* FindWithTag(const byte tag);

		void Add(Object3D* obj);
		void AllClear();

		void Update();
		void LateUpdate();

		void Draw();
		void LateDraw();

		void CheckDestroy();
	};


	Object3DManager* GetObject3DManager();

};