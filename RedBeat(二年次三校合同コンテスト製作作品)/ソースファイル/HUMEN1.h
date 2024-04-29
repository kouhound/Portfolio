#pragma once
typedef struct {
	bool lane1;
	bool lane2;
	bool lane3;
	bool lane4;
	bool Exist;
	int Beat;
	int FourHalfBeat;
}NOTE;
typedef struct {
	float x;
	float y;
	float z;
}Float_3;
//int FINISH;
void initHumen();
void UninitHumen();
void UpdateHumen();
bool CheckNote(int i);
bool GetNote(int i);
//#include <nn/time/time_StandardSteadyClock.h>

int GetFramecount();