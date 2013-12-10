#ifndef STAGE_H
#define STAGE_H



class Stage
{
private:
	int time;
	int score;
	int speed;
	int level;
	int combo;
	int valve;
	int x;
	int y;

	//‰æ‘œŠÖŒW
	int g_stage;
	int g_waku;
public:

	const int wide;
	const int high;
//	const int line[6];

	Stage();
	~Stage();

	bool load();
	void draw();
	void waku_draw();

	//void linecheck();
};










#endif