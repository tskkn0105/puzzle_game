#include "GameMain.h"


////再帰的に関数を呼び出して同じ色のブロックがいくつつながっているのか調べる
int game::clr_check(Block* bl,int n,int wide,int high)
{
	int temp = wide + high*st->wide;
	int temp_state = bl[temp].get_state();

	
	if(temp_state <NON && bl[temp].get_check_flag() == 0)
	{
		bl[temp].get_check_flag(OVER);
		n++; 

		if(wide > 0 && temp_state == bl[temp-1].get_state() && bl[temp-1].get_check_flag() == EVER)
		{ n = clr_check(bl,n,wide-1,high); }
		if(wide < st->wide-1 && temp_state == bl[temp+1].get_state() && bl[temp+1].get_check_flag() == EVER)
		{ n = clr_check(bl,n,wide+1,high); }
		if(high > 0 && temp_state == bl[temp-st->wide].get_state() && bl[temp-st->wide].get_check_flag() == EVER)
		{ n = clr_check(bl,n,wide,high-1); }
		if(high < st->high-1 && temp_state == bl[temp+st->wide].get_state() && bl[temp+st->wide].get_check_flag() == EVER)
		{ n = clr_check(bl,n,wide,high+1); }

	}
	return n;
}

//再帰を使ってブロックを消していく
int game::clr_block(Block* bl,int n,int wide,int high)
{
	const int max_chain = 3;
	int temp = wide + high*st->wide;
	int temp_state = bl[temp].get_state();
	
	if(n > max_chain && bl[temp].get_state() < NON)
	{
		bl[temp].get_check_flag(OFF);

		if(wide > 0 && temp_state == bl[temp-1].get_state() && bl[temp-1].get_check_flag() == OVER)
		{ clr_block(bl,n,wide-1,high); }
		if(wide < st->wide-1 && temp_state == bl[temp+1].get_state() && bl[temp+1].get_check_flag() == OVER)
		{ clr_block(bl,n,wide+1,high); }
		if(high > 0 && temp_state == bl[temp-st->wide].get_state() && bl[temp-st->wide].get_check_flag() == OVER)
		{ clr_block(bl,n,wide,high-1); }
		if(high < st->high-1 && temp_state == bl[temp+st->wide].get_state() && bl[temp+st->wide].get_check_flag() == OVER)
		{ clr_block(bl,n,wide,high+1); }

		//bl[temp].get_state(NON);
	}
	return n;
}
 //ブロックを落ちる状態に変えるかチェック
int game::Drop_check(Block* bl,Drop_Block* d_bl)
{
	int temp;
	bool drop_flag;

	for(int i=st->wide-1;i>=0;i--)
	{
		drop_flag = false;
		for(int j=st->high-1;j>=0;j--)
		{
			temp = i + j*st->wide;
			if(drop_flag == true && bl[temp].get_state() < NON)
			{
				d_bl[d_num].get_state(bl[temp].get_state());//状態をコピー
				d_bl[d_num].get_pos(bl[temp].get_pos());
				if(d_num < 72){ d_num++; }
				else{ d_num = 0; }

				bl[temp].get_state(NON);
			}

			if(bl[temp].get_state() == NON)
			{ drop_flag = true; }

		}

	}
	return 0;
}

void game::upper_check(Block* bl,Drop_Block* d_bl)
{
	for(int i=0;i<st->high * st->wide;i++)
	{
		if(bl[i].get_state() == UP)
		{
			d_bl[d_num].get_pos(bl[i].get_pos());
			d_bl[d_num].get_state(WHITE);
			d_bl[d_num].get_time(bl[i].get_time());
			d_num++;
			if(d_num >= 72){ d_num = 0; }
			bl[i].get_state(NON);
		}
	}
}