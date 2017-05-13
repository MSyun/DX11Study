// 仮のシーン
// 2016. 5.10	:	プログラム作成
// author		:	SyunMizuno


#pragma once



#include	"../GameFramework/framework/Scene/Base/SceneBase.h"

#include	"../GameFramework/framework/Resource/Manager/ResourceManager.h"
#include	"../GameFramework/framework/Camera/Camera.h"
#include	"../GameFramework/framework/Light/Light.h"
#include	"../GameFramework/framework/Resource/Texture/Texture.h"
#include	"../GameFramework/framework/Resource/Mesh/Mesh.h"
#include	"../GameFramework/framework/Resource/Shader/Base/Shader.h"


class CheckScene	:	public	SceneBase {
private:
	ID3D11Buffer*		m_pVertexBuffer;

	Texture*			m_pTexture;
	Mesh*				m_pMesh;
	Shader*				m_pShader;
	Camera*				m_pCamera;
	Light*				m_pLight;

public:
	CheckScene();
	virtual ~CheckScene();

	void Update() final;
	void Draw() final;
	bool ReStart() final {
		return true;
	}

protected:
	bool Init() final;
	void Release() final;

	void CreatePolygon();
};