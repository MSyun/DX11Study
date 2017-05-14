// ライトクラス
// 2016. 5. 5	:	プログラム作成
// author		:	SyunMizuno


#pragma once


#include	"../Convert/Convert.h"
#include	"../Object/3DObject/Object3D.h"





class Light	:	public	Object3D {
public:
	typedef enum _eLIGHT_COLOR {
		LIGHT_DIFFUSE,
		LIGHT_AMBIENT,
		LIGHT_SPECULAR,
	} LIGHT_COLOR;

protected:
#pragma region variable

	float	m_fLookLength;
	Matrix	m_mtxView;
	Matrix	m_mtxProj;
	float	m_fFovy;		// 視野角
	float	m_fAspect;		// 視野角
	float	m_fNear;		// 前方クリップ
	float	m_fFar;			// 後方クリップ

	Color	m_Diffuse;		// 拡散反射光
	Color	m_Ambient;		// 環境光
	Color	m_Specular;		// 鏡面反射光

#pragma endregion

public:
	Light();
	virtual ~Light();

	/* ビュー行列作成 */
	void CreateView();

	/* プロジェクション行列作成 */
	void CreateProj();

	/* 設定 */
	void Set();

	/* 注視点までの距離を設定
	// _len	; 距離
	*/
	void SetLookLength(const float _len);

	/* 視野角の設定
	// _fovy	: 視野角
	*/
	void SetFovy(const float _fovy);

	/* アスペクト比の設定
	// _aspect	; アスペクト比
	*/
	void SetAspect(const float _aspect);

	/* 前方クリップの設定
	// _near	: 前方クリップ
	*/
	void SetNear(const float _near);

	/* 後方クリップの設定
	// _far	: 後方クリップ
	*/
	void SetFar(const float _far);

	/* ライトの色の設定
	*/
	void SetColor(LIGHT_COLOR type, float r, float g, float b, float a);
	void SetColor(LIGHT_COLOR type, float col);
	void SetColor(LIGHT_COLOR type, const Color& col);

	/* 方向ベクトルの取得 */
	Vector3 GetDirection3();
	Vector4 GetDirection4();

	/* ビュー行列の取得 */
	Matrix GetView() const;

	/* プロジェクション行列の取得 */
	Matrix GetProj() const;

	/* ライトの色の取得 */
	Color GetColor(LIGHT_COLOR type) const;
};