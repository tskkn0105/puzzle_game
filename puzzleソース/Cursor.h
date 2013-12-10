#ifndef CURSOR
#define CURSOR

#include "PadState.h"
#include "Position.h"
#include "Block.h"

enum CUR_STATE{ YOKO,TATE };

class Cursor
{
private:
	int g_cursor;
	int se_change;
	int se_move;

	int life;	//体力。ステージの幅分失うとゲームオーバー
	int rensa;
	int rensa_time;
	int attack;
	int damage;
	int pace;

	Position pos;
	CUR_STATE state;
	Change_Block* c_bl;
public:
	const int block_num;
	Cursor();
	~Cursor();
	void init();

	int get_rensa();
	void get_rensa(int Rensa);
	int get_rensa_time();
	void get_rensa_time(int Rensa_Time);
	int get_attack();
	int get_attack(int Attack);
	int get_damage();
	void get_damage(int Damage);
	int get_pace();
	void get_pace(int Pace);
	
	bool load(int G_cursor,int SE_change,int SE_move);

	void move(padstate* ps,Block* bl,int wide=6,int high=12);
	void change(padstate* ps,Block* bl,int wide=6,int high=12);
	void draw(const Position* nut,const int block_size);
	void get_c_bl(Change_Block* bl_p);
	int get_life();
	void get_life(int Life);
};





#endif