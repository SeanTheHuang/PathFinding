#include "pathfinding.h"

#include "AStarQueue.h"
#include <vector>


bool CPathFinding::AStar(CNode* nodeMatrix[GRID_WIDTH][GRID_HEIGHT], std::stack<CNode*>& outputStack,
						 CNode* startNode, CNode* endNode)
//Return: True - Found path
//        False - No path
{
	ResetAStarValues(nodeMatrix, endNode);

	std::vector<CNode*> tempVec;
	std::vector<CNode*> closedSet;
	AStarQueue openSet;

	openSet.Insert(startNode);
	startNode->SetGCost(0);

	while (!openSet.Empty())
	{
		CNode* currentNode = openSet.Pop();
		closedSet.push_back(currentNode);

		if (currentNode == endNode)	//Found target! start tracing back
		{
			currentNode = currentNode->m_previousNodeInPath;
			while (currentNode != startNode) //Create path back to start node
			{
				outputStack.push(currentNode);
				currentNode = currentNode->m_previousNodeInPath;
			}

			return true; //Tell others of your success
		}

		//Get valid surrounding nodes
		GetSurroundingNodes(tempVec, nodeMatrix, currentNode);

		for (size_t i = 0; i < tempVec.size(); i++)	//Go through each node
		{
			//Make sure node is not in closed set
			if (std::find(closedSet.begin(), closedSet.end(), tempVec[i]) == closedSet.end())
			{
				if (GetDistanceBetweenNodes(currentNode, tempVec[i]) + currentNode->GCost()
						< tempVec[i]->GCost())
				{	//Found shorter path
					//Update path
					tempVec[i]->SetGCost(GetDistanceBetweenNodes(currentNode, tempVec[i]) + currentNode->GCost());
					tempVec[i]->m_previousNodeInPath = currentNode;

					//If node is not in open set, add to open set
					if (!openSet.Find(tempVec[i]))
					{
						openSet.Insert(tempVec[i]);
					}
				}
			}
		}

		//Finished with this batch of nodes, clear vector
		tempVec.clear();
	}

	return false; //Only reach here if no path could be found!
}

void CPathFinding::ResetAStarValues(CNode* nodes[GRID_WIDTH][GRID_HEIGHT], CNode* targetNode)
{
	for (size_t i = 0; i < GRID_WIDTH; i++)
	{
		for (size_t j = 0; j < GRID_HEIGHT; j++)
		{
			nodes[i][j]->SetGCost(INT16_MAX);
			nodes[i][j]->SetHCost(GetDistanceBetweenNodes(targetNode, nodes[i][j]));
			nodes[i][j]->m_previousNodeInPath = NULL;
		}
	}
}

void CPathFinding::GetSurroundingNodes(std::vector<CNode*>& output, 
					CNode* nodeMatrix[GRID_WIDTH][GRID_HEIGHT], CNode* target)
{
	// === BEWARE: Ugly ===
	
	//Hard coding picking nodes
	bool leftFree, rightFree, botFree, topFree;
	leftFree = rightFree = topFree = botFree = false;

	//First: adjecent nodes
	int tempX = target->XCoord();
	int tempY = target->YCoord();

	if (tempX - 1 >= 0) //Left
	{
		if (nodeMatrix[tempX - 1][tempY]->NodeIsWalkable())
		{
			output.push_back(nodeMatrix[tempX - 1][tempY]);
			leftFree = true;
		}
	}

	if (tempX + 1 < GRID_WIDTH) // Right
	{
		if (nodeMatrix[tempX + 1][tempY]->NodeIsWalkable())
		{
			output.push_back(nodeMatrix[tempX + 1][tempY]);
			rightFree = true;
		}
	}

	if (tempY - 1 >= 0)	//Top
	{
		if (nodeMatrix[tempX][tempY - 1]->NodeIsWalkable())
		{
			output.push_back(nodeMatrix[tempX][tempY-1]);
			topFree = true;
		}
	}

	if (tempY + 1 < GRID_HEIGHT)	//Bottom
	{
		if (nodeMatrix[tempX][tempY + 1]->NodeIsWalkable())
		{
			output.push_back(nodeMatrix[tempX][tempY+1]);
			botFree = true;
		}
	}

	//Now check diagonals, make sure not passable if wall inbetween diagonal movement

	if (tempX - 1 >= 0 && tempY - 1 >= 0 && topFree && leftFree)	//Top left
	{
		if (nodeMatrix[tempX - 1][tempY - 1]->NodeIsWalkable())
		{
			output.push_back(nodeMatrix[tempX - 1][tempY - 1]);
		}
	}

	if (tempX + 1 >= 0 && tempY - 1 >= 0 && topFree && rightFree)	//Top right
	{
		if (nodeMatrix[tempX + 1][tempY - 1]->NodeIsWalkable())
		{
			output.push_back(nodeMatrix[tempX + 1][tempY - 1]);
		}
	}

	if (tempX - 1 >= 0 && tempY + 1 >= 0 && botFree && leftFree)	//Bot left
	{
		if (nodeMatrix[tempX - 1][tempY + 1]->NodeIsWalkable())
		{
			output.push_back(nodeMatrix[tempX - 1][tempY + 1]);
		}
	}

	if (tempX + 1 >= 0 && tempY + 1 >= 0 && botFree && rightFree)	//Bot right
	{
		if (nodeMatrix[tempX + 1][tempY + 1]->NodeIsWalkable())
		{
			output.push_back(nodeMatrix[tempX + 1][tempY + 1]);
		}
	}
}

int CPathFinding::GetDistanceBetweenNodes(CNode* nodeA, CNode* nodeB)
{
	int xDiff = (int)abs(nodeA->XCoord() - nodeB->XCoord());
	int yDiff = (int)abs(nodeA->YCoord() - nodeB->YCoord());

	int diffOfDiff = (int)abs(xDiff - yDiff);
	int largerDiff = (xDiff > yDiff) ? xDiff : yDiff;

	return (10 * diffOfDiff + 14 * (largerDiff - diffOfDiff));
	
}