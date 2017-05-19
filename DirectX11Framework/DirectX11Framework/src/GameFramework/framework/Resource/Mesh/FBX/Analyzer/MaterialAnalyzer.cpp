// マテリアル解析者
// 2017.05. 4	: プログラム作成
// author		: SyunMizuno


#include	"MaterialAnalyzer.h"


namespace MSLib {

	MaterialAnalyzer::MaterialAnalyzer() :
		m_Transparency(0.0f),
		m_Shiniess(0.0f),
		m_Reflectivity(0.0f)
	{

	}

	MaterialAnalyzer::~MaterialAnalyzer() {

	}


	void MaterialAnalyzer::Analyze(FbxSurfaceMaterial* material) {
		// LambertかPhongか
	//	if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
			// Lambert
		FbxSurfaceLambert* lambert = (FbxSurfaceLambert*)material;
		SetLambertInfo(lambert);
		//	} else
		//	if (material->GetClassId().Is(FbxSurfacePhong::ClassId)) {
				// Phong
		FbxSurfacePhong* phong = (FbxSurfacePhong*)material;
		SetLambertInfo(phong);	// PhongはLambertを継承してる

		// スペキュラ
		m_Specular.r = (float)phong->Specular.Get()[0];
		m_Specular.g = (float)phong->Specular.Get()[1];
		m_Specular.b = (float)phong->Specular.Get()[2];
		//		SetTextureInfo(phong, FbxSurfaceMaterial::sSpecular, m_SpecularTexName);

				// 光沢
		m_Shiniess = (float)phong->Shininess.Get();

		// 反射
		m_Reflectivity = (float)phong->ReflectionFactor.Get();
		//	}
	}


	void MaterialAnalyzer::SetLambertInfo(FbxSurfaceLambert* lambert) {
		// アンビエント
		m_Ambient.r = (float)lambert->Ambient.Get()[0];
		m_Ambient.g = (float)lambert->Ambient.Get()[1];
		m_Ambient.b = (float)lambert->Ambient.Get()[2];
		//	SetTextureInfo(lambert, FbxSurfaceMaterial::sAmbient, m_AmbientTexName);

			// ディフューズ
		m_Diffuse.r = (float)lambert->Diffuse.Get()[0];
		m_Diffuse.g = (float)lambert->Diffuse.Get()[1];
		m_Diffuse.b = (float)lambert->Diffuse.Get()[2];
		//	SetTextureInfo(lambert, FbxSurfaceMaterial::sDiffuse, m_DiffuseTexName);

			// エミッシブ
		m_Emissive.r = (float)lambert->Emissive.Get()[0];
		m_Emissive.g = (float)lambert->Emissive.Get()[1];
		m_Emissive.b = (float)lambert->Emissive.Get()[2];
		//	SetTextureInfo(lambert, FbxSurfaceMaterial::sEmissive, m_EmissiveTexName);

			// バンプ
		m_Bump.r = (float)lambert->Bump.Get()[0];
		m_Bump.g = (float)lambert->Bump.Get()[1];
		m_Bump.b = (float)lambert->Bump.Get()[2];
		//	SetTextureInfo(lambert, FbxSurfaceMaterial::sBump, m_BumpTexName);

			// 透過度
		m_Transparency = (float)lambert->TransparencyFactor.Get();
	}


	void MaterialAnalyzer::SetTextureInfo(
		FbxSurfaceMaterial* material,
		const char* matFlag,
		char* outTexName)
	{
		FbxProperty pro = material->FindProperty(matFlag);
		//int layerNum = pro.GetSrcObjectCount(FbxLayeredTexture::ClassId);
		//if (layerNum == 0) {
		//	int numGeneralTexture = pro.GetSrcObjectCount(FbxTexture::ClassId);
		//	for (int i = 0; i < numGeneralTexture; ++i) {
		//		FbxTexture* texture = FbxCast<FbxTexture>(pro.GetSrcObject(FbxTexture::ClassId, i));
		//		const char* fileName = texture->GetFileName();
		//		size_t size = strlen(fileName);
		//		memcpy(outTexName, fileName, size);
		//		outTexName[size] = '\0';

		//		break;	// とりあえず今は1枚だけサポート
		//	}
		//}
	}


	Vector3& MaterialAnalyzer::GetAmbient() {
		return m_Ambient;
	}


	Vector3& MaterialAnalyzer::GetDiffuse() {
		return m_Diffuse;
	}


	Vector3& MaterialAnalyzer::GetSpecular() {
		return m_Specular;
	}

	Vector3& MaterialAnalyzer::GetEmissive() {
		return m_Emissive;
	}

	Vector3& MaterialAnalyzer::GetBump() {
		return m_Bump;
	}

	float MaterialAnalyzer::GetTransparency() {
		return m_Transparency;
	}

	float MaterialAnalyzer::GetShininess() {
		return m_Shiniess;
	}

	float MaterialAnalyzer::GetReflectivity() {
		return m_Reflectivity;
	}

	const char* MaterialAnalyzer::GetTextureFileName(MaterialAnalyzer::PropertyType propertyType) {
		switch (propertyType) {
		case PropertyType_Ambient:	return m_AmbientTexName;
		case PropertyType_Diffuse:	return m_DiffuseTexName;
		case PropertyType_Specular:	return m_SpecularTexName;
		case PropertyType_Emissive:	return m_EmissiveTexName;
		case PropertyType_Bump:		return m_BumpTexName;
		default:
			return "";
		};
		return "";
	}

}