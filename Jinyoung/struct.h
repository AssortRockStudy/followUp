#pragma once

#include "TArray.h"

struct User
{
	char			name[10];
	int	Age;
	unsigned char	Sex; // 1, 2
	unsigned int	ID;
};


extern tArray<User> g_user;