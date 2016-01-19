#ifndef __STDAFX_H
#define __STDAFX_H

#include "Types.h"

#include <string>
#include <vector>


#include "MyLibs\Math\mat4.h"
#include "MyLibs\Math\vec3.h"
#include "MyLibs\Math\vec2.h"
#include "MyLibs\Math\vec4.h"

#include "Tools\ArrayList.h"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "MyLibs\OpenGL\GL\GLExtensions.h"

#include "MyLibs\OpenGL\Window.h"
#include "Config.h"

#include "MyLibs\OpenGL\Helper.h"
#include "MyLibs\Memory\MemoryTracker.h"
#include "MyLibs\Logging\LightLogger.h"

//bullet header
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "../Libraries/Bullet/Source/BulletCollision/CollisionDispatch/btGhostObject.h"

#define PI 3.14159265359

#endif //__STDAFX_H