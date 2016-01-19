#ifndef __COLLISION_TAG_H
#define __COLLISION_TAG_H

namespace Game
{
    //this will tag collision objects to tell people that collide what kind of object they are
	enum CollisionTag
	{
		DamageTag = 0,
        PlayerTag,
        EventTag,
		FloorTag,
		MaxCollisionTags
	};
}

#endif //__COLLISION_TAG_H