#include "Game.h"

SceneManager::~SceneManager()
{
	for (auto sceneMap : mScenes)
	{
		sceneMap.second->Release();
		delete sceneMap.second;
	}
	mScenes.clear();
}

void SceneManager::AddObject(Object * object)
{
	if (!mCurScene)
	{
		assert(0);
		return;
	}
	mCurScene->mObjectManager.AddObject(object);
}

void SceneManager::AddScene(wstring sceneName, Scene * scene)
{
	auto sf = mScenes.find(sceneName);
	if (sf != mScenes.end())
	{
		assert(0);
		return;
	}
	auto is = mScenes.insert(make_pair(sceneName, scene));
	is.first->second->Create();
}

void SceneManager::DelScene(wstring sceneName)
{
	auto sf = mScenes.find(sceneName);
	if (sf == mScenes.end())
	{
		assert(0);
		return;
	}
	mScenes.erase(sf);
	sf->second->Release();
	delete sf->second;
}

void SceneManager::ChangeScene(wstring sceneName)
{
	if (mNextScene != nullptr)
		return;

	auto sf = mScenes.find(sceneName);
	if (sf != mScenes.end())
		mNextScene = sf->second;
}

void SceneManager::UpdateScene(float deltaTime)
{
	if (mNextScene)
	{
		mNextScene->Init();
		if (mCurScene)
			mCurScene->Term();
		mCurScene = mNextScene;
		mNextScene = nullptr;
	}

	if (mCurScene)
	{
		mCurScene->Update(deltaTime);
		mCurScene->mObjectManager.Update(deltaTime);
	}
}

void SceneManager::RenderScene()
{
	if (mCurScene)
	{
		mCurScene->mObjectManager.Render();
		mCurScene->Render();
	}
}

