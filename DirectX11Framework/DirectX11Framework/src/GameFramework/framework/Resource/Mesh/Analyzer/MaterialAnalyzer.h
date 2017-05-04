// �}�e���A����͎�
// 2017.05. 4	: �v���O�����쐬
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

	// �A���r�G���g���擾
	Vector3& GetAmbient();

	// �f�B�t���[�Y���擾
	Vector3& GetDiffuse();

	// �X�y�L�������擾
	Vector3& GetSpecular();

	// �G�~�b�V�u���擾
	Vector3& GetEmissive();

	// �o���v���擾
	Vector3& GetBump();

	// ���ߓx���擾
	float GetTransparency();

	// ������擾
	float GetShininess();

	// ���˂��擾
	float GetReflectivity();

	// �e�N�X�`���t�@�C�������擾
	const char* GetTextureFileName(PropertyType propertyType);

protected:
	// Lambert���Z�b�g
	void SetLambertInfo(FbxSurfaceLambert* lambert);

	// �e�N�X�`�������擾
	void SetTextureInfo(
		FbxSurfaceMaterial* material,
		const char* matFlag,
		char* outTexName);
};