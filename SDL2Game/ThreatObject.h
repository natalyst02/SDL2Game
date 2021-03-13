
#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_
#include "AttackObject.h"
#include "BaseObject.h"
#include "CommonFunction.h"
#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3
class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	enum TypeMove
	{
		REMAIN_THREAT = 0,
		MOVE_THREAT = 1,
	};


	void set_x_val(const float& xVal){ x_val_ = xVal;}
	void set_y_val(const float& yVal){ y_val_ = yVal;}
	void set_x_pos(const float& xPos){ x_pos_ = xPos;}
	void set_y_pos(const float& yPos){ y_pos_ = yPos;}
	float get_x_pos() const {return x_pos_;}
	float get_y_pos() const {return y_pos_;}
	void SetMapXY (const int& mp_x, const int& mp_y){map_x_=mp_x;map_y_=mp_y;}

	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int get_width_frame()const{return width_frame_;}
	int get_height_frame()const{return height_frame_;}
	void DoPlayer(Map& tMap);
	void CheckMap(Map& tMap);

	void set_type_move( const int& typemove) {type_move_ = typemove;}
	void set_animation_pos( const int& pos_a, const int& pos_b){animation_left = pos_a; animation_right = pos_b;}
	void set_input_left(const int& inputleft){input_type_.left_ = inputleft;}
	void ImpMoveType( SDL_Renderer* screen);
	std::vector<AttackObject*> get_attack_list() const { return attack_list_;}
	void set_attack_list(const std::vector<AttackObject*>& at_list) { attack_list_ = at_list;}
	void InitAttack( AttackObject* p_attack, SDL_Renderer* screen);
	void MakeAttack(SDL_Renderer* screen, const int& x_border, const int& y_border);
private:

	int frame_;
	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	bool on_ground_;
	int comebacktime;
	float x_pos_;
	float y_pos_;
	float x_val_;
	float y_val_;
	int map_x_;
	int map_y_;
	int type_move_ ;
	int animation_left;
	int animation_right;
	int barrier;

	Input input_type_;
	std::vector <AttackObject*> attack_list_;
};


#endif
