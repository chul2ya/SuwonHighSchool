#include "pch.h"

void Object::Render()
{
	if (collisionLine.size() < 2)
		return;

	auto pLine = Direct3D::GetInstance()->pLine;

	pLine->SetWidth(1.0f);
	pLine->SetAntialias(true);
	D3DXVECTOR3* collisionBox = new D3DXVECTOR3[collisionLine.size()];
	int i = 0;
	for (auto it = collisionLine.begin(); it != collisionLine.end(); ++it, ++i)
	{
		collisionBox[i] = D3DXVECTOR3((*it).x, (*it).y, 0.0f) + D3DXVECTOR3(position.x, position.y, 0.f);
	}
	//circle[collisionLine.size()] = D3DXVECTOR3(collisionLine.front().x, collisionLine.front().y, 0.0f) + D3DXVECTOR3(position.x, position.y, 0.f);

	D3DXMATRIX lineMat = Direct3D::GetInstance()->viewMat * Direct3D::GetInstance()->projMat;

	pLine->Begin();
	HRESULT hr = pLine->DrawTransform(collisionBox, collisionLine.size(), &lineMat, D3DCOLOR_ARGB(255, 255, 0, 0));
	pLine->End();
	//pLine->DrawTransform(circle, 36, &mat, D3DCOLOR_ARGB(255, 255, 255, 255));

	delete collisionBox;
}

void Object::SetCollision(Sprite * spr)
{
	collisionLine.clear();

	float x = spr->ptexs[0]->Info.Width * spr->scale.x, y = spr->ptexs[0]->Info.Height * spr->scale.y;

	collisionLine.push_back(D3DXVECTOR2(-x * spr->center.x, -y * spr->center.y));
	collisionLine.push_back(D3DXVECTOR2(-x * spr->center.x, y * (1 - spr->center.y)));
	collisionLine.push_back(D3DXVECTOR2(x * (1 - spr->center.x), y * (1 - spr->center.y)));
	collisionLine.push_back(D3DXVECTOR2(x * (1 - spr->center.x), -y * spr->center.y));
	collisionLine.push_back(D3DXVECTOR2(-x * spr->center.x, -y * spr->center.y));
}
