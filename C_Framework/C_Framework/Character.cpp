#include "pch.h"

const string Character::stateStrs[State::kCount] = { "Stay", "Move", "Jump", "Hit", "Dead" };
const string Character::rootPath = "Assets/Character/";

Character::Character(string name)
{
	this->name = name;
	for (int i = 0; i < State::kCount; ++i)
	{
		stateSprs[i] = Sprite(rootPath + name + "/" + stateStrs[i] + "/*.png");
		stateSprs[i].center = D3DXVECTOR2(0.0f, 0.0f);
		if (stateStrs[i] == "Dead" || stateStrs[i] == "Hit")
			stateSprs[i].loopAni = false;
		else if (stateStrs[i] == "Jump")
		{
			stateSprs[i].loopAni = false;
		}
		else
			stateSprs[i].loopAni = true;
	}
}

void Character::AddSkill(Skill* skill)
{
	skills.push_back(skill);
	for (int i = 0; i <= skill->maxPhase; ++i)
	{
		char phaseBuffer[10];
		_itoa(i, phaseBuffer, 10);
		skillSprites[skill->name].push_back(rootPath + name + "/" + skill->name + phaseBuffer + "/*.png");
		skillSprites[skill->name].back().loopAni = false;
		skillSprites[skill->name].back().center = D3DXVECTOR2(0.0f, 0.0f);

	}
}

void Character::Update(float deltaTime)
{
	if (curSkill == nullptr && !IsHit)
	{
		nextState = State::kStay;

		if (moveDir != D3DXVECTOR2(0.0f, 0.0f))
		{
			if (moveDir.y != 0)
				nextState = State::kJump;
			else 
				nextState = State::kMove;
		}
	}
	else if (IsHit)
		nextState = State::kHit;

	if (hp <= 0)
		nextState = State::kDead;

	if (state != nextState)
	{
		stateSprs[state].curScene = 0;
		state = nextState;
	}

	//float leftPos = NowRoom->position.x - 1920.f / 2.f;
	//float topPos = NowRoom->position.y + 1080.f / 2.f;
	//float rightPos = NowRoom->position.x + 1920.f / 2.f - (float)stateSprs[1].ptexs[1]->Info.Height;
	//float bottomPos = NowRoom->position.y - 1080.f / 2.f;

	if(!isBottom)
		moveDir.y -= 2.0f * deltaTime;

	if (state == State::kMove || state == State::kJump)
	{
		position += moveDir * moveSpeed * deltaTime;

	}
	else if (state == State::kHit)
	{
		position.x += moveDir.x * moveSpeed * deltaTime;

		if (moveDir.x != 0.0f)
		{
			if (moveDir.x > 0.0f)
			{
				moveDir.x -= 3.f * deltaTime;

				if (prevDir_x > 0.0f && moveDir.x <= 0.0f)
					moveDir.x = 0.0f;
			}
			else if (moveDir.x < 0.0f)
			{
				moveDir.x += 3.f * deltaTime;

				if (prevDir_x <= 0.0f && moveDir.x > 0.0f)
					moveDir.x = 0.0f;
			}
		}
	}
	
	if (state == State::kSkill)
	{
		if (curSkill != nullptr)
		{
			if (!curSkill->IsCastingProgress())
				nextState = State::kStay;
		}
		else
			nextState = State::kStay;
	}
	else
	{
		if (curSkill)
		{
			auto& curSprite = skillSprites[curSkill->name];

			for (int i = 0; i < (int)curSprite.size(); ++i)
			{
				curSprite[i].curScene = 0;
			}

		}
		curSkill = nullptr;
	}

	for (int i = 0; i < (int)skills.size(); ++i)
	{
		skills[i]->Update(deltaTime);
	}


	if (state != State::kSkill)
	{
		stateSprs[state].Update(deltaTime);
	}
	else
	{
		auto& curSprite = skillSprites[curSkill->name][curSkill->phase];
		curSprite.Update(deltaTime);
	}


	if (state == State::kHit)
	{
		if (!isBottom)
			stateSprs[kHit].curScene = min(stateSprs[kHit].curScene, (int)stateSprs[kHit].ptexs.size() - standUpFream - 1);
		else
			if ((int)stateSprs[kHit].ptexs.size() - 1 == stateSprs[kHit].curScene)
			{
				IsHit = false;
				moveDir.y = 0;
			}
	}
	else
		moveDir.x = 0.0f;

	prevDir_x = moveDir.x;
	isBottom = false;
	position.y -= 1.0f;
}

void Character::OnCollisionInprogress(Object * another, float deltaTime)
{
	if (another->tag == "Wall")
	{
		Wall* wall = static_cast<Wall*>(another);

		switch (wall->kind)
		{
			case 1:
			{
				if (prevPos.x >= wall->position.x && position.x < wall->position.x)
				{
					position.x = wall->position.x;
					moveDir.x = 0;
				}

				return;
			}
			case 2:
			{
				float wallPos = wall->position.y - stateSprs[0].ptexs[0]->Info.Height;
				if (prevPos.y <= wallPos && position.y > wallPos)
				{
					position.y = wallPos;
					moveDir.y = -0.01f;
				}

				return;
			}
			case 3:
			{
				float wallPos = wall->position.x - stateSprs[0].ptexs[0]->Info.Width;
				if (prevPos.x <= wallPos && position.x > wallPos)
				{
					position.x = wallPos;
					moveDir.x = 0;
				}

				return;
			}
			case 4:
			{
				if (prevPos.y >= wall->position.y && position.y < wall->position.y)
				{
					position.y = wall->position.y;
					moveDir.y = 0;
					isBottom = true;
				}

				return;
			}
			case 5:
			{
				if (moveDir.y <= 0)
				{
					if (prevPos.y >= wall->position.y && position.y < wall->position.y)
					{
						position.y = wall->position.y;
						moveDir.y = 0;
						isBottom = true;
					}

					return;
				}
			}
		}

		/*RECT rc1, rc2;
		rc1.left = 0 + wall->position.x;
		rc1.right = rc1.left + wall->spr.ptexs[0]->Info.Width;
		rc1.bottom = 0 + wall->position.y;
		rc1.top = rc1.bottom + wall->spr.ptexs[0]->Info.Height;

		rc2.left = 0 + position.x;
		rc2.right = rc2.left + stateSprs[0].ptexs[0]->Info.Width;
		rc2.bottom = 0 + position.y;
		rc2.top = rc2.bottom + stateSprs[0].ptexs[0]->Info.Height;
		
		if (wall->position.x <= position.x && wall->position.y <= position.y)
		{

		}
		else if (wall->position.x >= position.x && wall->position.y >= position.y)
		{

		}
		else if (wall->position.x < position.x && wall->position.y < position.y)
		{

		}
		else if (wall->position.x < position.x && wall->position.y < position.y)
		{

		}*/

	}
}

void Character::LateUpdate(float deltaTime)
{
	if (moveDir.y == 0)
		stateSprs[State::kJump].curScene = 0;

	prevPos = position;
}

void Character::Render()
{
	if (state != State::kSkill)
	{
		stateSprs[state].pos = position;
		stateSprs[state].Render();
	}
	else
	{
		auto& curSprite = skillSprites[curSkill->name][curSkill->phase];
		curSprite.pos = position;
		curSprite.Render();
	}

	Object::Render();
}

void Character::Casting(string name)
{
	if (state != State::kStay && state != State::kMove)
		return; 

	for (int i = 0; i < (int)skills.size(); ++i)
	{
		if (skills[i]->onCast())
		{
			curSkill = skills[i];
			nextState = State::kSkill;
		}
	}
}

void Character::Hit(int damage, bool knockbackDir)
{
	if (state != State::kDead)
	{
		stateSprs[kHit].curScene = 0;
		hp -= damage;
		IsHit = true;
		moveDir.y = 1;
		moveDir.x = knockbackDir ? -1.f : 1.f;
	}
}
