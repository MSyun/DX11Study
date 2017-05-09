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


class CheckScene	:	public	SceneBase {
private:
	ID3D11InputLayout*	m_pVertexLayout;
	ID3D11VertexShader*	m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;
	ID3D11Buffer*		m_pConstantBuffer;

	ID3D11Buffer*		m_pVertexBuffer;

	Texture*			m_pTexture;
	Mesh*				m_pMesh;
	Camera*				m_pCamera;
	Light*				m_pLight;


public:
	CheckScene();
	virtual ~CheckScene();

	void Update() override;
	void Draw() override;
	bool ReStart() override {
		return true;
	}

protected:
	bool Init() override;
	void Release() override;

	void CreateShader();
	void CreatePolygon();
};