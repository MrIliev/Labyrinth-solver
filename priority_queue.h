#pragma once
#include "Cell.h"
#include <unordered_set>

class PQueue
{
public:
	PQueue();

public:
	Node* top();
	Node* pop();
	void push(Node *);
	bool exists(const Node *) const;
	bool empty()
	{
		return(front.empty());
	}

private:
	PQueue(const PQueue &) = delete;
	PQueue& operator=(const PQueue &) = delete;
	
	

private:
	std::unordered_set<Node *> front;
};
