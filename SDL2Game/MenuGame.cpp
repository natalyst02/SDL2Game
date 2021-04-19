#include "stdafx.h"
#include "MenuGame.h"
#include "BaseObject.h"
#include "TextObject.h"
#include "stdafx.h"
#include "CommonFunction.h"
int MenuGame::ShowMenu(SDL_Renderer* g_screen, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
							const std::string& menu3,
                            const std::string& img_name)
{
	
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
	char* ch3 = (char*)menu3.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();
	int size3 = menu3.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 3;
    char* labels[kMenuNum];

    labels[0] = new char [size1 + 1];
    labels[1] = new char[size2 + 1];
	labels[2] = new char[size3 + 1];

    strcpy_s(labels[0], size1+1, ch1);
    strcpy_s(labels[1], size2+1, ch2);
	strcpy_s(labels[2], size3+1, ch3);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0,0 };
    SDL_Color color[2] = { { 255, 242, 0 },{ 255, 0, 0 } };

	

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].SetColor(color[0].r, color[0].g, color[0].b);

    text_object[0].LoadFromRenderText(font, g_screen);

    text_object[1].SetText(labels[1]);
    text_object[1].SetColor(color[0].r, color[0].g, color[0].b);
    text_object[1].LoadFromRenderText(font, g_screen);

	text_object[2].SetText(labels[2]);
    text_object[2].SetColor(color[0].r, color[0].g, color[0].b);
    text_object[2].LoadFromRenderText(font, g_screen);

    SDL_Rect pos[kMenuNum];
    pos[0].x = SCREEN_WIDTH*0.1;
    pos[0].y = SCREEN_HEIGHT*0.2;
    pos[1].x = SCREEN_WIDTH*0.1;
    pos[1].y = SCREEN_HEIGHT*0.4;
	pos[2].x = SCREEN_WIDTH*0.1;
    pos[2].y = SCREEN_HEIGHT*0.6;

    BaseObject gBackground;
    bool ret = gBackground.LoadImg(img_file, g_screen,100,100,100);

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[0].Free();
                gBackground.Free();
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].SetColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].SetColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
						text_object[2].Free();
                        gBackground.Free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
					text_object[2].Free();
                    gBackground.Free();
					//SDL_Quit();
                    return 1;

                }
            }
        }
		TTF_Font* font_timeAu = NULL;
        gBackground.Render(g_screen, NULL);
		font_timeAu = TTF_OpenFont("font//dlxfont_.ttf", 15);
		std::string author = "Author:NGUYEN ANH TUAN";
		std::string author2 = "Natalyst X FlowNak";
		TextObject Author;
		Author.SetText(author);
		Author.SetColor(color[0].r, color[0].g, color[0].b);
		Author.LoadFromRenderText(font_timeAu,g_screen);
		Author.RenderText(g_screen,SCREEN_WIDTH*0.7,20);

		TextObject Author2;
		Author2.SetText(author2);
		Author2.SetColor(color[0].r, color[0].g, color[0].b);
		Author2.LoadFromRenderText(font_timeAu,g_screen);
		Author2.RenderText(g_screen,SCREEN_WIDTH*0.75,40);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].GetWidth();
            pos[i].h = text_object[i].GetHeight();
        }


        SDL_RenderPresent(g_screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
	 gBackground.Free();
    return 0;
}
MenuGame::MenuGame()
{

}
MenuGame::~MenuGame()
{

}
int MenuGame::ShowGuideStory(SDL_Renderer* g_screen, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& img_name)
{

	
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 2;
    char* labels[kMenuNum];

    labels[0] = new char [size1 + 1];
    labels[1] = new char[size2 + 1];

    strcpy_s(labels[0], size1+1, ch1);
    strcpy_s(labels[1], size2+1, ch2);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 100, 242, 0 },{ 255, 0, 0 } };

	

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].SetColor(color[0].r, color[0].g, color[0].b);

    text_object[0].LoadFromRenderText(font, g_screen);

    text_object[1].SetText(labels[1]);
    text_object[1].SetColor(color[0].r, color[0].g, color[0].b);
    text_object[1].LoadFromRenderText(font, g_screen);

    SDL_Rect pos[kMenuNum];
    pos[0].x = SCREEN_WIDTH*0.6;
    pos[0].y = SCREEN_HEIGHT*0.7;
    pos[1].x = SCREEN_WIDTH*0.6;
    pos[1].y = SCREEN_HEIGHT*0.9;

    BaseObject gBackground;
    bool ret = gBackground.LoadImg(img_file, g_screen,100,100,100);

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[0].Free();
                gBackground.Free();
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].SetColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].SetColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        gBackground.Free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    gBackground.Free();
					//SDL_Quit();
                    return 1;

                }
            }
        }


		gBackground.Render(g_screen, NULL);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].GetWidth();
            pos[i].h = text_object[i].GetHeight();
        }


        SDL_RenderPresent(g_screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
	 gBackground.Free();
    return 0;
}
int MenuGame::ShowPause(SDL_Renderer* g_screen, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& img_name)
{

	
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 2;
    char* labels[kMenuNum];

    labels[0] = new char [size1 + 1];
    labels[1] = new char[size2 + 1];

    strcpy_s(labels[0], size1+1, ch1);
    strcpy_s(labels[1], size2+1, ch2);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 0, 128, 255 },{ 255, 0, 0 } };

	

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].SetColor(color[0].r, color[0].g, color[0].b);

    text_object[0].LoadFromRenderText(font, g_screen);

    text_object[1].SetText(labels[1]);
    text_object[1].SetColor(color[0].r, color[0].g, color[0].b);
    text_object[1].LoadFromRenderText(font, g_screen);

    SDL_Rect pos[kMenuNum];
    pos[0].x = SCREEN_WIDTH*0.25;
    pos[0].y = SCREEN_HEIGHT*0.25;
    pos[1].x = SCREEN_WIDTH*0.25;
    pos[1].y = SCREEN_HEIGHT*0.4;

    BaseObject gBackground;
    bool ret = gBackground.LoadImg(img_file, g_screen,100,100,100);

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[0].Free();
                gBackground.Free();
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].SetColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].SetColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        gBackground.Free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    gBackground.Free();
					//SDL_Quit();
                    return 1;

                }
            }
        }

		gBackground.SetRect(300,130);
		gBackground.Render(g_screen, NULL);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].GetWidth();
            pos[i].h = text_object[i].GetHeight();
        }


        SDL_RenderPresent(g_screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
	 gBackground.Free();
    return 0;
}
