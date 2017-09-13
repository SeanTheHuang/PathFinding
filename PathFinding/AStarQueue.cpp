#include "AStarQueue.h"

#include <algorithm>

bool AStarQueue::Empty() { return m_container.empty(); }

void AStarQueue::Insert(CNode* newNode)
{
	//If empty, just place node
	if (m_container.empty())
	{
		m_container.push_back(newNode);
		return;
	}

	//Find out where in list node should be placed
	int targetIndex = 0;

	for (size_t i = 0; i < m_container.size(); i++)
	{
		if (GreaterPriority(newNode, m_container[i]))
			break;

		targetIndex++;
	}

	//Place said node
	m_container.insert(m_container.begin() + targetIndex, newNode);
}

CNode* AStarQueue::Pop()
{
	if (m_container.empty())
	{
		return NULL;
	}

	CNode* target = m_container.front();
	m_container.erase(m_container.begin());

	return target;
}

bool AStarQueue::GreaterPriority(CNode* newNode, CNode* targetNode)
{
	if (newNode->FCost() < targetNode->FCost())
	{
		return true;
	}
	else if ((newNode->FCost() == targetNode->FCost())
		&& (newNode->GCost() < targetNode->GCost()))
	{
		return true;
	}

	return false;	//Does not have higher priority
}

bool AStarQueue::Find(CNode* target)
{
	return std::find(m_container.begin(), m_container.end(), target) != m_container.end();
}