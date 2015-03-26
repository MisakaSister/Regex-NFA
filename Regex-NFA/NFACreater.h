#pragma once

#include "NFA_Graphics.h"

class NFACreater
{
public:
	NFACreater(void);
	~NFACreater(void);
	static NFA_Graphics* create();
};

