// UVâêÕé“
// 2017.05. 4	: ÉvÉçÉOÉâÉÄçÏê¨
// author		: SyunMizuno



#pragma once

#include	<fbxsdk.h>
#include	"../../../Convert/Convert.h"
#include	"../../../Utility/System/SystemUtility.h"


class UVAnalyzer {
public:
#pragma region struct

	struct UVInfo {
		int			Size;
		Vector2*	Buffer;

		UVInfo() : Size(0), Buffer(0) {}
		~UVInfo() {
			SAFE_DELETE_ARRAY(Buffer);
		}
	};

#pragma endregion

protected:
#pragma region variable

	UVInfo m_UVInfo;
	UVInfo m_DiffuseUV;
	UVInfo m_SpecularUV;
	UVInfo m_AmbientUV;
	UVInfo m_EmissiveUV;

#pragma endregion

public:
	UVAnalyzer();
	virtual ~UVAnalyzer();

	/* UVâêÕ */
	bool Analyze(FbxMesh* mesh);
	bool Analyze(FbxLayer* layer);

	int GetUVNum() const;

	UVInfo& GetUVInfo();

protected:
	bool SetPropertyUV(FbxLayerElementUV* elem, UVInfo& uvInfo);
};