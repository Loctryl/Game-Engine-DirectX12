# Game Engine DirectX12

## Context
This is a student project with a team of 4 people, during 3 weeks. (October 2023)
The goal was to learn about making game engine in C++. We started it from scratch, only with the DirectX12 API. In a second time, we had to develop a game with this engine, and it had to be a first person space shooter. As the time was really restricted, there’s no editor for this engine. Everything is done in the code.

## Engine
We first implemented an ECS system, inspired by Unity's system. Each component is referenced in a list so the Rendering Manager and the Physic Manager can iterate on their purpose list.

- The Transform component is inherent to every game object. It manages the position, rotation and scale of the object. Those 3 settings are put together in a matrix for the rendering.
- The RenderComponent provides the possibility to display the object, with a define geometry, shader (with or without lightning), and texture. 
    - The geometries are created at the beginning of the program and then referenced for each component which needs it. There’re 3 available geometries : box, sphere and diamond.
    - For the shader, it is written in HLSL and is compiled once, before being used for different objects thanks to some settings as the texture.

- The PhysicComponent to simulate the collisions between the game objects. They have a bitmask that works as a layer to filter the objects that collide and those who don’t. The PhysicManager also divide the space to avoid checking the collision between 2 objects that are factually too far from each other to collide. Those 2 optimization systems allow pretty good performances, even with thousands of game objects.
    - To complete the PhysicComponent, there’s also a Rigidbody component. Here, it essentially simulate some space velocity physic, and in case of a collision to apply invert velocity.

Finally, we added a prototype of a ParticleEmitter, which use only 1 draw call, and allow a loop emission with a definite number of particles.
We also started to create a simple UI system, but it still really specific to the current use. 

There are 3 specific unique game objects : the perspective camera, for the viewpoint, the orthographic camera, for the UI, and a skybox.

## The game
As said, it is a first person space shooter, looking like an arcade game. 

We build the spaceship from 4 diamond shape objects and a sphere at the center.

There are asteroids that are coming to us linearly. We can freely move but in a defined area around those asteroids. We can shoot them to earn points and they deal damage to us if we hit them.
Finally, there are some enemies, that chase us, that we can shoot to destroy but they flee if we let them with low HP. It’s a simple state machine behind their behaviour.

![image](https://github.com/Loctryl/Game-Engine-DirectX12/assets/91985442/939bb035-0307-4585-b63d-0bd186cb843d)

### Inputs

- Z : Forward
- S : Backward
- Q : Left
- D : Right
- Space : Up
- Shift : Down
- A : Rotate left
- E : Rotate right
- Mouse : Aim/camera
- Mouse left clic : Shoot
