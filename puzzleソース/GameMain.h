#ifndef GAMEMAIN
#define GAMEMAIN

#include"PadState.h"
#include"Fps.h"
#include"Stage.h"
#include"Cursor.h"

#include "DxLib.h"


enum GAMESTATE { LOAD,TITLE,MENU,CHOICE,AREA,
				BATTLE1,BATTLE2,BATTLE3,
				CONTINUE,GAMEOVER,RANKING,RANK_ENTRY,
				OPTION,TUTORIAL };

class game
{
private:
	int back;	//後でなおせ
	int se_drop;//上に同じ
	int se_down;//上に同じ
	int a;//ue
	int bgm[4];
	int g_title;
	double si;


	int big_font; //フォント
	int time;
	bool end_flag;
	int d_num;
	GAMESTATE gamestate;

	FPS* f;
	padstate ps1;
	padstate ps2;

	Stage* st;
	Block* bl1;
	Drop_Block* d_bl1;	//落ちてくるブロック
	Cursor* cur1;

	Block* bl2;
	Drop_Block* d_bl2;	//落ちてくるブロック
	Cursor* cur2;
public:
	game();
	~game();

	int MAINLOOP();

	void gameLoad();
	void gameTitle();
	void gameMenu(){};
	void gameChoice(){};
	void gameArea(){};
	void gameBattle1(){};
	void gameBattle2();
	void gameBattle3(){};
	void gameContinue(){};
	void gameGameover(){};
	void gameRanking(){};
	void gameRank_entry(){};
	void gameOption(){};
	void gameTutorial(){};

	int clr_check(Block* bl,int n=0,int wide=0,int high=0);
	int clr_block(Block* bl,int n,int wide=0,int high=0);
	int Drop_check(Block* bl,Drop_Block* d_bl);
	void play(const Position* nut,Block* bl,Drop_Block* d_bl,Cursor* cur,padstate* ps);
	void upper_check(Block* bl,Drop_Block* d_bl);
};



#endif