#pragma once

#include "../Utility/vec4.h"

struct Job
{
	int x, y;
	DIR d;

	Job(int x, int y, DIR d);
};

