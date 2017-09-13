#pragma once

#include <vector>
#include "node.h"

class AStarQueue
{
public:
	AStarQueue() = default;
	~AStarQueue() = default;

	bool Empty();
	bool Find(CNode*);
	void Insert(CNode*);
	CNode* Pop();


private:
	std::vector<CNode*> m_container;

	bool GreaterPriority(CNode*, CNode*);
};