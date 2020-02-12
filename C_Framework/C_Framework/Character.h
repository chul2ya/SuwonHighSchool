#pragma once
class Character : public GameObject
{
protected:
public:
	int hp = 10;
	enum State
	{
		kStay,
		kMove,
		kJump,
		kHit,
		kDead,
		kCount,
		kSkill
	};
	State state = State::kStay;
	State nextState = State::kStay;
	Sprite stateSprs[State::kCount];
	string name;
	string enemyTag = "";

	vector<Skill*> skills;
	map<string, vector<Sprite>> skillSprites;
	Skill* curSkill = nullptr;

	float moveSpeed = 1200.f;
	float prevDir_x = 0.0f;

	int standUpFream = 0;
	bool IsHit = false;
	bool isBottom = false;

	D3DXVECTOR2 prevPos = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 moveDir = D3DXVECTOR2(0.0f, 0.0f);

	static const string stateStrs[State::kCount];
	static const string rootPath;

	Character(string name);

	void AddSkill(Skill* skill);

	virtual void Update(float deltaTime);
	virtual void OnCollisionInprogress(Object* another, float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render();

	void Casting(string name);
	void Hit(int damage, bool kbockbackDir);
};

