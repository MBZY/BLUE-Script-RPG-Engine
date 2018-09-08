#pragma once

#include"thread"
#include"graphics.h"
#include"cstdio"
#include"cstdlib"
#include"iostream"
#include"cstring"
#include"conio.h"
#include "io.h"
#include "process.h"
#include"queue"
using namespace std;

#define _DEBUG 1

#if _DEBUG
#define LOG(x) cout<<x<<endl
#else
#define LOG(x)
#endif

//Form.h
#define Formsx 40
#define Formsy 300
#define Formex 600
#define Formey 440
#define NameFormsx 40
#define NameFormsy 270
#define NameFormex 130
#define NameFormey 300
#define MaxThread 1024
#define FontHeight 20
#define LineLength 54
#define PLineWidth 5

class Form;
IMAGE *BackGround=NULL;
IMAGE *FormBackGround = NULL;
thread *Ts[1024];
int Tnum = 0;
bool EngineEnd = false;
bool IsOnForm(MOUSEMSG);
bool CanPast();
void DoForm(Form);
void readfpic(Form*, char*);
void FormInThread();
queue<Form*> TimesQueue;

//Back.h
#define FirstCharacterX 20
#define FirstCharacterY 40
#define SecondCharacterX 220
#define SecondCharacterY 40
#define ThirdCharacterX 420
#define ThirdCharacterY 40
#define CharacterWidth 200
#define CharacterHeight 40
class Character;

//Engine.h
bool BackGroundRefresh = 0;
void WhileInThread();
void InitEngine();
void EndEngine();
void StopRefresh();

//Else.h
void PutIma(IMAGE**);

