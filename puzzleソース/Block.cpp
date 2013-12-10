#include "Block.h"
#include "DxLib.h"

///////↓ブロック//////////////////////////////////////////////////////

Block::Block() :
time(0),
alfa(0),
state( NON ),
check_flag(EVER),
G_BLOCK(14),
block_size(32)
{}
/*
Block::Block(int a)
{ state = a; }
*/

bool Block::load(int g_handle[])
{
	g_block = g_handle;

	return true;
}

void Block::del_p()
{
	delete [] g_block;
}

void Block::draw(const Position* nut,int bl_size)
{
	if(state < NON)
	{
		DrawGraph(nut->x + pos.x * bl_size,
			  	  nut->y + pos.y * bl_size,
				  g_block[state],true);

		if(check_flag == OFF)//消えるフラグがたった時
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,alfa);
		
			DrawGraph(nut->x + pos.x * bl_size,
				  	  nut->y + pos.y * bl_size,
					  g_block[state+7],true);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			alfa+=9;
			if(alfa > 255){ state = UP; }
			return;
		}

	}
//	else if(state == TEMP)
//	{
//		DrawGraph(nut->x + pos.x * bl_size,
//			  	  nut->y + pos.y * bl_size,
//				  g_block[6],true);
//	}
	check_flag = EVER;
	time++;
}
Position Block::get_pos(Position p)
{
	pos.x = p.x;
	pos.y = p.y;

	return pos;
}
Position Block::get_pos(int x,int y)
{
	pos.x = x;
	pos.y = y;

	return pos;
}
Position Block::get_pos(){ return pos; }

BLOCKSTATE Block::get_state()
{
	return state;
}
BLOCKSTATE Block::get_state(BLOCKSTATE s)
{
	state = s;
	alfa = 0;
	return s;
}

FLAG Block::get_check_flag()
{
	return check_flag;
}
void Block::get_check_flag(FLAG flag)
{
	check_flag = flag;
}

int Block::get_time()
{ return time; }
void Block::get_time(int Time)
{ time = Time; }


//////////////ドロップブロック↓////////////////////////////////////////////

Drop_Block::Drop_Block() :
d_speed(31),
dis_y(0),
G_RAY(6)
{}

bool Drop_Block::load(int G_block[],int G_ray[])
{
	g_block = G_block;
	g_ray = G_ray;

	return true;
}

void Drop_Block::del_p()
{
	delete [] g_ray;
}


int Drop_Block::inc_disy(int y){ dis_y += y; return dis_y; }
void Drop_Block::get_d_speed(int s){ d_speed = s; }

Position Drop_Block::get_pos(Position p)
{
	pos.x = p.x * 32;
	pos.y = p.y * 32;
	check_flag = OVER;

	return pos;
}

bool Drop_Block::drop(Block* bl,int se,int wide,int high)
{
	if(state < WHITE)
	{
		int temp = pos.x/32 + (pos.y/32 +1) * wide;
		if(temp >= wide){ bl[temp-wide].get_state(NON); }

		pos.y += d_speed;
		
		if(temp >= high*wide || bl[temp].get_state() < NON)
		{
			temp -= wide;
			Position bl_pos = bl[temp].get_pos();
			bl_pos.y *= 32;
			if(pos.y > bl_pos.y)
			{
				//着地した時
	//			PlaySoundMem(se,DX_PLAYTYPE_BACK);
				bl[temp].get_state(state);
				bl[temp].get_time(0);
				state = NON;
				while(temp>0)
				{
					if(bl[temp].get_state() == TEMP)
					{ bl[temp].get_state(NON); }
					temp -= wide;
				}
			}
		}
		else
		{
			for(int i=0;i<4;i++)
			{
				if(temp < high*wide && bl[temp].get_state() == NON)
				{ bl[temp].get_state(TEMP); }


				temp += wide;
			}
		}
		return false;
	}
	else if(state == WHITE)
	{
		pos.y -= d_speed;
		if(pos.y < -150)
		{
			state = NON; 
		}
	}
	return true;
}

void Drop_Block::draw(const Position* nut)
{
	int temp;

	if(check_flag == EVER)
	{
		if(state > 5){ temp = 5; }else{ temp = state; }
		DrawRotaGraph2(pos.x + nut->x,pos.y + nut->y,9,99,1.0,0.0,g_ray[state],true);
	}
	else if(state == WHITE)
	{
		if(state > 5){ temp = 5; }else{ temp = state; }
		DrawRotaGraph2(pos.x + nut->x,pos.y + nut->y,9,9,1.0,0.0,g_ray[5],true);
	}
	else if(state < NON)
	{
		DrawGraph(pos.x + nut->x,pos.y + nut->y,g_block[state],true);
	}
}


/////////////////////Change_Block↓////////////////////////////////////////////
Change_Block::Change_Block() :
dis(0),
c_speed(8)
{}

void Change_Block::draw(const Position* nut)
{
	if(dis > 0 && state < NON)
	{
		DrawGraph(pos.x + nut->x,pos.y + nut->y,g_block[state],true);

	}
}

int Change_Block::get_dis(int x){ dis = x; return 0; }
int Change_Block::get_dis(){ return dis; }

////左右上下に動く
bool Change_Block::moveL()
{
	if(state != NON)
	{
		if(dis > 0)
		{
			pos.x -= c_speed;
			dis -= c_speed;
		}
		if(dis <= 0)
		{
			state = NON;
			return true;
		}
	}

	return false;
}
bool Change_Block::moveR()
{
	if(state != NON)
	{
		if(dis > 0)
		{
			pos.x += c_speed;
			dis -= c_speed;
		}
		if(dis <= 0)
		{
			state = NON;
			return true;
		}
	}

	return false;
}
bool Change_Block::moveU()
{
	if(state != NON)
	{
		if(dis > 0)
		{
			pos.y -= c_speed;
			dis -= c_speed;
		}
		if(dis <= 0)
		{
			state = NON;
			return true;
		}
	}

	return false;
}
bool Change_Block::moveD()
{
	if(state != NON)
	{
		if(dis > 0)
		{
			pos.y += c_speed;
			dis -= c_speed;
		}
		if(dis <= 0)
		{
			state = NON;
			return true;
		}
	}

	return false;
}