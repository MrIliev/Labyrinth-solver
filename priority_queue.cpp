#include "priority_queue.h"

PQueue::PQueue()
{  }

Node* PQueue::pop()
{
	Node* min = const_cast<Node*>(top());
	front.erase(min);
	return min;
}

 Node* PQueue::top()
{
	Node* min = NULL;
	size_t priority = INT_MAX;

	for (auto iter : front)
	{
		if (iter->get_level() < priority)
		{
			priority = iter->get_level();
			min = iter;
		}
	}
	return min;
}

void PQueue::push(Node* node)
{
	front.insert(node);
}

bool PQueue::exists(const Node* node) const
{
	if (front.empty())
		return false;

	for (auto iter : front)
	{
		//if (iter->location == node->location)
			return true;
	}

	return false;
}

