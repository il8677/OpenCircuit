#pragma once

enum DIR;

struct Job
{
	int x, y;
	DIR d;

	Job(int x, int y, DIR d);
};

