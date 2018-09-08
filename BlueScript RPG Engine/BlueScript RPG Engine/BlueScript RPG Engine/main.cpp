#include"cstdio"
#include"cstdlib"
#include"iostream"
#include"Head.h"
#include"Form.h"
#include"Back.h"
#include"Engine.h"
#include"Else.h"
#include <Windows.h>
using namespace std;
int main(){
	InitEngine();
	setbkcolor(WHITE);
	IMAGE *img,TIMEHERE,TIMEHERE2;
	img = new IMAGE[2];
	loadimage(&TIMEHERE, "SampleBack.png", 560, 140, true);
	FormBackGround = &TIMEHERE;
	loadimage(&TIMEHERE2, "SampleBG.jpg", 640, 480, true);
	BackGround = &TIMEHERE2;
	BackGroundRefresh = true;
	LoadIma(img, "PersonTemple2-1.jpeg", "PersonTemple2-2.jpeg");
	Character Jack("Jack",&img,1);
	Form f("123456456", &Jack);

	StopRefresh();
	EndEngine();
}