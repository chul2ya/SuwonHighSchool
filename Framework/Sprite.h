#pragma once

class Sprite
{
public:
	vector<Texture*> ptexs;
	DWORD color = 0xffffffff;
	int a = 255, r = 255, g = 255, b = 255;

	int curScene = 0;
	float aniTime = 0.05f;
	float curAniTime = 0.0f;
	bool loopAni = true;

	D3DXVECTOR2 imageSize = D3DXVECTOR2(0.0f, 0.0f); //�̹��� ũ��  0, 0�̸� �⺻��  �ȼ�����
	D3DXVECTOR2 imageScenePos = D3DXVECTOR2(0.0f, 0.0f); //�̹��� ��� ��ġ  ���� �� ����  �ȼ�����
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 scale = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 scaleAnchor = D3DXVECTOR2(0.0f, 0.0f);
	float rotate = 0.0f;
	D3DXVECTOR2 rotateAnchor = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 center = D3DXVECTOR2(0.5f, 0.5f);

	Sprite();
	Sprite(string path, D3DXVECTOR2 imagesize);
	Sprite(string path);
	virtual ~Sprite();

	void Update(float deltaTime);
	void Render();


};

