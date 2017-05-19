// オブジェクト3Dクラス
// 2016. 5. 1	プログラム作成
// Author		SyunMizuno


#pragma once


#include	"../Object.h"
#include	"../../../Transform/Transform.h"
#include	"../../Resource/Mesh/Mesh.h"
#include	<memory>


namespace MSLib {

	class Object3D : public Object {
	protected:
#pragma region variable

		Transform*	m_pTransform;
		Mesh*		m_pMesh;
//		shared_ptr<Mesh>	m_pMesh;

#pragma endregion

	public:
		Object3D();
		virtual ~Object3D();

		virtual void UpdateAll() final;
		virtual void LateUpdateAll() final;
		virtual void DrawAll() final;
		virtual void LateDrawAll() final;

		Transform* GetTransform() { return m_pTransform; }
		Mesh* GetMesh() { return m_pMesh; }


		virtual void OnCollisionTrigger(Object3D* obj) {}
		virtual void OnCollisionStay(Object3D* obj) {}
		virtual void OnCollisionRelease(Object3D* obj) {}

#pragma region Mesh
		void CreateMesh(string name);
		void DeleteMesh();
		void SetModel(Mesh* mesh);
//		void SetModel(shared_ptr<Mesh> mesh);
#pragma endregion

		virtual void Destroy() override;

	private:

	};

};