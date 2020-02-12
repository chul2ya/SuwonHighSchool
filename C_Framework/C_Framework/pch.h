#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

#include <map>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

#include "Time.h"

#include "Direct3D.h"
#include "TextureManager.h"
#include "Sprite.h"

#include "Object.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Room.h"
#include "RoomManager.h"
#include "HitEffect.h"
#include "SkillObject.h"
#include "Skill.h"
#include "Kick.h"
#include "Wall.h"
#include "Character.h"
#include "Portal.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerManager.h"

#include "Scene.h"
#include "GameScene.h"