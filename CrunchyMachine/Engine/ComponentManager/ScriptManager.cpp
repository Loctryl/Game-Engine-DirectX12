#include "ScriptManager.h"

ScriptManager::ScriptManager()
{
	mComponentType = SCRIPT;
	mComponents = std::vector<Script*>();

}

ScriptManager::~ScriptManager()
{
	for (auto obj : mComponents) {
		RELPTR(obj);
	}

	mComponents.clear();
}

void ScriptManager::AddComponent(Script* script)
{
	script->OnInit();
	mComponents.push_back(script);

}

void ScriptManager::RemoveComponent(GameObject* go)
{
	for (int i = 0; i < mComponents.size(); i++) {
		if (mComponents[i]->mGameObject == go)
			if (mComponents.size() == 1)
			{
				mComponents[i]->OnDestroy();
				mComponents.clear();
			}
			else 
			{
				mComponents[i]->OnDestroy();
				mComponents.erase(mComponents.begin() + i);
			}
	}
}

void ScriptManager::Update(float deltaTime)
{
	for (auto obj : mComponents) {
		obj->OnUpdate(deltaTime);
	}
}
