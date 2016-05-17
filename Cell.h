#pragma once
#include <iostream>

struct Node
{
public:
	int PosX;
	int PosY;
	Node* parent;

	double cost;
	char symbol;
	double level;
	double distance;
	double priority;
	bool visited;
	bool inQueue;

	Node() : cost(0), priority(0), symbol(NULL), level(0), parent(NULL), distance(0), visited(false),inQueue(false) {};
	Node (int x, int y, double costt, char symb, double lev, double dist)
	{
		PosX = x;
		PosY = y;
		cost = costt;
		symbol = symb;
		level = lev;
		distance = dist;
		visited = false;

	}
	void set_Node(int x, int y, double costt, char symb, double lev, double dist)
	{
		PosX = x;
		PosY = y;
		cost = costt;
		symbol = symb;
		level = lev;
		distance = dist;
	}
	void set_visited()
	{
		visited = true;
	}
	void print_Node()
	{
		std::cout<<symbol;
	}
	bool isWalkable()
	{
		return(symbol != 'N');
	}
	void set_Node_cost(double costing, double lev)
	{
		cost = costing;
		level = lev+ cost + distance;
	}
	bool isVisited()
	{
		return visited == true;
	}
	double get_level() const
	{
		return priority;
	}
};