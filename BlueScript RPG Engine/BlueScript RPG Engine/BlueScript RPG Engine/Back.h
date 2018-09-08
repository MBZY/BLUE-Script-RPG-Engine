#pragma once

#include"Head.h"

class Character{
public:
	IMAGE** Pic;
	char* Name;
	unsigned char lmor;
	const void operator =(Character* Cha){
		*this->Pic = *Cha->Pic;
		delete[] this->Name;
		this->Name = new char[strlen(Cha->Name) + 1];
		strcpy(this->Name, Cha->Name);
		this->lmor=Cha->lmor;
	}
	const void operator ()(char*Name,IMAGE** Pic = NULL,byte lmor =0){
		this->Pic = new IMAGE*[2];
		if(Pic!=NULL)*this->Pic = *Pic;
		delete[] this->Name;
		this->Name = new char[strlen(Name) + 1];
		strcpy(this->Name, Name);
		this->lmor = lmor;
		LOG(Name);
	}
	Character(char* Name, IMAGE** Pic = NULL,byte lmor=0){
		this->Pic = new IMAGE*[2];
		if(Pic!=NULL)*this->Pic = *Pic;
		this->Name = new char[strlen(Name) + 1];
		strcpy(this->Name, Name);
		this->lmor = lmor;
		LOG(Name);
	}
};