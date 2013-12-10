#include "Cursor.h"
#include "DxLib.h"

Cursor::Cursor() :
g_cursor(NULL),
state(YOKO),
block_num(2),
life(0),
rensa(0),
rensa_time(0),
attack(0),
damage(0),
pace(60)
{}

void Cursor::init()
{
	state = YOKO;
	life = 0;
	rensa = 0;
	rensa_time = 0;
	attack = 0;
	damage = 0;
	pace = 60;
}

Cursor::~Cursor()
{
	delete [] c_bl;
}

int Cursor::get_rensa()
{ return rensa; }
void Cursor::get_rensa(int Rensa)
{ rensa = Rensa; }
int Cursor::get_rensa_time()
{ return rensa_time; }
void Cursor::get_rensa_time(int Rensa_Time)
{ rensa_time = Rensa_Time; }
int Cursor::get_attack()
{ return attack; }
int Cursor::get_attack(int Attack)
{ attack = Attack; return attack; }
int Cursor::get_damage()
{ return damage; }
void Cursor::get_damage(int Damage)
{ damage = Damage; }
int Cursor::get_pace()
{ return pace; }
void Cursor::get_pace(int Pace)
{
	pace = Pace;
	if(pace < 5){ pace = 5; }
}

bool Cursor::load(int G_cursor,int SE_change,int SE_move)
{
	g_cursor = G_cursor;
	se_change = SE_change;
	se_move = SE_move;

	return true;
}

void Cursor::move(padstate *ps,Block* bl,int wide,int high)
{
	const int wait = 13;
	const int c_pace = 7;

	if(c_bl[0].get_dis() <= 0)
	{

		//ƒJ[ƒ\ƒ‹‚Ìc‰¡‚ð•Ï‚¦‚é
		if(ps->input[1] == 1 && state == YOKO){ state = TATE; }
		else if(ps->input[1] == 1 && state == TATE){ state = YOKO; }
		//
		if((ps->input[2] == 1 || (ps->input[2] > 40 && ps->input[2]%15 == 0)) && pace > 5)
		{ pace = (int)(pace/1.20); }
	///////////////ˆÚ“®ŠÖŒW//////////////////////////////////////////
		if(ps->up == 1 || (ps->up > wait && ps->up%c_pace == 0) ){ pos.y--; PlaySoundMem(se_move,DX_PLAYTYPE_BACK); }
		if(ps->down == 1 || (ps->down > wait && ps->down%c_pace == 0)){ pos.y++; PlaySoundMem(se_move,DX_PLAYTYPE_BACK); }
		if(ps->left == 1 || (ps->left > wait && ps->left%c_pace == 0)){ pos.x--; PlaySoundMem(se_move,DX_PLAYTYPE_BACK); }
		if(ps->right == 1 || (ps->right > wait && ps->right%c_pace == 0)){ pos.x++; PlaySoundMem(se_move,DX_PLAYTYPE_BACK); }

		if(state == YOKO){ wide -= 2; }else{ wide -= 1; }
		if(state == YOKO){ high -= 1; }else{ high -= 2; }

		if(ps->input[1] == 1)
		{
			if(pos.x > wide && state == YOKO){ pos.x -= 1; }
			if(pos.y > high && state == TATE){ pos.y -= 1; }
		}

		if(pos.x > wide)	{ pos.x = 0; }
		else if(pos.x < 0)	{ pos.x = wide; }
		if(pos.y > high)	{ pos.y = 0; }
		else if(pos.y < 0)	{ pos.y = high; }
		////////////////////////////////////////////////////////
	}
}

void Cursor::change(padstate* ps,Block* bl,int wide,int high)
{
	BLOCKSTATE temp1,temp2;
	int n = 0;
	int bl_num = pos.x + wide*pos.y;

	temp1 = c_bl[0].get_state();
	temp2 = c_bl[1].get_state();

	if(state == YOKO)
	{
		if(c_bl[1].moveL()==true){ n++; }
		if(c_bl[0].moveR()==true){ n++; }
	}
	else
	{
		if(c_bl[1].moveU()==true){ n++; }
		if(c_bl[0].moveD()==true){ n++; }
	}


	if(n == 2)
	{
		if(temp1 == TEMP){ temp1 = NON; }
		if(temp2 == TEMP){ temp2 = NON; }
		if(state == YOKO)
		{
			bl[bl_num].get_state(temp2);
			bl[bl_num+1].get_state(temp1);
		}
		else if(state == TATE)
		{
			bl[bl_num].get_state(temp2);
			bl[bl_num+wide].get_state(temp1);
		}
	}


	if(ps->input[0] == 1 && c_bl[0].get_dis() <= 0 &&
		bl[bl_num].get_state() < TEMP && bl[bl_num+1].get_state() < TEMP &&
		bl[bl_num].get_check_flag() != OFF && bl[bl_num+1].get_check_flag() != OFF && 
		state == YOKO)
	{
		PlaySoundMem(se_change,DX_PLAYTYPE_BACK);
		c_bl[0].get_pos(pos.x*32,pos.y*32);
		c_bl[1].get_pos(pos.x*32+32,pos.y*32);
		c_bl[0].get_dis(c_bl[0].block_size);	//ˆÚ“®—Ê‚ð’Ç‰Á
		c_bl[1].get_dis(c_bl[1].block_size);
		if(c_bl[0].get_state(bl[bl_num].get_state())==NON)
		{ c_bl[0].get_state(TEMP); }
		if(c_bl[1].get_state(bl[bl_num+1].get_state())==NON)
		{ c_bl[1].get_state(TEMP); }
		bl[bl_num].get_state(TEMP);
		bl[bl_num+1].get_state(TEMP);
	}
	else if(ps->input[0] == 1 && c_bl[0].get_dis() <= 0 &&
		bl[bl_num].get_state() < TEMP && bl[bl_num+wide].get_state() < TEMP &&
		bl[bl_num].get_check_flag() != OFF && bl[bl_num+wide].get_check_flag() != OFF &&
		state == TATE)
	{
		PlaySoundMem(se_change,DX_PLAYTYPE_BACK);
		c_bl[0].get_pos(pos.x*32,pos.y*32);
		c_bl[1].get_pos(pos.x*32,pos.y*32+32);
		c_bl[0].get_dis(c_bl[0].block_size);	//ˆÚ“®—Ê‚ð’Ç‰Á
		c_bl[1].get_dis(c_bl[1].block_size);
		if(c_bl[0].get_state(bl[bl_num].get_state())==NON)
		{ c_bl[0].get_state(TEMP); }
		if(c_bl[1].get_state(bl[bl_num+wide].get_state())==NON)
		{ c_bl[1].get_state(TEMP); }
		bl[bl_num].get_state(TEMP);
		bl[bl_num+wide].get_state(TEMP);
	}

}

void Cursor::draw(const Position* nut,const int block_size)
{

	c_bl[0].draw(nut);
	c_bl[1].draw(nut);

	int x = nut->x + pos.x * block_size;
	int y = nut->y + pos.y * block_size;

	DrawGraph(x,y,g_cursor,true);

	if(state == YOKO){ x += block_size; }else{ y += block_size; }

	DrawGraph(x,y,g_cursor,true);

}

void Cursor::get_c_bl(Change_Block *bl_p){ c_bl = bl_p; }


int Cursor::get_life(){ return life; }
void Cursor::get_life(int Life){ life = Life; }