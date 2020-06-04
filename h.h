#pragma once
class Graph
{
public:
	struct Node
	{
		Node* next;
		int distance;
		int number_where;
	private:
		void add_priv(int distance, int to, Node*& link1);
		void show_priv(Node* root);

	public:
		void add(Node*& link_tab, int distance, int to);
		void show(Node* root);
	};
private:
	int size;
	Node** ls;
	void dijsktra_priv(int start_node);
public:
	Graph();
	void show();
	void dijkstra(int start_node);

};