#include "GameMain.h"


void game::gameBattle2()
{
	const Position nut1(16,64);	//左上ブロックの初期位置
	const Position nut2(432,64);
	const int bl_size = 32;	//ブロックの大きさ

	if(cur1->get_life() <= st->wide && cur2->get_life() <= st->wide && time>=0)
	{
		play(&nut1,bl1,d_bl1,cur1,&ps1);
//		play(&nut2,bl2,d_bl2,cur2,&ps2);
	}

	////攻撃関係//////////////////
	if(cur1->get_attack() < 0)
	{
		if( cur1->get_attack(cur1->get_attack()*(-1)) > cur1->get_damage())
		{
			cur2->get_damage(cur2->get_damage() + cur1->get_attack() - cur1->get_damage()); 
			cur1->get_damage(0);
		}
		else
		{ cur1->get_damage(cur1->get_damage() - cur1->get_attack()); }
		cur1->get_attack(0);
	}
	if(cur2->get_attack() < 0)
	{
		if( cur2->get_attack(cur2->get_attack()*(-1)) > cur2->get_damage())
		{
			cur1->get_damage(cur1->get_damage() + cur2->get_attack() - cur2->get_damage()); 
			cur2->get_damage(0);
		}
		else
		{ cur2->get_damage(cur2->get_damage() - cur2->get_attack()); }
		cur2->get_attack(0);
	}
	/*********************************/

	//描画関係↓
	DrawGraph(0,0,back,true);
	st->draw();
	for(int i=0;i<st->wide*st->high;i++)
	{ bl1[i].draw(&nut1,bl_size); }
	for(int i=0;i<72;i++)
	{ d_bl1[i].draw(&nut1); }
	cur1->draw(&nut1,bl_size);

	//描画関係2↓
	for(int i=0;i<st->wide*st->high;i++)
	{ bl2[i].draw(&nut2,bl_size); }
	for(int i=0;i<72;i++)
	{ d_bl2[i].draw(&nut2); }
	cur2->draw(&nut2,bl_size);
	st->waku_draw();

	if(time > 0)
	{

		if(cur1->get_life() > st->wide)
		{
			DrawFormatStringToHandle(224,144,GetColor(255,255,255),big_font," 2Pのかち！"); 
			if(ps1.input[0] == 1){ gamestate = TITLE; }
			for(int i=0;i<4;i++){ StopSoundMem(bgm[i]);}
		}
		else if(cur2->get_life() > st->wide)
		{
			DrawFormatStringToHandle(224,144,GetColor(255,255,255),big_font," 1Pのかち！"); 
			if(ps1.input[0] == 1){ gamestate = TITLE; }
			for(int i=0;i<4;i++){ StopSoundMem(bgm[i]);}
		}
		DrawFormatStringToHandle(224,96,GetColor(255,255,255),big_font,"1P");
		DrawFormatStringToHandle(336,96,GetColor(255,255,255),big_font," 2P");
		DrawFormatStringToHandle(224,256,GetColor(255,255,255),big_font,"はやさ");
		DrawFormatStringToHandle(336,256,GetColor(255,255,255),big_font,"はやさ");
		DrawFormatStringToHandle(250,288,GetColor(255,255,255),big_font,"%d",61 - cur1->get_pace());
		DrawFormatStringToHandle(362,288,GetColor(255,255,255),big_font,"%d",61 - cur2->get_pace());
		if(cur1->get_rensa() > 0)
		{DrawFormatStringToHandle(224,320,GetColor(255,255,255),big_font,"%d れんさ!",cur1->get_rensa()); }
		if(cur2->get_rensa() > 0)
		{DrawFormatStringToHandle(304,320,GetColor(255,255,255),big_font,"%d れんさ!",cur2->get_rensa()); }
		if(cur1->get_damage() > 0)
		{DrawFormatStringToHandle(224,352,GetColor(255,180,180),big_font,"残り %d",cur1->get_damage()); }
		if(cur2->get_damage() > 0)
		{DrawFormatStringToHandle(320,352,GetColor(255,180,180),big_font,"残り %d",cur2->get_damage()); }
	}
	else if(time==0){ PlaySoundMem(bgm[GetRand(3)],DX_PLAYTYPE_LOOP); }
	else if(time > -240)
	{
		DrawFormatStringToHandle(224,144,GetColor(255,255,255),big_font," よーい");
		if(time > -220)
		{ DrawFormatStringToHandle(224,176,GetColor(255,255,255),big_font,"　 ・"); }
		if(time > -180)
		{ DrawFormatStringToHandle(224,208,GetColor(255,255,255),big_font,"　 ・"); }
		if(time > -140)
		{ DrawFormatStringToHandle(224,240,GetColor(255,255,255),big_font,"　 ・"); }
		if(time > -60)
		{ DrawFormatStringToHandle(224,272,GetColor(255,255,255),big_font," スタート！"); }
	}

#ifdef _DEBUG
	clsDx();
	printfDx("\n\n\nup %d\ndown %d\nleft %d\nright %d\n1 %d\n2 %d\n3 %d\n4 %d\n5 %d",ps1.up,ps1.down,ps1.left,ps1.right,ps1.input[0],ps1.input[1],ps1.input[2],ps1.input[3],ps1.input[4]);
#endif
	time++;
}

void game::play(const Position* nut,Block* bl,Drop_Block* d_bl,Cursor* cur,padstate* ps)
{
	int temp = 0;

	//ブロック配置場所の初期化
	if(time == 0)
	{
		for(int i=0;i<st->high;i++)
		{
			for(int j=0;j<st->wide;j++)
			{
				bl[ j+i*st->wide ].get_pos(j,i);
			}
		}
	}

	cur->move(ps,bl,st->wide,st->high);	//カーソルの移動
	cur->change(ps,bl,st->wide,st->high);//ブロック入れ替え

	Drop_check(bl,d_bl); //ブロックをDrop状態に変えるかチェック
	for(int i=0;i<st->high;i++)
	{
		for(int j=0;j<st->wide;j++)
		{
			temp = clr_block(bl,clr_check(bl,0,j,i),j,i);//ブロックを消すかチェック
			if(temp > 3)//max_chain = 3;
			{
				if(cur->get_rensa() == 0)
				{ 
					cur->get_rensa(1);
					cur->get_rensa_time(40);
					cur->get_attack(cur->get_attack()+temp/2);
				}
				else if(cur->get_rensa_time() > 0)
				{
					cur->get_rensa(cur->get_rensa()+1);
					cur->get_rensa_time(40);
					cur->get_attack(cur->get_attack()+cur->get_rensa()*temp/2);
				}
				

			}
		}
	}
	if(cur->get_rensa_time() != 0)
	{ cur->get_rensa_time(cur->get_rensa_time()-1); }
	else
	{
		cur->get_rensa(0); 
		cur->get_attack(cur->get_attack()*(-1));
	}

	upper_check(bl,d_bl);
	
	//tempはブロック落下間隔
	if(time%1200 == 0 && time>100 ){cur->get_pace((int)(cur->get_pace()/1.25));}
	if(cur->get_damage() != 0){ temp = cur->get_pace()/5+1; }
	else{ temp = cur->get_pace(); }

	if(time%temp==0 || time < 18)//ブロックを落とす
	{
		a = GetRand(5);
		while(bl[a].get_state() != NON)
		{
			a++;
			if(a>5){ a = 0; }
			cur->get_life( cur->get_life()+1 );
			if(cur->get_life()>6){ break; }
		}
		if(bl[a].get_state() == NON)
		{
			//	PlaySoundMem(se_drop,DX_PLAYTYPE_BACK);
			Position temp_pos(a,0);
		
			d_bl[d_num].get_state((BLOCKSTATE)GetRand(4));
			d_bl[d_num].get_pos(temp_pos);
			d_bl[d_num].get_check_flag(EVER);
			if(d_num < 72){ d_num++; }
			else{ d_num = 0; }

			cur->get_life(0);
			if(cur->get_damage() > 0){ cur->get_damage(cur->get_damage()-1); }
		}
	}

	for(int i=0;i<72;i++)
	{ d_bl[i].drop(bl,se_down); }
}