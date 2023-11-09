#pragma once
#include "ComponentManager/RenderManager.h"
#include "ComponentManager/Physics/PhysicsManager.h"
#include "ComponentManager/StateMachine/StateMachineManager.h"
#include "Component/Component.h"


class PhysicsComponent;
class RenderComponent;
class StateMachineComponent;
class GameObject;

enum ComponentType;

// Main class and singleton.
// Manages all the component managers.
// Also provides base functions for game objects to manage their components.
class Engine
{
private:
    static Engine* mInstance;
    
public:
    PhysicsManager* mPhysicsManager;
    RenderManager* mRenderManager;
    StateMachineManager* mStateMachineManager;
    
    Engine();
    ~Engine();
    
    static Engine* GetInstance();

    // Global game object call to add a component with a given type.
    template <class T = Component>
    void  AddComponent(T* component);

    template <class T = Component>
    T* GetComponent(ComponentType componentType, GameObject* go);

    void Update(float deltaTime) const;

    bool  HasComponent(ComponentType componentType, GameObject* go) const;
    void  RemoveComponent(ComponentType componentType, GameObject* go) const;
    void  DeleteGameObject(GameObject* go) const;
};


template <class T>
void Engine::AddComponent(T* component)
{
    switch (component->mComponentType)
    {
    case(PHYSICS):
        mPhysicsManager->AddComponent(reinterpret_cast<PhysicsComponent*>(component));
        break;
    case(RENDER):
        mRenderManager->AddComponent(reinterpret_cast<RenderComponent*>(component));
        break;
    case(STATE_MACHINE):
        mStateMachineManager->AddComponent(reinterpret_cast<StateMachineComponent*>(component));
        break;
    default:
        break;
    }
}

template <class T>
T* Engine::GetComponent(ComponentType componentType, GameObject* go)
{
    switch (componentType)
    {
    case(PHYSICS):
        return reinterpret_cast<T*>(mPhysicsManager->GetComponent(go));
    case(RENDER):
        return reinterpret_cast<T*>(mRenderManager->GetComponent(go));
    case(STATE_MACHINE):
        return reinterpret_cast<T*>(mStateMachineManager->GetComponent(go));
    default:
        return nullptr;
    }
}