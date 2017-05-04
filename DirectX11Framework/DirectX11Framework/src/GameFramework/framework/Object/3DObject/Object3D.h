// �I�u�W�F�N�g3D�N���X
// 2016. 5. 1	�v���O�����쐬
// Author		SyunMizuno


#pragma once


#include	"../Object.h"
#include	"../../../Transform/Transform.h"



class Object3D	:	public Object {
protected:
#pragma region variable

	Transform*	m_pTransform;


#pragma endregion

public:
	Object3D();
	virtual ~Object3D();

	virtual void UpdateAll() override;
	virtual void LateUpdateAll() override;
	virtual void DrawAll() override;
	virtual void LateDrawAll() override;

	Transform* GetTransform() { return m_pTransform; }

	virtual void OnCollisionTrigger(Object3D* obj) {}
	virtual void OnCollisionStay(Object3D* obj) {}
	virtual void OnCollisionRelease(Object3D* obj) {}

	virtual void Destroy() override;

private:

};