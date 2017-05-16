// 仮のシーン
// 2016. 5.10	:	プログラム作成
// author		:	SyunMizuno


#pragma once



#include	"../GameFramework/framework/Scene/Base/SceneBase.h"

#include	"../GameFramework/framework/Light/Light.h"
#include	"../GameFramework/framework/Resource/Texture/Texture.h"
#include	"../GameFramework/framework/Object/3DObject/Object3D.h"
#include	"../GameFramework/framework/Resource/Shader/Base/Shader.h"
#include	"../GameFramework/framework/Object/3DObject/Quad/Quad.h"


class CheckScene	:	public	SceneBase {
private:
	Light* m_pLight;
	Shader*	m_pShader;
	Quad*	m_pQuad;
	Object3D* m_pObj;

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
};