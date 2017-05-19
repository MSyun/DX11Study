// カメラ
// 2016. 4.30	:	プログラム作成
// author		:	SyunMizuno

#pragma once

#include	"../Object/3DObject/Object3D.h"
#include	"../Convert/Convert.h"


namespace MSLib {

	class Camera : public	Object3D {
	protected:
		// ビュー関係
		Matrix	m_matView;		// 
		float	m_fLookLength;	// 注視点までの距離

		// プロジェクション関係
		Matrix	m_matProj;		// プロジェクション
		float	m_fFovy;		// 視野角
		float	m_fAspect;		// アスペクト比
		float	m_fNear;		// 前方クリップ
		float	m_fFar;			// 後方クリップ

	public:
		/* コンストラクタ */
		Camera();

		/* デストラクタ */
		virtual ~Camera();

		/* カメラの設定 */
		void Set();

		/* 注視点の距離を設定
		// len	: 設定する長さ
		*/
		void SetLookLength(float len);
		void AddLookLength(float len);

		/* ビュー行列の取得 */
		Matrix GetView() const;

		/* プロジェクション行列の取得 */
		Matrix GetProj() const;

		/* 視野角の設定
		// Fovy	: 設定したい視野角
		*/
		void SetFovy(float fovy);

		/* アスペクト比の設定
		// Aspect	: 設定したいアスペクト比の設定
		*/
		void SetAspect(float aspect);

		/* ニアクリップの設定
		// Near	: 設定したいニアクリップ
		*/
		void SetNear(float Near);

		/* ファークリップの設定
		// Far	: 設定したいファークリップ
		*/
		void SetFar(float Far);
	};

};