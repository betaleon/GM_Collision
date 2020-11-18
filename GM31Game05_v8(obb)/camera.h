#pragma once
#include "game_object.h"

class CCamera:public CGameObject
{

private:
	D3DXVECTOR3 m_Target;
	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectionMatrix;

public:
	CCamera(){}
	~CCamera(){}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() {return m_ViewMatrix;}
	bool CheckView(D3DXVECTOR3 Position);
};