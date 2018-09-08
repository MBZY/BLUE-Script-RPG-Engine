#pragma once

#include"Head.h"


void WhileInThread(){
	while (!EngineEnd){
		while (!BackGroundRefresh){
			Sleep(10);
		}
		if (BackGround)putimage(0, 0, BackGround);
		else cleardevice();
		BackGroundRefresh = false;
	}
}

void InitEngine(){
	initgraph(640, 480, (_DEBUG) ? SHOWCONSOLE : 0);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	for (int i = 0; i < MaxThread; i++){
		Ts[i] = NULL;
	}
	settextstyle(FontHeight, 0, "ËÎÌו");
	settextcolor(BLACK);
	Ts[Tnum++] = new thread(FormInThread);
	Ts[Tnum++] = new thread(WhileInThread);
}

void EndEngine(){
	closegraph();
	EngineEnd = true;
	StopRefresh();
}

void StopRefresh(){
	for (int i = 0; i < MaxThread&&Ts[i] != NULL&&i < Tnum; i++){
		Ts[i]->join();
	}
}