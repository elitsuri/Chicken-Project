#pragma once
#include "GameObject.h"

class ThrownObjects:public GameObject
{
public:
	ThrownObjects();
	virtual ~ThrownObjects();
	virtual void move(unsigned);
};