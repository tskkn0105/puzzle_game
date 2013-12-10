#include "Stage.h"
#include "DxLib.h"

Stage::Stage() :
wide(6),
high(12)
{}

Stage::~Stage()
{
}

bool Stage::load()
{
	g_stage = LoadGraph("media\\karistage.png");
	g_waku = LoadGraph("media\\waku.png");
	return true;
}

void Stage::draw()
{
	DrawGraph(0,0,g_stage,true);
}

void Stage::waku_draw()
{
	DrawGraph(0,0,g_waku,true);
}



