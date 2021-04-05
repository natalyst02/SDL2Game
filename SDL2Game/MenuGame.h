#ifndef MENU_GAME_H_
#define MENU_GAME_H_

#include "CommonFunction.h"
#include "BaseObject.h"
class MenuGame
{
public:
	MenuGame();
	~MenuGame();

	static int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font, 
                      const std::string& menu1, 
                      const std::string& menu2,
					  const std::string& menu3,
                      const std::string& img_name);
	static int ShowGuideStory(SDL_Renderer* g_screen, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& img_name);
private:
};

#endif
