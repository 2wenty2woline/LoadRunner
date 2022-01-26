#pragma once
#include <string>
#include "Object.h"

class Character : public Object
{
public:
	Character();
	~Character();

	int			health			= 1;
	int			speedMovement	= 4;

	FRKey		currentSide;
};

