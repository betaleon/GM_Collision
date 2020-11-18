#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "input.h"
#include "scene.h"
#include "camera.h"


void CPlayer ::Init()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\horse_v3.obj");

	m_Position = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}

void CPlayer::Uninit()
{

	m_Model->Unload();
	delete m_Model;

}

void CPlayer::Update()
{

	if (CInput::GetKeyPress('A'))	//VK_SHIFT��SHIFT�ɑΉ��@VK_SHIFT�̒�`�Ɉړ��ő�̃L�[�R�[�h�킩��
	{
		m_Position.x -= 0.1f;
	}

	if (CInput::GetKeyPress('D'))
	{
		m_Position.x += 0.1f;
	}

	if (CInput::GetKeyPress('S'))
	{
		m_Position.z -= 0.1f;
	}

	if (CInput::GetKeyPress('W'))
	{
		m_Position.z += 0.1f;
	}

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		CScene* scene = CManager::GetScene();
		scene->AddGameObject<CBullet>(1)->SetPosition(m_Position);
	}

}

void CPlayer::Draw()
{
	//������J�����O
	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject<CCamera>(0);
	if (!camera->CheckView(m_Position)) return;
	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}