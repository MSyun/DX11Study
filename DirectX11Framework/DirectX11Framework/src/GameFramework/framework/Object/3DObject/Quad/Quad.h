// �|���S���I�u�W�F�N�g
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno

#pragma once

#include	"../Object3D.h"
#include	"QuadPolygon/QuadPolygon.h"


namespace MSLib {

	class Quad : public	Object3D {
	private:
		QuadPolygon*	m_pPolygon;

	public:
		Quad();
		virtual ~Quad();

		QuadPolygon* GetPolygon() const;

	protected:
		void Init() override;
		void Update() override;
		void LateUpdate() override;
		void Draw() override;
		void LateDraw() override;
	};

};