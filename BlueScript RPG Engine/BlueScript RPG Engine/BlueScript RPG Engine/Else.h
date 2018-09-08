#pragma once

#include"Head.h"

void PutIma(IMAGE** IMG,int x,int y){
	if (IMG == NULL)return;
	if (IMG[1] != NULL)putimage(x, y, &IMG[0][1], NOTSRCERASE);
	if (IMG[0] != NULL)putimage(x, y, &IMG[0][0], SRCINVERT);
}
void LoadIma(IMAGE* IMG, char* Front,char*Back){
	if (IMG){
		loadimage(&IMG[0], Front, 200, 560, true);
		loadimage(&IMG[1], Back, 200, 560, true);
	}
}