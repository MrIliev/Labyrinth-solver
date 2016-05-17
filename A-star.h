#pragma once
#include <iostream>
#include "Map.h"
#include <queue>
#include "priority_queue.h"

struct CompareNode : public std::binary_function<Node*, Node*, bool> 
{
	bool operator()(const Node* first, const Node* second) const
	{
		return first->get_level() < second->get_level() ;
	}
};


/*void calculate_cost_straight_moves(std::priority_queue<Node*,std::vector<Node*>,CompareNode>& front,Node* current,Node* buff,double currLevel) //calculate cost of the neighbor
{
	
	if((!buff->isVisited()) && buff->isWalkable() )
	{
		buff->parent = current;
		if ((current->symbol == '`') || (current->symbol == 'M' ))
		{
			buff->set_Node_cost(1, currLevel);
			front.push(buff);
		}
		if (current->symbol == '~')
		{
			buff->set_Node_cost(2, currLevel);
			front.push(buff);
		}
	}
}
void calculate_cost_diagonal_moves(std::priority_queue<Node*,std::vector<Node*>,CompareNode>& front,Node* current,Node* buff,double currLevel) //calculate cost of the neighbor
{
	if((!buff->isVisited()) && buff->isWalkable() )
	{
		buff->parent = current;
		if ((current->symbol == '`') || (current->symbol == 'M' ))
		{
			buff->set_Node_cost(1.5, currLevel);
			front.push(buff);
		}
		if (current->symbol == '~')
		{
			buff->set_Node_cost(2, currLevel);
			front.push(buff);
		}
	}
}*/

#include <iostream>
using std::cout;
void print(map& lap, int endX,int endY)
{
	Node* current = lap.get_Cell(endX, endY);
	while (current)
	{
		cout << "(" << current->PosX << "," << current->PosY << "),";
		current = current->parent;
	}
	cout << std::endl;
}
bool A_Star(char*path, int begX, int begY, int endX, int endY)
{
	map Labyrynt;
	Labyrynt.read_From_File(path);
	Labyrynt.setDistance(endX,endY);
	double currLevel = 0;
	Node* current;
//	Node* next;
	/*std::priority_queue<Node*, std::vector<Node*>, CompareNode> front;*/
	PQueue front;
	front.push( Labyrynt.get_Cell(begX,begY));
	Labyrynt.get_Cell(begX, begY)->visited = true;
	Labyrynt.get_Cell(begX, begY)->inQueue = true;
	while(!front.empty())
	{
		current = front.top();
		front.pop();
		current->inQueue = false;
		current->set_visited();
		if (current->symbol == 'X')
		{
			print(Labyrynt, endX, endY);
			//std::cout << endX << " " << endY << "\n" << Labyrynt.get_Cell(endX, endY)->symbol;
			return true;
		}
		int posx = current->PosX;
		int posy = current->PosY;
		std::vector<Node*> neighbours;
		Labyrynt.get_neighbours(neighbours, posx, posy);

		size_t len = neighbours.size();
		for (size_t i = 0; i < len; i++)
		{
			Node* neighbour = neighbours[i];
			Labyrynt.calculate_priority(current, neighbour/*, Labyrynt.get_Cell(endX, endY)*/);
			current->visited = true;
			

			front.push(neighbour);
		}
		
		/*neighbours.clear();
		Labyrynt.get_visited_neighbours(neighbours, posx, posy);
		len = neighbours.size();
		for (size_t i = 0; i < len; i++)
		{
			Node* neighbour = neighbours[i];

			double distance = Labyrynt.calculateDistance(*current, neighbour->PosX, neighbour->PosY);
			if (current->priority + distance < neighbour->priority)
			{
				Labyrynt.calculate_priority(current, neighbour, Labyrynt.get_Cell(endX, endY));
				front.push(neighbour);
			}
		}*/
	}
	return false;


};