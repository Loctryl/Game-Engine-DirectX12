#include "PhysicsManager.h"
#include "Engine/GameObject.h"
#include "Engine/Component/Transform.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"

PhysicsManager::PhysicsManager()
{
    mComponentType = PHYSICS;
    mComponents = std::vector<PhysicsComponent*>();
}

void PhysicsManager::CalculateNewPositions(float deltaTime) const
{
    for (auto obj : mComponents)
        if (obj)
            obj->Move(deltaTime);
}

void PhysicsManager::ReCalculatePositions(PhysicsComponent* pc1, PhysicsComponent* pc2, float dist)
{
    Transform* transform1 = GetRootTransform(pc1);
    Transform* transform2 = GetRootTransform(pc2);

    XMFLOAT3 pos1 = transform1->GetWorldPosition();
    XMFLOAT3 pos2 = transform2->GetWorldPosition();

    //direction of pos1 to pos2
    XMFLOAT3 direction = {pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z};

    XMVECTOR vecDirection = XMLoadFloat3(&direction);
    vecDirection = XMVector4Normalize(vecDirection);

    XMStoreFloat3(&direction, vecDirection * dist / 2);

    if (pc1->mIsStatic)
        if (!pc2->mIsStatic)
        {
            pc2->GetTransform()->Translate(direction.x * -1, direction.y * -1, direction.z * -1);
            pc2->AddVelocity(direction.x * -2, direction.y * -2, direction.z * -2);
        }
    else if (pc2->mIsStatic)
        if (!pc1->mIsStatic)
        {
            pc1->GetTransform()->Translate(direction.x * 1, direction.y * 1, direction.z * 1);
            pc1->AddVelocity(direction.x * 2, direction.y * 2, direction.z * 2);
        }
    else
    {
        pc1->AddVelocity(direction);
        pc2->AddVelocity(direction.x * -1, direction.y * -1, direction.z * -1);
    }
}

void PhysicsManager::CheckCollision(float deltaTime)
{
    //get camera position
    XMFLOAT3 cam = GameObjectManager::GetInstance()->GetCamera()->mTransform->GetWorldPosition();

    for (int i = 0; i < mComponents.size(); i++)
    {
        PhysicsComponent* iComponent = mComponents[i];

        //If the component need to be destroy don't check collsion
        if (iComponent->mGameObject->mToDestroy)
            continue;

        XMFLOAT3 iPos = iComponent->GetTransform()->GetWorldPosition();

        //do not test collision if the object is too far away of the camera
        if (std::abs(iPos.x - cam.x) < MAX_COLLISION_DIST &&
            std::abs(iPos.y - cam.y) < MAX_COLLISION_DIST &&
            std::abs(iPos.z - cam.z) < MAX_COLLISION_DIST)

            for (int j = i + 1; j < mComponents.size(); j++)
            {
                PhysicsComponent* jComponent = mComponents[j];

                //If the component need to be destroy don't check collsion
                if (jComponent->mGameObject->mToDestroy)
                    continue;

                //Avoid collision check with parents
                if (iComponent->mGameObject->GetParent() == jComponent->mGameObject)
                    continue;

                //Avoid collision check with children
                if (jComponent->mGameObject->GetParent() == iComponent->mGameObject)
                    continue;

                //Test if the iComponent and the jComponent have a common collision mask, otherwise don't check collision
                if (iComponent->HasCommonMask(jComponent->GetBitMask()))
                {
                    //Get grid position of each component.
                    XMFLOAT3 iGridPos = iComponent->mGridPos;
                    XMFLOAT3 jGridPos = jComponent->mGridPos;

                    //Get the grid size of each component.
                    int iGridSize = std::ceilf(iComponent->GetRadius() * 2 / GRID_SIZE);
                    int jGridSize = std::ceilf(jComponent->GetRadius() * 2 / GRID_SIZE);

                    //test distance to avoid useless collision test.
                    if (std::abs(iGridPos.x - jGridPos.x) < iGridSize + jGridSize &&
                        std::abs(iGridPos.y - jGridPos.y) < iGridSize + jGridSize &&
                        std::abs(iGridPos.z - jGridPos.z) < iGridSize + jGridSize)
                    {
                        //cout << "test collision  {" << iGridPos.x << " ," << iGridPos.y << " ," << iGridPos.y << "} : {" << jGridPos.x << " ," << jGridPos.y << " ," << jGridPos.y << "}" << endl;

                        //Test collision here
                        float dist = iComponent->GetDistanceBetween(jComponent);
                        if (dist < 0)
                        {
                            //Adapt position of the two game objects if they are both rigids
                            if (iComponent->IsRigid() && jComponent->IsRigid())
                                ReCalculatePositions(iComponent, jComponent, dist);

                            iComponent->mGameObject->OnCollision(jComponent->mGameObject);
                            jComponent->mGameObject->OnCollision(iComponent->mGameObject);
                        }
                    }
                }
            }
    }
}

void PhysicsManager::Update(float deltaTime)
{
    CalculateNewPositions(deltaTime);
    CheckCollision(deltaTime);
}

Transform* PhysicsManager::GetRootTransform(PhysicsComponent* physicsComponent)
{
    GameObject* go1 = physicsComponent->mGameObject;

    bool isRootFind = false;

    if (!go1->IsIndependent())
        while (!isRootFind)
        {
            GameObject* newGo = go1->GetParent();
            if (newGo)
            {
                if (newGo->IsIndependent())
                    isRootFind = true;

                go1 = newGo;
            }
            else
                isRootFind = true;
        }

    return go1->mTransform;
}