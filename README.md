# Game Engine DirectX12

## Context
This is a student project with a team of 4 people, during 3 weeks.

The first goal was to learn about making game engine. We stated it from scratch, only with the DirectX12 API.
In a second time, we had to develop a game with this engine, and it had to be a first person space shooter.

## The engine
We first implemented an ECS system, inspired by Unity's system.

### Available components and sub-features : 
- Transform
- RenderComponent :
    - Mesh Geometry
    - Shader
          - Lightning
    - Texture
- PhysicComponent :
    - Bitmask
- RigidBody
- ParticleEmitter

We also started to create a simple UI system, but it still really specific to the current use.
We finally added some special game objects as a camera (Perspective or Orthographic) and a skybox.

## The game
As said, it is a first person space shooter, looking like an arcade game.
There are asteroids that are coming on us linearly. We're can freely move in a defined area around those asteroids.
We can shoot them to earn points and they deal damage on us.

Finally, there are some enemies (and yes, they look as T.I.E), that chase us.

![image](https://github.com/Loctryl/Game-Engine-DirectX12/assets/91985442/939bb035-0307-4585-b63d-0bd186cb843d)
