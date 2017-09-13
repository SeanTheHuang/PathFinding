#pragma once

#include <vector>
#include <stack>

#include "node.h"
#include "level.h"

struct NodeInfo
{
	int index;
	int gCost, hCost;
};

class CPathFinding
{
public:
	static bool AStar(CNode*[GRID_WIDTH][GRID_HEIGHT], std::stack<CNode*>&, CNode*, CNode*);
	
private:
	static void ResetAStarValues(CNode*[GRID_WIDTH][GRID_HEIGHT], CNode*);
	static void GetSurroundingNodes(std::vector<CNode*>&, CNode*[GRID_WIDTH][GRID_HEIGHT], CNode*);

	static int GetDistanceBetweenNodes(CNode*, CNode*);
};