#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "bullet.h"
#include "explosion.h"
#include "input.h"
#include "scene.h"


CModel* CBullet::m_Model;

void CBullet::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\cube.obj");
}

void CBullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}


void CBullet::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
}

void CBullet::Uninit()
{

}

void CBullet::Update()
{

	m_Position.z += 0.1f;

	if (m_Position.z > 10.0f)
	{
		SetDestroy();
		return;
	}

	CScene* scene = CManager::GetScene();
	std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);

	for (CEnemy* enemy : enemyList)
	{
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();
		D3DXVECTOR3 direction = m_Position - enemyPosition;

		D3DXVECTOR3 obbx, obby, obbz;
		float obbLenx, obbLeny, obbLenz;

		obbx = enemy->GetObbX();
		obbLenx = D3DXVec3Length(&obbx);
		obbx /= obbLenx;

		obby = enemy->GetObbY();
		obbLeny = D3DXVec3Length(&obby);
		obby /= obbLeny;

		obbz = enemy->GetObbZ();
		obbLenz = D3DXVec3Length(&obbz);
		obbz /= obbLenz;

		float lenX, lenY, lenZ;
		lenX = D3DXVec3Dot(&obbx, &direction);
		lenY = D3DXVec3Dot(&obby, &direction);
		lenZ = D3DXVec3Dot(&obbz, &direction);

		if (fabs(lenX) < obbLenx && fabs(lenY) < obbLeny && fabs(lenZ) < obbLenz)
		{
			enemy->SetDestroy();
			SetDestroy();
			return;
		}
		//球体と点の当たり判定
		//float length = D3DXVec3Length(&direction);
		//
		//if (length < 1.5f)
		//{
		//	scene->AddGameObject<CExplosion>(1)->SetPosition(m_Position);
		//
		//	enemy->SetDestroy();
		//	SetDestroy();
		//	return;
		//}
	}

}

void CBullet::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}