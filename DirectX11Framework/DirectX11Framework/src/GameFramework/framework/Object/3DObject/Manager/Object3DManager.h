// 3Dオブジェクトマネージャー
// 2016. 5.15	:	プログラム作成
// author		:	SyunMizuno

#pragma once


#include	"../Object3D.h"
#include	"../../../Singleton/Singleton.h"
#include	<list>


namespace MSLib {

	typedef struct {
		Object3D*	pObject;
	} _3DOBJECT;


	class Object3DManager : public	Singleton<Object3DManager> {
	protected:
		list<_3DOBJECT*>	m_lstObject;

		bool	m_bHelper;

	public:
		Object3DManager();
		virtual ~Object3DManager();

		/* 検索 */
		Object3D* Find(const string& name);
		Object3D* FindWithTag(const byte tag);

		void Add(Object3D* obj);
		void AllClear();
		void Delete(Object3D* obj);

		void Update();
		void LateUpdate();

		void Draw();
		void LateDraw();

		void CheckDestroy();
		void SetHelper(bool helper);
	};


	Object3DManager* GetObject3DManager();

};