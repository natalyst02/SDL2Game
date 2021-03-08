
#include "stdafx.h"
//#include "CommonFunction.h"
//#include "BaseObject.h"
#include "AttackObject.h"

AttackObject ::AttackObject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;

}

AttackObject::~AttackObject()
{

}

void AttackObject::LoadAttackType(SDL_Renderer* des)
{
	if (attack_type_ == ATTACK1)
	{
		LoadImg("img//player_attack1.png",des);
	}
	else if (attack_type_ == ATTACK2)
	{
		LoadImg("img//player_attack2.png",des);
	}
	else LoadImg("img//player_attack3.png",des);


}

void AttackObject::HandleMove(const int& x_border, const int& y_border)
{
	if (attack_sign_ == SIGN_RIGHT)
	{
	rect_.x += x_val_;
	if (rect_.x > x_border)
	{
		is_move_ = false;

	}
	}
	else if (attack_sign_ == SIGN_LEFT)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}

	}


}



