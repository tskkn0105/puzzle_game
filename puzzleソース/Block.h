#ifndef BLOCK_H
#define BLOCK_H

#include "Position.h"

//Mはmoveの意
enum BLOCKSTATE{ RED=0,GREEN,BLUE,YELLOW,PURPLE,STONE,
				WHITE,W_GREEN,W_BLUE,W_YELLOW,W_PURPLE,NON,TEMP,UP };
enum FLAG { EVER=0,OVER,OFF };

//ブロック
class Block
{
protected:
	int time;	//時間
	int alfa;
	Position pos;	//場所

	BLOCKSTATE state;		//状態
	FLAG check_flag;	//つながりチェックをしたかどうか。

	int* g_block;	//画像ハンドル
public:
	Block();
//	Block(int a);

	const int G_BLOCK;
	const int block_size;

	bool load(int g_handle[]);
	void del_p();
	virtual void draw(const Position* nut,int bl_size);

	Position get_pos(int x,int y);
	virtual Position get_pos(Position p);
	Position get_pos();
	BLOCKSTATE get_state(BLOCKSTATE s);
	BLOCKSTATE get_state();
	FLAG get_check_flag();
	void get_check_flag(FLAG flag);
	int get_time();
	void get_time(int Time);

};

enum LR{ LEFT,RIGHT };

class Drop_Block : public Block
{
private:
	int dis_y;
	int d_speed;
	int* g_ray;
//	char check_flag;	//
public:
	Drop_Block();
	const int G_RAY;

	bool load(int G_block[],int G_ray[]);
	void del_p();
	virtual Position get_pos(Position p);
	int inc_disy(int y);
	void get_d_speed(int s);
	bool drop(Block* bl,int se,int wide = 6,int high = 12);
	void draw(const Position* nut);
};
////////////////////////////////////
class Change_Block : public Block
{
private:
	int dis;
	const int c_speed;
public:
	Change_Block();

	int get_dis(int x);
	int get_dis();
	bool moveL();
	bool moveR();
	bool moveU();
	bool moveD();
	virtual void draw(const Position* nut);
};





#endif