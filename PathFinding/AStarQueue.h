//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: AStarQueue.h
// Description	: defintion of AStarQueue. Class is specifically used in A* algorithm as the open set
// Author		: Sean Huang
// Mail			: sean.hua7281@mediadesign.school.nz
//

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