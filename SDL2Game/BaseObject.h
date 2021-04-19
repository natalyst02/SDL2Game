#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
	SDL_Rect GetRect() const { return rect_;} 
	SDL_Texture* GetObject() const { return p_object_;}

	virtual bool LoadImg(std::string path, SDL_Renderer* screen,int COLOR_KEY_R, int COLOR_KEY_G, int COLOR_KEY_B);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
	int broken;
};


#endif 