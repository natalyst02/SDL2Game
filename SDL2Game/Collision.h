#ifndef COLLISION_H_
#define COLLISION_H_
#include "CommonFunction.h"
class Collision
{
public:
	Collision();
	~Collision();

	static bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
private:
};

#endif