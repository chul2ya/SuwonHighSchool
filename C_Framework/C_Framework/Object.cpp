#include "pch.h"

void Object::Render()
{
	if (collisionLine.size() < 2)
		return;

	auto pLine = Direct3D::GetInstance()->pLine;

	pLine->SetWidth(1.0f);
	pLine->SetAntialias(true);
	D3DXVECTOR3* circle = new D3DXVECTOR3[collisionLine.size()];
	int i = 0;
	for (auto it = collisionLine.begin(); it != collisionLine.end(); ++it, ++i)
	{
		circle[i] = D3DXVECTOR3((*it).x, (*it).y, 0.0f) + D3DXVECTOR3(position.x, position.y, 0.f);
	}
	//circle[collisionLine.size()] = D3DXVECTOR3(collisionLine.front().x, collisionLine.front().y, 0.0f) + D3DXVECTOR3(position.x, position.y, 0.f);

	D3DXMATRIX lineMat = Direct3D::GetInstance()->viewMat * Direct3D::GetInstance()->projMat;

	pLine->Begin();
	HRESULT hr = pLine->DrawTransform(circle, collisionLine.size(), &lineMat, D3DCOLOR_ARGB(255, 255, 0, 0));
	pLine->End();
	//pLine->DrawTransform(circle, 36, &mat, D3DCOLOR_ARGB(255, 255, 255, 255));

	delete circle;
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

void Object::SetCollisionAngle(D3DXVECTOR2 center, float angle)
{
	//for (auto it = collisionLine.begin(); it != collisionLine.end(); ++it)
	//{
	//	float dir = atan2f((*it).y - center.y, (*it).x - center.x) * 180.f / D3DX_PI;
	//	float dis = sqrtf((center.x - (*it).x)*(center.x - (*it).x) + (center.y - (*it).y)*(center.y - (*it).y));
	//	(*it) = D3DXVECTOR2(dis * (cosf((angle - dir) / 180.f * D3DX_PI)), (*it).y * (sinf((angle - dir) / 180.f * D3DX_PI)));
	//}
}
