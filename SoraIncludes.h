#ifndef SORAINCLUDES_H_
#define SORAINCLUDES_H_

/*

     S O R A
     [Sick of Restarting Again] Engine
     by Rick Chou

     2/16/2014

     APIs/libraries used:
     - OpenGL
     - SDL2
     - SDL_Image
     - Lua
     - Box2D
     - Boost

     Modular game engine of generic functionality.  Will hopefully streamline development process for future projects.

*/

#include "TextureImage.h"
#include "GameContext.h"
#include "StateMachine.h"
#include "State.h"
#include "GraphicsContext.h"
#include "GameInput.h"
#include "DrawContext.h"
#include "EntityContext.h"
#include "Logging.h"
#include "Vector.h"
#include "Macros.h"
#include "ShaderProgram.h"
#include "FileUtil.h"
#include "Factory.h"
#include "TextureFactory.h"
#include "LuaObject.h"
#include "Matrix.h"
#include "EntityManager.h"
#include "PhysicsWorld.h"
#include "Sprite.h"
#include "WorldEntity.h"
#include "Util.h"
#include "AIController.h"
#include "AIEntity.h"
#include "JsonObject.h"
#include "AnimEntity.h"
#include "InstancedParticleEngine.h"
#include "FrameBuffer.h"
#include "CollisionBody.h"
#include "TextureSheet.h"
#include "FontMaterial.h"
#include "FreeTypeContext.h"
#include "FontFactory.h"
#include "QuadTree.h"
#include "CollisionEngine.h"
#include "SoundObject.h"
#include "SoundFactory.h"
#include "SoundContext.h"
#include "TrailsEffect.h"
#include "Level.h"

#endif
