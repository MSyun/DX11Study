// マテリアル解析者
// 2017.05. 4	: プログラム作成
// author		: SyunMizuno




#pragma once

#include	<fbxsdk.h>
#include	"../../../Convert/Convert.h"
#include	<string>
using namespace std;



class MaterialAnalyzer {
public:
#pragma region enum

	enum PropertyType {
		PropertyType_Ambient,
		PropertyType_Diffuse,
		PropertyType_Specular,
		PropertyType_Emissive,
		PropertyType_Bump,
	};

#pragma endregion

protected:
#pragma region variable

	Vector3	m_Ambient;
	Vector3	m_Diffuse;
	Vector3	m_Emissive;
	Vector3	m_Specular;
	Vector3	m_Bump;
	float	m_Transparency;
	float	m_Shiniess;
	float	m_Reflectivity;
	char	m_AmbientTexName[256];
	char	m_DiffuseTexName[256];
	char	m_SpecularTexName[256];
	char	m_EmissiveTexName[256];
	char	m_BumpTexName[256];

#pragma endregion

public:
	MaterialAnalyzer();
	virtual ~MaterialAnalyzer();

	void Analyze(FbxSurfaceMaterial* material);

	// アンビエントを取得
	Vector3& GetAmbient();

	// ディフューズを取得
	Vector3& GetDiffuse();

	// スペキュラを取得
	Vector3& GetSpecular();

	// エミッシブを取得
	Vector3& GetEmissive();

	// バンプを取得
	Vector3& GetBump();

	// 透過度を取得
	float GetTransparency();

	// 光沢を取得
	float GetShininess();

	// 反射を取得
	float GetReflectivity();

	// テクスチャファイル名を取得
	const char* GetTextureFileName(PropertyType propertyType);

protected:
	// Lambert情報セット
	void SetLambertInfo(FbxSurfaceLambert* lambert);

	// テクスチャ情報を取得
	void SetTextureInfo(
		FbxSurfaceMaterial* material,
		const char* matFlag,
		char* outTexName);
};