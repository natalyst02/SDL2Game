
#include "stdafx.h"
#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	width_frame_ = 0;
	height_frame_ =0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground_ =0 ;
	comebacktime = 0;
	frame_ =0;
	animation_left = 0;
	animation_right = 0;
	input_type_.left_ = 0;
	type_move_ = REMAIN_THREAT;
	////dasdasdasd
	//dasdasdasdasdasdasdasd
	//dasdasdasdsad
}
ThreatObject::~ThreatObject()
{

}

bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen,int COLOR_KEY_R, int COLOR_KEY_G, int COLOR_KEY_B)
{

	bool ret = BaseObject::LoadImg(path,screen,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B);
	if (ret == true )
	{
		width_frame_ = rect_.w / THREAT_FRAME_NUM;
		height_frame_ = rect_.h;
	}
	return ret;
}

void ThreatObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0 )
	{
		for (int i = 0; i < THREAT_FRAME_NUM; i++)
		{
		frame_clip_[i].x = i * width_frame_;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = width_frame_;
		frame_clip_[i].h = height_frame_;

		}
	}

}
void ThreatObject::Show(SDL_Renderer* des)
{
	if (comebacktime == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if (frame_ >=8 )
		{
			frame_ = 0 ;
		}

		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect rendQuad = {rect_.x,rect_.y,width_frame_,height_frame_};
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
	}

}

void ThreatObject::DoPlayer(Map& tMap)
{
	if (comebacktime == 0 )
	{
		x_val_ =0;
		if (type_move_ != FLY_THREAT ){
		y_val_ += THREAT_GRAVITY_SPEED;
		if (y_val_ >= THREAT_MAX_FALL_SPEED)
		{
			y_val_ = THREAT_MAX_FALL_SPEED;
		}}
		if (type_move_ == MOVE_THREAT|| type_move_ == FLY_THREAT)
		{
		if (input_type_.left_ == 1)
		{
			x_val_ -= THREAT_SPEED;
		}
		else 
		{
			x_val_ += THREAT_SPEED;
		}
		}

		CheckMap(tMap);
	}
	else if (comebacktime > 0 )
	{
		comebacktime --;
		if (comebacktime == 0)
		{
			x_val_ = 0;
			y_val_ = 0 ;
			if (x_pos_ > 256)
			{
				x_pos_ -= 256;
				animation_left -= 256;
				animation_right -= 256;
			}
			else {x_pos_ = 0 ;}
			y_pos_ = 0;
			input_type_.left_ = 1;
		}

	}


}

void ThreatObject::CheckMap(Map& map_data)
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

				if ((val1 != 0 && val1 != COIN)  
					|| (val2 != 0 && val2 != COIN ) )
				{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ +1;
				x_val_ = 0 ;
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				}

		}
		else if (x_val_ < 0 )
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
				if ((val1 != 0 && val1 != COIN) || (val2 != 0 && val2 != COIN ))
				{
				x_pos_ = (x1 + 1 )* TILE_SIZE;
				x_val_ = 0 ;
				input_type_.left_ = 0;
				input_type_.right_ = 1;

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
				if ((val1 != 0 && val1 != COIN) || (val2 != 0 && val2 != COIN))
				{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ +1);
				y_val_ = 0;
				on_ground_ = true;
			
				}
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if ((val1 != 0 && val1 != COIN) || (val2 != 0 && val2 != COIN))
			{
				
				y_pos_ = (y1 + 1 ) *TILE_SIZE;
				y_val_ = 0 ;
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
		comebacktime = 60;
	}


}
void ThreatObject::ImpMoveType(SDL_Renderer* screen)
{
	if (type_move_ == REMAIN_THREAT)
	{

	}
	else if (type_move_ == MOVE_THREAT)
	{
		if ( on_ground_ ==true )
		{
			if (x_pos_ > animation_right   )
			{
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				if (type_img == 0)
					LoadImg("img//threat_left.png",screen,169,173,153);
				else if (type_img == 1)
					LoadImg("img//1left.png",screen,166,141,85);
				else if (type_img == 2)
					LoadImg("img//2left.png",screen,166,141,85);
				else if (type_img == 3)
					LoadImg("img//3left.png",screen,169,173,153);
				
			}
			else if ( x_pos_ < animation_left )
			{
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				if (type_img == 0)
					LoadImg("img//threat_right.png",screen,169,173,153);
				else if (type_img == 1)
					LoadImg("img//1right.png",screen,166,141,85);
				else if (type_img == 2)
					LoadImg("img//2right.png",screen,166,141,85);
				else if (type_img == 3)
					LoadImg("img//3right.png",screen,166,141,85);
			}
			else if (input_type_.left_ == 1 || input_type_.right_ == 0) {
				if (type_img == 0)
					LoadImg("img//threat_left.png",screen,169,173,153);
				else if (type_img == 1)
					LoadImg("img//1left.png",screen,166,141,85);
				else if (type_img == 2)
					LoadImg("img//2left.png",screen,166,141,85);
				else if (type_img == 3)
					LoadImg("img//3left.png",screen,166,141,85);}
			else if (input_type_.right_ == 1|| input_type_.left_ == 0 ){
				if (type_img == 0)
					LoadImg("img//threat_right.png",screen,169,173,153);
				else if (type_img == 1)
					LoadImg("img//1right.png",screen,166,141,85);
				else if (type_img == 2)
					LoadImg("img//2right.png",screen,166,141,85);
				else if (type_img == 3)
					LoadImg("img//3right.png",screen,166,141,85);}

		}
		else 
		{
			if (input_type_.left_ == 1 )
			{
				LoadImg("img//threat_left.png",screen,169,173,153);
			}
			else
			{
				LoadImg("img//threat_right.png",screen,169,173,153);
			}


		}


	}
	else 
	{
		if (x_pos_ > animation_right   )
			{
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				if (type_img == 0)
					LoadImg("img//mau_left.png",screen,186,207,184);
				else if (type_img == 1)
					LoadImg("img//mau2_left.png",screen,237,149,90);
			}
			else if ( x_pos_ < animation_left )
			{
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				if (type_img == 0)
					LoadImg("img//mau_right.png",screen,186,207,184);
				else if (type_img == 1)
					LoadImg("img//mau2_right.png",screen,237,149,90);
			}
			else if (input_type_.left_ == 1 || input_type_.right_ == 0) {if (type_img == 0)
					LoadImg("img//mau_left.png",screen,186,207,184);
				else if (type_img == 1)
					LoadImg("img//mau2_left.png",screen,237,149,90);}
			else if (input_type_.right_ == 1|| input_type_.left_ == 0 ){if (type_img == 0)
					LoadImg("img//mau_right.png",screen,186,207,184);
				else if (type_img == 1)
					LoadImg("img//mau2_right.png",screen,237,149,90);}
	}


}
void ThreatObject::InitAttack( AttackObject* p_attack, SDL_Renderer* screen)
{
	if (p_attack != NULL) 
	{
		p_attack->set_attack_type(AttackObject::ATTACK1);
		p_attack->LoadAttackType(screen);
		p_attack->set_is_move(true);
		p_attack->set_attack_sign(AttackObject::SIGN_LEFT);
		p_attack->SetRect( x_pos_ +20, y_pos_ +20);
		p_attack->set_x_val(15);
		attack_list_.push_back(p_attack);
	}

}
void ThreatObject::MakeAttack(SDL_Renderer* screen, const int& x_border, const int& y_border)
{
	for (int i = 0; i < attack_list_.size(); i++)
	{
		AttackObject* p_attack = attack_list_.at(i);
		if (p_attack != NULL)
		{
			if (p_attack->get_is_move())
			{
				int distance = abs(rect_.x - p_attack->GetRect().x);
				if (distance < 300 )
				{
				p_attack->HandleMove(x_border, y_border);
				p_attack->Render(screen);
				}
				else 
				{
					p_attack->set_is_move(false);
				}

			}
			else
			{
				p_attack->set_is_move(true);
				p_attack->SetRect(this->rect_.x +20, this->rect_.y +10 );
			}


		}

	}

}

void ThreatObject::RemoveAttack(const int& num)
{
	if (attack_list_.size() > 0 && num < attack_list_.size())
	{
		AttackObject* p_attack = attack_list_.at(num);
		attack_list_.erase(attack_list_.begin() + num);

		if (p_attack )
		{
			delete p_attack;
			p_attack = NULL;
		}

	}

}
SDL_Rect ThreatObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.h = height_frame_;
	rect.w = width_frame_;
	return rect;
}

