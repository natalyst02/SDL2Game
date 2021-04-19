
#include "stdafx.h"
#include "CommonFunction.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"
#include "Collision.h"
#include "TextObject.h"
#include "MenuGame.h"
BaseObject	g_background;
TTF_Font* font_time = NULL;
TTF_Font* g_font_MENU = NULL;
bool InitData()
{
	 bool success = true;
	 int ret = SDL_Init(SDL_INIT_VIDEO);
	 if (ret < 0)
	 {
		 return false;
	 }

	 SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	 g_window = SDL_CreateWindow(" GAME SDL2.0",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH,
								SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN);

	 if (g_window == NULL)
	 {
		 success = false;
	 }
	 else 
	 {
		 g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		 if (g_screen == NULL)
		 {
			 success = false;
		 }
		 else 
		 {
			 SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			 int imgFlags = IMG_INIT_PNG;
			 if (!(IMG_Init(imgFlags) && imgFlags))
				 success = false;

		 }
		 if (TTF_Init() == -1)
        {
            success = false;
        }
		 if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;
        }
		
        font_time = TTF_OpenFont("font//dlxfont_.ttf", 20);
        if (font_time == NULL)
        {
            success = false;
        }
		g_font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
        if (g_font_MENU == NULL)
        {
            return false;
        }
	 }

	 return success;
}

 bool LoadBackground(int typemap)
 {
	 bool ret;
	 if (typemap == 0)
	 ret = g_background.LoadImg("img//background.png", g_screen,169,173,153);
	 else ret = g_background.LoadImg("img//background2.png", g_screen,169,173,153);
	 if (ret == false)
		 return false;

	 return true;
 }

 void close()
 {
	 g_background.Free();

	 SDL_DestroyRenderer(g_screen);
	 g_screen = NULL;

	 SDL_DestroyWindow(g_window);
	 g_window = NULL;

	 IMG_Quit();
	 SDL_Quit();
 }

 std::vector<ThreatObject*> MakeThreatList()
 {
	 std::vector<ThreatObject*> list_threats;

	ThreatObject* move_threats = new ThreatObject[50];
	for (int i = 0; i < 50; i++)
	{
		ThreatObject* p_threat = (move_threats + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("img/threat_left.png",g_screen,169,173,153);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatObject::MOVE_THREAT);
			int d1 = rand()%800;
			p_threat->set_x_pos(i*800+d1);
			p_threat->set_y_pos (200);
			int v1 = rand() % 10;
			int v2 = rand() % 4;
			p_threat->set_image_threat(v2);
			int pos1 = p_threat->get_x_pos() - 200;
			int pos2 = p_threat->get_x_pos() + 200;
			p_threat->set_animation_pos(pos1,pos2);
			if (  v1% 2 == 0)
			p_threat->set_input_left(1);
			else 
				p_threat->set_input_left(0);
			list_threats.push_back(p_threat);
		}
	}



	ThreatObject* threats_objs = new ThreatObject[30];

	for (int i = 0; i < 30; i++)
	{
		ThreatObject* p_threat = (threats_objs + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("img/threat_level.png",g_screen,169,173,153);
			p_threat->set_clips();
			int d1= rand()%1500;
			p_threat->set_x_pos(i*1500 +d1 );
			p_threat->set_y_pos(250);
			p_threat->set_type_move(ThreatObject::REMAIN_THREAT);

			p_threat->set_input_left(0);

			AttackObject* p_attack = new AttackObject();
			p_threat->InitAttack(p_attack,g_screen);
			
			list_threats.push_back(p_threat);
		}

	}
	
	ThreatObject* fly_threats = new ThreatObject[30];
	for (int i = 0; i < 30; i++)
	{
		ThreatObject* p_threat = (fly_threats + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("img/mau_right.png",g_screen,186,207,184);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatObject::FLY_THREAT);
			int v2 = rand() % 2;
			p_threat->set_image_threat(v2);
			int d1= rand()%1000;
			p_threat->set_x_pos( 500+ i*1000);
			int d2 = rand()%200;
			p_threat->set_y_pos (d2);
			int v1 = rand()%100;
			int pos1 = p_threat->get_x_pos() - 200;
			int pos2 = p_threat->get_x_pos()+200;
			p_threat->set_animation_pos(pos1,pos2);
			if ( i % 2 == 0)
			p_threat->set_input_left(1);
			else 
				p_threat->set_input_left(0);
			list_threats.push_back(p_threat);
		}
	}
	
	return list_threats;
 }

int main(int argc, char* argv[])
{
	ImpTimer fps_timer;

	if (InitData() == false) 
		return -1;
	 bool quit = false;
	 int ret_menu = 2;
	 int check_menu = 0;
	 int choose_game = 0;
	 int typemap = 0;

	 GameMap game_map;

	 while (ret_menu ==2 && check_menu == 0)
	 {
		g_background.Free();
		ret_menu = MenuGame::ShowMenu(g_screen, g_font_MENU, "Play Game", "Exit","Guide", "img//MENU2.png");
			
		if (ret_menu == 1)
		{
			quit = true;
			break;
		}

		if (ret_menu == 0) 
		{
			choose_game = MenuGame::ShowMenu(g_screen, g_font_MENU, "Easy", "Hard","Exit", "img//MENU2.png");
			if (choose_game == 2)
			{
				quit = true;
				break;
			}
			else if (choose_game == 0)
			{
				typemap = 0;
				game_map.LoadMap("map/map01.dat");
				game_map.LoadTiles(g_screen,typemap);
			}
			else if (choose_game == 1)
			{
				typemap= 1;
				game_map.LoadMap("map2/map01.dat");
				game_map.LoadTiles(g_screen,typemap);
			}
			break;
		}

		g_background.Free();
		check_menu = MenuGame::ShowGuideStory(g_screen,g_font_MENU,"Back","Exit","img//StoryGuide.png");
			
		if (check_menu == 1)
		{
			quit = true;
			break;
		}
		
	}
	 
	if (LoadBackground(typemap) == false) 
		return -1;

	/*GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);*/

	MainObject p_player;
	p_player.LoadImg("img//player_right.png",g_screen,169,173,153);
	p_player.set_clips();

	std::vector<ThreatObject*> threats_list = MakeThreatList();

	//bool quit = false;


	TextObject time_game;
    time_game.SetColor(TextObject::RED_TEXT);

	TextObject BulletPlayer;
    BulletPlayer.SetColor(TextObject::WHITE_TEXT);
	Mix_Chunk* beep_sound = Mix_LoadWAV("sound//gunny.wav");
						if (beep_sound != NULL){
							Mix_PlayChannel(-1, beep_sound,-1);Mix_VolumeChunk(beep_sound,20);}
	while (!quit)
	{
		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if(g_event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (g_event.type == SDL_KEYDOWN)
			{
			switch (g_event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				{
					ret_menu = MenuGame::ShowPause(g_screen, g_font_MENU, "GO ON", "SURRENDER", "img//MENU.png");
			
					if (ret_menu == 1)
						{
						quit = true;
						break;
						}
				}
			}
			}
			p_player.HandleInputAction(g_event, g_screen);
			
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		Map	map_data = game_map.getMap();

		p_player.HandleAttackObject(g_screen);
		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);

		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatObject* p_threat = threats_list.at(i);
			if (p_threat != NULL)
			{
				p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
				p_threat->ImpMoveType(g_screen);
				p_threat->DoPlayer(map_data);
				p_threat->MakeAttack(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);
				p_threat->Show(g_screen);

				SDL_Rect rect_player = p_player.GetRectFrame();
				bool CheckColli = false;
				std::vector<AttackObject*> AttackObj = p_threat->get_attack_list();
				for (int num = 0; num < AttackObj.size(); num++)
				{
					AttackObject* Threat_attack = AttackObj.at(num);
					if ( Threat_attack != NULL)
					{
						CheckColli = Collision::CheckCollision(Threat_attack->GetRect(),rect_player);
						if (CheckColli)
						{
							//p_threat->RemoveAttack(num);
							//commit
							break;
						}

					}

				}

				SDL_Rect rect_threat = p_threat->GetRectFrame();
				bool CheckColli2 = Collision::CheckCollision(rect_player, rect_threat);
				if (CheckColli == true || CheckColli2 == true )
				{
					{
						//p_player.CoinPlus(10);
						
						Mix_Chunk* beep_sound = Mix_LoadWAV("sound//occun.wav");
						if (beep_sound != NULL){
							Mix_PlayChannel(-1, beep_sound, 0);}
						p_player.SetRect(0,0);
						p_player.SetComebackTime(10);
						TextObject StupidMes;
						TTF_Font* font_timemes = TTF_OpenFont("font//dlxfont_.ttf", 50);
						std::string str_rebullet = " NGU ";
						StupidMes.SetText(str_rebullet);
						StupidMes.LoadFromRenderText(font_timemes, g_screen);
						StupidMes.RenderText(g_screen,0,0);
						SDL_Delay(100);
					}

				}

			}

		}
		std::vector <AttackObject*> attackplayer = p_player.get_attack_list();

		for ( int num = 0; num < attackplayer.size(); num++ )
		{
			AttackObject* p_attack = attackplayer.at(num);
			if (p_attack != NULL)
			{
				for (int i = 0 ;i < threats_list.size(); i++ )
				{
					ThreatObject* threatattack = threats_list.at(i);
					if (threatattack != NULL)
					{
						SDL_Rect objRect;
						objRect.x = threatattack->GetRect().x;
						objRect.y = threatattack->GetRect().y;
						objRect.w = threatattack->get_width_frame();
						objRect.h = threatattack->get_height_frame();
	
						SDL_Rect playerRect = p_attack->GetRect();

						bool CheckColl = Collision::CheckCollision(objRect,playerRect);
						if (CheckColl )
						{
							p_player.RemoveAttack(num);
							threatattack->Free();
							threats_list.erase(threats_list.begin() + i);
						}

					}

				}

			}

		}


		std::string str_time = "Time : ";
		int time_val = SDL_GetTicks() / 1000;
		int val_time = time_val;
 
        std::string str_val = std::to_string(val_time);
        str_time += str_val;

        time_game.SetText(str_time);
        time_game.LoadFromRenderText(font_time,g_screen);
        time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 10);
   
		
		std::string str_rebullet = " reload!!!!!!";
		std::string str_bullet = " Bullet : ";
		int Bullet = p_player.RestBullet();
		if (Bullet == 0 ) 
		{
			BulletPlayer.SetText(str_rebullet);
		BulletPlayer.LoadFromRenderText(font_time, g_screen);
		BulletPlayer.RenderText(g_screen,50, 15);
		}

		std::string BulletS = std::to_string(Bullet);
		str_bullet += BulletS;


		BulletPlayer.SetText(str_bullet);
		BulletPlayer.LoadFromRenderText(font_time, g_screen);
		BulletPlayer.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 15);

		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			SDL_Delay(delay_time);
		}

	}
	for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatObject* p_threat = threats_list.at(i);
			if (p_threat)
			{
				p_threat->Free();
				p_threat = NULL;
			}
	}
	threats_list.clear();
	close();
    return 0;
}