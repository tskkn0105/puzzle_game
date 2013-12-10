#include "GameMain.h"


void game::gameLoad()
{
	int temp = NULL;
	//////後で書き直す系/////////////
	back = LoadGraph("media\\back3.jpg");
	se_drop = LoadSoundMem("media\\drop.ogg");
	se_down = LoadSoundMem("media\\down.ogg");
	bgm[0] = LoadSoundMem("media\\loop1.ogg");
	bgm[1] = LoadSoundMem("media\\loop2.ogg");
	bgm[2] = LoadSoundMem("media\\loop3.ogg");
	bgm[3] = LoadSoundMem("media\\loop4.ogg");
	g_title = LoadGraph("media\\title.jpg");
	/****************************************/

	st = new Stage;	//ステージの読み込み
	st->load();

	big_font = CreateFontToHandle(NULL,28,5,DX_FONTTYPE_ANTIALIASING);


	/////////ブロック画像をロードする///////////////////////////
	const int MAX_BLOCK = st->wide * st->high + 8;//6*12 + 7 +1(予備)

	bl1 = new Block [MAX_BLOCK];
	d_bl1 = new Drop_Block[MAX_BLOCK];
	bl2 = new Block [MAX_BLOCK];
	d_bl2 = new Drop_Block[MAX_BLOCK];

	int* g_ray;
	temp = d_bl1[0].G_RAY;
	g_ray = new int [temp];
	LoadDivGraph("media\\ray.png",temp,temp,1,50,150,g_ray);

	int* g_Block;		//すぐに消えるがアドレスはブロックに渡されるので問題なし
	g_Block = new int [bl1[0].G_BLOCK];
	LoadDivGraph("media\\kari_block.png",bl1[0].G_BLOCK,bl1[0].G_BLOCK/2,2,32,32,g_Block);

	for(int i=0;i<MAX_BLOCK;i++){ bl1[i].load(g_Block); }
	for(int i=0;i<MAX_BLOCK;i++){ d_bl1[i].load(g_Block,g_ray); }
	for(int i=0;i<MAX_BLOCK;i++){ bl2[i].load(g_Block); }
	for(int i=0;i<MAX_BLOCK;i++){ d_bl2[i].load(g_Block,g_ray); }
	/***********************************************************/

	////カーソル関係のロード///////////////////////////////
	cur1 = new Cursor; //カーソルの動的配列を確保
	cur2 = new Cursor; //カーソルの動的配列を確保
	Change_Block* c_bl;
	c_bl = new Change_Block[cur1->block_num];	//カーソルのかずぶん
	for(int i=0;i<cur1->block_num;i++){ c_bl[i].load(g_Block); }

	int g_cursor = LoadGraph("media\\cursor.png");
	int se_change = LoadSoundMem("media\\change.ogg");
	int se_move = LoadSoundMem("media\\move.ogg");

	cur1->load(g_cursor,se_change,se_move);
	cur1->get_c_bl(c_bl);
	cur2->load(g_cursor,se_change,se_move);
	c_bl = new Change_Block[cur1->block_num];	//カーソルのかずぶん
	for(int i=0;i<cur1->block_num;i++){ c_bl[i].load(g_Block); }
	cur2->get_c_bl(c_bl);
	/*******************************************************/

	DrawString(300,230,"ロード!!!",GetColor(255,255,255));

	gamestate = TITLE;
}