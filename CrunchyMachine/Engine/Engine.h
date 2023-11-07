#pragma once
#include <iostream>
#include <vector>
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
// Also provides base fonctions for game objects to manage their components.
class Engine
{
public:
    Engine();
    ~Engine();

    // Global game object call to add a component with a given type.
    template <class T = Component>
    void  AddComponent(T* component);

    template <class T = Component>
    T* GetComponent(ComponentType componentType, GameObject* go);

    void Update(float deltaTime);

    bool  HasComponent(ComponentType componentType, GameObject* go);
    void  RemoveComponent(ComponentType componentType, GameObject* go);
    void  DeleteGameObject(GameObject* go);

    static Engine* GetInstance();

    PhysicsManager* mPhysicsManager;
    RenderManager* mRenderManager;
    StateMachineManager* mStateMachineManager;

private:
    static Engine* mInstance;
};

template <class T>
T* Engine::GetComponent(ComponentType componentType, GameObject* go)
{
    switch (componentType)
    {
    case(PHYSICS):
        return reinterpret_cast<T*>(mPhysicsManager->GetComponent(go));
        break;

    case(RENDER):
        return reinterpret_cast<T*>(mRenderManager->GetComponent(go));
        break;

    case(STATEMACHINE):
        return reinterpret_cast<T*>(mStateMachineManager->GetComponent(go));
        break;
    default:
        break;
    }
}

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

    case(STATEMACHINE):
        mStateMachineManager->AddComponent(reinterpret_cast<StateMachineComponent*>(component));
        break;
    default:
        break;
    }
}