#include "h.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void Graph::Node::add_priv(int distance, int to, Node*& root)
{
	Node* nowy = new Node;
	nowy->distance = distance;
	nowy->number_where = to;
	nowy->next = root;
	root = nowy; //
}

void Graph::Node::show_priv(Node* link2)
{
	while (link2)
	{
		std::cout << link2->distance << "(" << link2->number_where << ")";
		link2 = link2->next;
	}
	std::cout << std::endl;
}



Graph::Graph()
{
	fstream plik;
	plik.open("graph.txt");
	int current_number;

	plik >> size;
	ls = new Node *[size];

	for (int i = 0; i < size; i++)
	{
		//ls[i] = new Node;
		ls[i] = NULL;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			plik >> current_number;

			if (current_number != 0)
				ls[i]->add(ls[i], current_number, j);
		}
	}
}

void Graph::show()
{
	for (int i = 0; i < size; i++)
	{
		ls[i]->show(ls[i]);
	}
}

void Graph::Node::add(Node*& link_tab, int distance, int to)
{
	add_priv(distance, to, link_tab);
}

void Graph::Node::show(Node* root)
{
	show_priv(root);
}

//------------------------------------------Algorytm dikstry------------------------------------------//
void fill_tab(int*tab, int size, int value)
{
	for (int i = 0; i < size; i++)
	{
		tab[i] = value;
	}    //wypelnienie tablicy value
}

void show_tab(int* color, int* prev, int* total_distance, int size)
{
	cout << endl << "[C] "; //kolor
	for (int i = 0; i < size; i++)
	{
		cout << color[i] << " | ";
	}
	cout << endl; //poprzednik
	cout << "[P] ";
	for (int i = 0; i < size; i++)
	{
		cout << prev[i] << " | ";
	}
	cout << endl;
	cout << "[D] "; //drogaa
	for (int i = 0; i < size; i++)
	{
		cout << total_distance[i] << " | ";
	}
	cout << endl;
}

int min_tab(int* color, int* total_distance, int size, Graph::Node** ls)
{
	int min;
	min = 999999;
	for (int i = 0; i < size; i++)
	{
		if (color[i] == 1) //jesli szary
		{
			if (min == 999999)
			{
				min = i; 
			}
			if (total_distance[i] < total_distance[min])
			{
				min = i;
			}
		}
	} //zwraca minimum w tablicy

	return min;
}

void Graph::dijsktra_priv(int start_node)
{
	int* color = new int[size];
	int* prev = new int[size];
	int* total_distance = new int[size];

	fill_tab(color, size, 0); 
	fill_tab(prev, size, -1);
	fill_tab(total_distance, size, -1);

	show_tab(color, prev, total_distance, size);

	color[start_node] = 2; //wierzcholek startowy ma kolor czarny
	prev[start_node] = -1; //nie ma poprzednika
	total_distance[start_node] = 0; //odleglosc do tego wierzcholka startowego xd rowna 0 

	show_tab(color, prev, total_distance, size);

	for(int i=size; i--; i>0)
	{
		while (ls[start_node])
		{
			if (color[ls[start_node]->number_where] == 1) //jesli wierzcholek do ktorego idziemy jest szary
			{
				if (total_distance[start_node] + ls[start_node]->distance < total_distance[ls[start_node]->number_where]) //sprawdzamy czy jest to najkrotsza droga
				{
					color[ls[start_node]->number_where] = 1; //nei zmieniamy
					prev[ls[start_node]->number_where] = start_node; //staje sie naszym startowym
					total_distance[ls[start_node]->number_where] = ((total_distance[start_node]) + (ls[start_node]->distance)); //updatujemy calkowita droge o koszt przejscia
				}
			}

			if (color[ls[start_node]->number_where] == 0) //jesli bialy
			{
				color[ls[start_node]->number_where] = 1; //zmieniamy na szary
				prev[ls[start_node]->number_where] = start_node;//staje sie startowym 
				total_distance[ls[start_node]->number_where] = ((total_distance[start_node]) + (ls[start_node]->distance)); //updatujemy
			}

			ls[start_node] = ls[start_node]->next; 
		}
		color[start_node] = 2; //czarny
		show_tab(color, prev, total_distance, size); //wyswietlamy
		start_node = min_tab(color, total_distance, size, ls); //startowym staje sie minimmalny
		cout << start_node << endl;

	}


}

void Graph::dijkstra(int start_node)
{
	dijsktra_priv(start_node);
}