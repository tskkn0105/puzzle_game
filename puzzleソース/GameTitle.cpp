#include "GameMain.h"
#include <math.h>


void game::gameTitle()
{
	DrawGraph(0,0,g_title,false);


	DrawFormatStringToHandle(224,300 + (int)(sin(si)*5),GetColor(255,255,255),big_font," 1P‚ªƒ{ƒ^ƒ“‚ğ");
	DrawFormatStringToHandle(224,332 + (int)(sin(si)*5),GetColor(255,255,255),big_font,"    ‚¨‚·‚Æ   ");
	DrawFormatStringToHandle(224,364 + (int)(sin(si)*5),GetColor(255,255,255),big_font," ‚Í‚¶‚Ü‚é‚æI");

	si += 0.05;
	if(ps1.input[0] == 1)
	{
		gamestate =  BATTLE2;
		time = -300;

		cur1->init();
		cur2->init();
		for(int i=0;i<st->high*st->wide;i++)
		{
			bl1[i].get_state(NON);
			bl2[i].get_state(NON);
			d_bl1[i].get_state(NON);
			d_bl2[i].get_state(NON);
		}
	}

}