#include <iostream>
#include <fstream>
#include "h.h"

int main()
{
	Graph* nowy = new Graph;
	nowy->show();
	nowy->dijkstra(0);

	system("PAUSE");
	return 0;
}