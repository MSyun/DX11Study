// �Q�[���pDirectX11
// 2016. 5.10	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"CheckScene.h"
#include	"../GameFramework/framework/Graphic/Graphics.h"
#include	"../GameFramework/framework/Convert/Convert.h"
#include	<d3dcompiler.h>
#include	<tchar.h>
#include	"../GameFramework/framework/Time/Time.h"

struct SimpleVertex {
	Point3 Pos;
	Vector3 Normal;
	Vector2 Tex;
};

struct SIMPLESHADER_CONSTANT_BUFFER {
	Matrix	mWorld;
	Matrix	mWVP;
	Vector4	vLightDir;
	Vector4	vDiffuse;
	Vector4	vEye;
};


CheckScene::CheckScene() :
	m_pVertexBuffer(nullptr),
	m_pCamera(nullptr),
	m_pLight(nullptr)
{
}

CheckScene::~CheckScene() {

}

bool CheckScene::Init() {
	CreatePolygon();

	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/Watch/Watch.pmd");
//	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/miku/kio_miku_20111121.pmd");
//	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/miku1/�����~�N_�A�m�}��ver.pmd");
//	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/miku2/�����~�N@���t1052��.pmd");
	m_pShader = GetResourceManager<Shader>()->Create("Phong.hlsl");

	return true;
}

void CheckScene::Release() {
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pLight);

	SAFE_RELEASE(m_pVertexBuffer);
}

void CheckScene::Update() {

}

void CheckScene::Draw() {
	auto context = Graphics::GetDevice();

	Matrix mWorld;
	// ���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	static float an = 0.0f;
	an -= Time::GetDeltaTime();
	MatrixRotationY(&mWorld, an);

	// �J����
	m_pCamera->Set();
	Vector3 pos = m_pCamera->GetTransform()->GetPos();

	// �g�p����V�F�[�_�̓o�^
	context->VSSetShader(m_pShader->GetVertexShader(), NULL, 0);
	context->PSSetShader(m_pShader->GetPixelShader(), NULL, 0);
	// �V�F�[�_�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	HRESULT hr;

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Graphics::GetDevice()->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&stride,
		&offset);

	auto constantBuffer = m_pShader->GetConstantBuffer();
	hr = context->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		cb.mWorld = mWorld;
		MatrixTranspose(&cb.mWorld, &cb.mWorld);
		// ���[���h�A�J�����A�ˉe�s���n��
		Matrix m = mWorld * m_pCamera->GetView() * m_pCamera->GetProj();
		MatrixTranspose(&m, &m);
		cb.mWVP = m;
		// �J���[��n��
		cb.vDiffuse = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		// ���C�g�x�N�g����n��
		cb.vLightDir = m_pLight->GetDirection4();
		// �J�����̈ʒu�i���_�j���V�F�[�_�ɓn��
		cb.vEye = Vector4(pos.x, pos.y, pos.z, 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		context->Unmap(constantBuffer, 0);
	}
	// ���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�̓o�^
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
	context->PSSetConstantBuffers(0, 1, &constantBuffer);

	// ���_�C���v�b�g���C�A�E�g���Z�b�g
	context->IASetInputLayout(m_pShader->GetVertexLayout());
	// �v���~�e�B�u�E�g�|���W�[���Z�b�g
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���\���V�F�[�_�ɓn��
	auto samp = m_pTexture->GetSample();
	auto tex = m_pTexture->GetTexture();
	context->PSSetSamplers(0, 1, &samp);
	context->PSSetShaderResources(0, 1, &tex);

	// �v���~�e�B�u�������_�����O
	//context->Draw(4, 0);

	m_pMesh->Draw(m_pCamera, m_pLight);
}


void CheckScene::CreatePolygon() {
	HRESULT hr;
	ID3D11Device* device = IResource::GetDevice();

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	SimpleVertex vertices[] = {
		Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 1),
		Vector3(-0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 0),
		Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 1),
		Vector3(0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 0),
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	hr = device->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (FAILED(hr))	return;

	// �o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Graphics::GetDevice()->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&stride,
		&offset);

	m_pTexture = GetResourceManager<Texture>()->Create("data/Texture/Sprite.jpg");
	m_pCamera = NEW Camera;
	m_pCamera->GetTransform()->SetPos(0.0f, 1.0f, -4.0f);
//	m_pCamera->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);
	m_pLight = NEW Light;
	m_pLight->GetTransform()->SetPos(0.0f, 1.0f, -2.0f);
	m_pLight->GetTransform()->Rotate(-20.0f, 0.0f, 0.0f);
}