#pragma once

#include "Head.h"
#include "Back.h"
#include "Else.h"

class Form{
private:
	int LeaderNum;
public:
	Character** Leader;
	char *ActorName;
	char *String;
	IMAGE* Back;
	
	const void operator()(char* String, Character* Person = NULL, IMAGE* Back = FormBackGround,char* ActorName=NULL){
		if(ActorName)strcpy(this->ActorName, ActorName);
		else memset(this->ActorName, 0, sizeof(this->ActorName));
		this->Back = Back;
		delete[] String;
		this->String = new char[strlen(String) + 1];
		strcpy(this->String, String);
		if(Person!=NULL)this->Leader[LeaderNum++] = Person;
		TimesQueue.push(this);
	}
	Form(char* String, Character* Person = NULL ,char* ActorName=NULL, IMAGE* Back = FormBackGround){
		this->ActorName = new char[15];
		if(ActorName)strcpy(this->ActorName, ActorName);
		else strcpy(this->ActorName,Person->Name);
		Leader = new Character*[3];
		LeaderNum = 0;
		this->Back = Back;
		this->String = new char[strlen(String) + 1];
		strcpy(this->String, String);
		if(Person!=NULL)this->Leader[LeaderNum++] = Person;
		LOG(String);
		TimesQueue.push(this);
	}
	inline void PaintOn(COLORREF FILLCOLOR =WHITE, COLORREF LINECOLOR = BLACK,COLORREF TEXTCOLOR=BLACK){
		for (int i = 0; i < LeaderNum; i++){
			if (Leader[i] != NULL){
				if (Leader[i]->Pic != NULL)
					if (Leader[i]->lmor == 0)PutIma(Leader[i]->Pic, FirstCharacterX, FirstCharacterY);
					else if (Leader[i]->lmor == 1)PutIma(Leader[i]->Pic, SecondCharacterX, SecondCharacterY);
					else if (Leader[i]->lmor == 2)PutIma(Leader[i]->Pic, ThirdCharacterX, ThirdCharacterY);
			}
		}
		COLORREF FC = getfillcolor(), LC = getlinecolor();
		LINESTYLE FT;
		getlinestyle(&FT);
		setfillcolor(FILLCOLOR);
		setlinecolor(LINECOLOR);
		settextcolor(TEXTCOLOR);
		setlinestyle(PS_SOLID, PLineWidth);
		if (this->Back == NULL)fillrectangle(Formsx, Formsy, Formex, Formey);
		else putimage(Formsx, Formsy, this->Back);
		fillrectangle(NameFormsx,NameFormsy,NameFormex,NameFormey);
		setfillcolor(FC),setlinecolor(LC),setlinestyle(&FT);
		char* strr = new char[strlen(String) + 10];
		int sle[300] = {0};
		strcpy(strr, String);
		LOG(strlen(strr));
		for (int i = 1; i < strlen(strr); i++){
			if (isascii(strr[i]))sle[i] = sle[i - 1] + 1;
			else sle[i] = sle[i - 1];
		}
		for (int i = 1; i <= strlen(strr)/LineLength; i++){
			if (isascii(strr[i*LineLength])){
				char s[1024];
				strcpy(s, strr + i*LineLength);
				strcpy(strr + i*LineLength + 1, s);
				strr[i*LineLength] = '\n';
			}
			else{
				LOG("DOING");
				char s[1024];
				strcpy(s, strr + i*LineLength - sle[i*LineLength]%2);
				LOG(s<<endl<<'2');
				strcpy(strr + i*LineLength - ((sle[i*LineLength] % 2)?0:1), s);
				strr[i*LineLength - sle[i*LineLength] % 2] = '\n';
			}
		}
		LOG(strr);
		RECT r = { Formsx + PLineWidth, Formsy + PLineWidth, Formex, Formey };
		RECT r2 = { NameFormsx + PLineWidth, NameFormsy + PLineWidth, NameFormex, NameFormey };
		drawtext(strr, &r, DT_WORDBREAK);
		if (Leader != NULL) drawtext(ActorName, &r2, DT_WORD_ELLIPSIS); 
		delete[] strr;
	}
};

bool IsOnForm(MOUSEMSG MSG){
	if (MSG.x >= Formsx&&MSG.x <= Formex&&MSG.y >= Formsy&&MSG.y <= Formey)return true;
	else return false;
}

bool CanPast(){
	if (MouseHit()){
		MOUSEMSG MSG;
		MSG = GetMouseMsg();
		if (MSG.uMsg == WM_LBUTTONDOWN)
			if (IsOnForm(MSG))return true;
			else return false;
		else return false;
	}
	else if (_kbhit()){
		int ch = 0;
		ch = _getch();
		if (ch == '\r' || ch == '\n' || ch == ' ')return true;
		else return false;
	}
	return false;
}

void DoForm(Form Fh){
	Fh.PaintOn(WHITE,BLACK,RED);
	while (!CanPast());
}

void FormInThread(){
	LOG("In the Thread");
	while (!EngineEnd){
		if (TimesQueue.empty() != true){
			DoForm(*TimesQueue.front());
			TimesQueue.pop();
			BackGroundRefresh = true;
			while (BackGroundRefresh)Sleep(10);
			LOG("In the Thread");
		}
		Sleep(10);
	}
}

void readfpic(Form* f, char* Path){
	if (Path == NULL || f == NULL || _access(Path, 0))LOG("ERROR , The Path is NULL");
	else loadimage(f->Back, Path, Formex, Formey, true);
}