
#include "stdafx.h"
#include "MainObject.h"

MainObject::MainObject()
{
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;
	come_back_time= 0;
	BulletsType = 1;
	CoinCount = 10;

}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen,int COLOR_KEY_R, int COLOR_KEY_G, int COLOR_KEY_B)
{
	bool ret = BaseObject::LoadImg(path, screen,169,173,153);

	if (ret == TRUE)
	{
		width_frame_ = rect_.w / NUMBER_FRAME;
		height_frame_ = rect_.h;
	}

	return ret;
}

void MainObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < NUMBER_FRAME; i++)
		{
		frame_clip_[i].x = i * width_frame_;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = width_frame_;
		frame_clip_[i].h = height_frame_;

		}
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	if (status_ == WALK_LEFT)
	{
		if (on_ground_ ==true )
		LoadImg("img//player_left.png",des,169,173,153);
		else 
		{
			LoadImg("img//fly_left.png",des,169,173,153);
		}

	}
	else if (status_ == WALK_RIGHT) 
	{
		if (on_ground_ ==true )
		LoadImg("img//player_right.png",des,169,173,153);
		else 
		{
			LoadImg("img//fly_right.png",des,169,173,153);
		}

	}
	else 
	{
		LoadImg("img//player_jump.png",des,169,173,153);
	}
	if (input_type_.left_ == 1 ||
		input_type_.right_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ =0;
	}

	if (frame_ >= NUMBER_FRAME )
	{
		frame_ = 0;
	}

	if (come_back_time == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_ ;

		SDL_Rect* current_clip = &frame_clip_[frame_];

		SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				
			}
			break;
		case SDLK_LEFT:
			{
				status_ = WALK_LEFT;
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				
			}
			break;
		case SDLK_UP:
			{
				input_type_.jump_ = 1;
				status_ = WALK_UP;
			}
			break;
		case SDLK_1:
			{
				 BulletsType = 1;

			}
			break;
		case SDLK_2:
			{
				BulletsType = 2 ;
				CoinPlus(1);
			}
			break;
		case SDLK_3:
			{
				BulletsType = 3;
				CoinPlus(2);
			}
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
			{
				
				input_type_.right_ = 0;

			}
			break;
		case SDLK_LEFT:
			{
				
				input_type_.left_ = 0;

			}
			break;
		case SDLK_UP:
			{
				input_type_.jump_ = 0;
			}
			break;
		}
	}
	if (events.type == SDL_MOUSEBUTTONDOWN && CoinCount > 0)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			CoinPlus(-1);
			AttackObject* p_attack = new AttackObject();
			if (BulletsType == 1)
			p_attack->set_attack_type(AttackObject::ATTACK1);
			else if (BulletsType == 2) 
			p_attack->set_attack_type(AttackObject::ATTACK2);
			else p_attack->set_attack_type(AttackObject::ATTACK3);
			p_attack->LoadAttackType(screen);
			if (status_ == WALK_LEFT) 
			{
			p_attack->set_attack_sign(AttackObject::SIGN_LEFT);
			p_attack->SetRect(this->rect_.x - 50 , rect_.y + height_frame_ *0.05);
			}
			else 
			{
			p_attack->set_attack_sign(AttackObject::SIGN_RIGHT);
			p_attack->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ *0.05);
			}
			p_attack->set_x_val(25);
			p_attack->set_is_move(true);

			p_attack_list_.push_back(p_attack);
		}

	}



}

void MainObject::regame()
{

}

void MainObject::DoPlayer(Map& map_data)
{
	if (come_back_time == 0)
	{
		x_val_ = 0;
		y_val_ += GRAVITY_SPEED;

		if (y_val_ >= MAX_FALL_SPEED)
		{
		y_val_ = MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1)
		{
		x_val_ -= PLAYER_SPEED;
		}
		else if (input_type_.right_ ==1 )
		{
		x_val_ += PLAYER_SPEED;
		}
		if (input_type_.jump_ == 1)
		{
		if (on_ground_ == true )
		{
			y_val_ = -PLAYER_JUMP;
		}

		on_ground_ = false;
		input_type_.jump_ = 0;
		}


		CheckMap(map_data);
		MoveOnMap(map_data);
	}

	if (come_back_time > 0 )
	{
		come_back_time --;
		if (come_back_time == 0)
		{
			x_pos_ = 0;// maybe error 7
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
			status_ = WALK_UP;
		}

	}

}

void MainObject::MoveOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0 )
	{
		map_data.start_x_ = 0;
	}
	else if ( map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;

	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2 );
	if (map_data.start_y_ < 0 )
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}



}

void MainObject::CheckMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	// kiem_tra_theo_chieu_ngang
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 =( x_pos_ + x_val_ ) / TILE_SIZE;
	x2 =( x_pos_ + x_val_ + width_frame_ -1 ) / TILE_SIZE;

	y1 =( y_pos_ ) / TILE_SIZE;
	y2 =( y_pos_  + height_min -1 ) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y )
	{
		if (x_val_ > 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if (val1 == COIN || val2 == COIN )
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				CoinPlus(1);
			}
			else 
			{
				if (map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0 )
				{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ +1;
				x_val_ = 0 ;
				}
			}

		}
		else if (x_val_ < 0 )
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if (val1 == COIN || val2 == COIN )
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				CoinPlus(1);
			}
			else
			{
				if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0 )
				{
				x_pos_ = (x1 + 1 )* TILE_SIZE;
				x_val_ = 0 ;
				}
			}
		}


	}

	// kiem tra theo chieu doc
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ :TILE_SIZE;
	x1 = (x_pos_ ) / TILE_SIZE;
	x2 = (x_pos_+ width_min ) / TILE_SIZE;

	y1 = (y_pos_ + y_val_ )/ TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ -1 )/ TILE_SIZE; 

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y )
	{
		if (y_val_ > 0 )
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == COIN || val2 == COIN)
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				CoinPlus(1);
			}
			else
			{
				if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0)
				{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ +1);
				y_val_ = 0;
				on_ground_ = true;
				}
			}
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == COIN || val2 == COIN)
			{
				map_data.tile[y1][x1]= 0;
				map_data.tile[y1][x2] = 0;
				CoinPlus(1);
			}
			else 
			{
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
			{
				y_pos_ = (y1 + 1 ) *TILE_SIZE;
				y_val_ = 0 ;
			}
			}
		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ <0)
		x_pos_ = 0;
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > map_data.max_y_)
	{
		come_back_time = 60;
	}


}
void MainObject::HandleAttackObject(SDL_Renderer* des)
{
	for (int i = 0; i < p_attack_list_.size(); i++)
	{
		AttackObject* p_attack = p_attack_list_.at(i);
		if (p_attack != NULL)
		{

			if (p_attack->get_is_move())
			{
				int distance = abs(rect_.x - p_attack->GetRect().x);
				if (distance < 400 )
				{
				p_attack->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
				p_attack->Render(des);
				}
				else 
				{
					p_attack->set_is_move(false);
				}

			}
			else
			{
				p_attack_list_.erase(p_attack_list_.begin() + i);
				if (p_attack != NULL)
				{
					delete p_attack;
					p_attack = NULL;
				}

			}


		}

	}


}

void MainObject::CoinPlus(int val)
{
	CoinCount += val;
}

void MainObject::RemoveAttack(const int& num)
{
	if (p_attack_list_.size() > 0 && num < p_attack_list_.size())
	{
		AttackObject* p_attack = p_attack_list_.at(num);
		p_attack_list_.erase(p_attack_list_.begin() + num);

		if (p_attack )
		{
			delete p_attack;
			p_attack = NULL;
		}

	}

}

SDL_Rect MainObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.h = height_frame_;
	rect.w = width_frame_;
	return rect;
}
