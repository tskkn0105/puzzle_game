#ifndef PADSTATE_H
#define PADSTATE_H


class padstate
{
private:
	int pi[10];
	int next;
public:
	int up;
	int down;
	int left;
	int right;

	int input[10];

	padstate();
	int pad(int x);
};

















#endif