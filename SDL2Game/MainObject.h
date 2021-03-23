
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "AttackObject.h"

#define GRAVITY_SPEED 0.8
#define NUMBER_FRAME 8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP 18
class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,

	};

	bool LoadImg(std::string path, SDL_Renderer* screen,int COLOR_KEY_R, int COLOR_KEY_G, int COLOR_KEY_B);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	void DoPlayer(Map& map_data);
	void CheckMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
	void MoveOnMap(Map& map_data);
	void set_attack_list(std::vector<AttackObject*> attack_list)
	{
		p_attack_list_ = attack_list;
	}
	std::vector<AttackObject*> get_attack_list() const {return p_attack_list_;}
	void HandleAttackObject(SDL_Renderer* des);
	void CoinPlus(int val);
	void RemoveAttack(const int& num);
	SDL_Rect GetRectFrame();
	void SetComebackTime(const int& cbt){come_back_time =cbt;}
	void regame();
	int RestBullet() const {return CoinCount;}


private:

	std::vector<AttackObject*> p_attack_list_;
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;

	bool on_ground_;

	int map_x_;
	int map_y_;

	int come_back_time ;

	int BulletsType;
	int CoinCount;
};

#endif