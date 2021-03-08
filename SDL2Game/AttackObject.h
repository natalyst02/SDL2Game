#ifndef ATTACK_OBJECT_H_
#define ATTACK_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

class AttackObject : public BaseObject
{

public :
	AttackObject();
	~AttackObject();

	enum AttackSign
	{
		SIGN_RIGHT = 0,
		SIGN_LEFT = 1,
	};
	enum AttackType
	{
		ATTACK1 = 0,
		ATTACK2 = 1,
		ATTACK3 = 2,
	};

	
	void set_x_val(const int& xVal){x_val_ = xVal;}
	void set_y_val(const int& yVal){y_val_ = yVal;}
	int get_x_val() const {return x_val_;}
	int get_y_val() const {return y_val_;}

	void set_is_move( const bool& isMove) {is_move_ = isMove;}
	bool get_is_move() const { return is_move_;}

	void HandleMove(const int& x_border, const int& y_border);
	void set_attack_sign(const int& attackSign){attack_sign_ = attackSign;}
	int get_attack_sign()const{return attack_sign_;}

	void set_attack_type(const int& attackType){ attack_type_ = attackType;}
	int get_atack_type() const { return attack_type_;}
	void LoadAttackType(SDL_Renderer* des);
private:
	int x_val_;
	int y_val_;
	bool is_move_;
	int attack_sign_;
	int attack_type_;

};


#endif
