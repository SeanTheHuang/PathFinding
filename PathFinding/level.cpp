//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: level.cpp
// Description	: implementation of level class
// Author		: Sean Huang
// Mail			: sean.hua7281@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include <math.h>
#include <time.h>

// This Include
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "pathfinding.h"
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

CLevel::CLevel()
	: m_startNode(NULL)
	, m_endNode(NULL)
{

}

CLevel::~CLevel()
{
	for (size_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (size_t x = 0; x < GRID_WIDTH; x++)
		{
			delete m_nodeMatrix[x][y];
		}
	}

	delete m_fpsCounter;
}

bool CLevel::Initialise(int _iWidth, int _iHeight)
{
	srand((unsigned int)time(NULL));

	//Window size
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	//Create FPS counter
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());
	
	//== Create Nodes Process ==

	//Create node early to get width/height of sprites
	CNode* newNode = new CNode(0, 0, 0, 0);
	m_iNodeSize = newNode->GetWidth();
	delete newNode;

	//Done with temp node, start filling up board

	m_iXOffset = (int)(m_iNodeSize / 2) + 16;
	m_iYOffset = (int)(m_iNodeSize / 2) + 20;

	//Start placing nodes
	int xPos = m_iXOffset;
	int yPos = m_iYOffset;

	for (size_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (size_t x = 0; x < GRID_WIDTH; x++)
		{
			m_nodeMatrix[x][y] = new CNode(xPos, yPos, x, y);

			xPos += m_iNodeSize;
		}

		xPos = m_iXOffset;
		yPos += m_iNodeSize;
	}
	
	return (true);
}

void CLevel::Draw()
{
	//Draw board
	for (size_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (size_t x = 0; x < GRID_WIDTH; x++)
		{
			m_nodeMatrix[x][y]->Draw();
		}
	}

	//Draw path on top
	for (size_t i = 0; i < m_vecPathNodes.size(); i++)
	{
		m_vecPathNodes[i]->Draw();
	}
}

void CLevel::Process(float _fDeltaTick)
{
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

void CLevel::ChangeNodeState(int xPos, int yPos, NODE_STATE newState)
{
	m_nodeMatrix[xPos][yPos]->UpdateNodeState(newState);
}

void CLevel::ProcessUserClick(int mouseX, int mouseY, NODE_STATE state)
{
	//Check if user pressed within node population;
	mouseX -= (m_iXOffset - m_iNodeSize/2);
	mouseY -= (m_iYOffset - m_iNodeSize/2);

	if (mouseX < 0 || mouseY < 0)
	{
		return;
	}
	else if (mouseX > (GRID_WIDTH * m_iNodeSize)
		|| mouseY > (GRID_HEIGHT * m_iNodeSize))
	{
		return;
	}

	//User pressed in range, figure out which node
	int xPos, yPos;

	xPos = mouseX / m_iNodeSize;
	yPos = mouseY / m_iNodeSize;

	//Check if updating singleton blocks
	if (state == PLAYER_STATE)
	{
		//Don't allow placing over singleton block
		if (m_nodeMatrix[xPos][yPos]->CurrentNodeState() == PLAYER_STATE
			|| m_nodeMatrix[xPos][yPos]->CurrentNodeState() == TARGET_STATE)
		{
			return;
		}

		//Change old position to empty (if exists)
		if (m_startNode != NULL)
		{
			m_startNode->UpdateNodeState(EMPTY_STATE);
		}

		m_startNode = m_nodeMatrix[xPos][yPos];
		m_startNode->UpdateNodeState(state);
	}
	else if (state == TARGET_STATE)
	{
		//Don't allow placing over singleton block
		if (m_nodeMatrix[xPos][yPos]->CurrentNodeState() == PLAYER_STATE
			|| m_nodeMatrix[xPos][yPos]->CurrentNodeState() == TARGET_STATE)
		{
			return;
		}

		//Change old position to empty (if exists)
		if (m_endNode != NULL)
		{
			m_endNode->UpdateNodeState(EMPTY_STATE);
		}

		m_endNode = m_nodeMatrix[xPos][yPos];
		m_endNode->UpdateNodeState(state);
	}
	else
	{
		m_nodeMatrix[xPos][yPos]->UpdateNodeState(state);

		//Make sure if change start node/end node state, the pointers say consistent
		if (m_nodeMatrix[xPos][yPos] == m_startNode)
		{
			m_startNode = NULL;
		}
		else if (m_nodeMatrix[xPos][yPos] == m_endNode)
		{
			m_endNode = NULL;
		}
	}
	
	//Signal to update path
	UpdatePath();
}

void CLevel::UpdatePath()
{
	ClearOldPath();

	//No start node or end node == NO PATH
	if (m_startNode == NULL || m_endNode == NULL)
	{
		return;
	}

	else if (!CPathFinding::AStar(m_nodeMatrix, m_pathStack, m_startNode, m_endNode))
	{
		//No path, clear previous path
		return;	
	}

	//Path found! empty path stack and fill board with path
	while (!m_pathStack.empty())
	{
		CNode* topNode = m_pathStack.top();
		m_pathStack.pop();

		CNode* pathNode = new CNode(topNode->GetX(), topNode->GetY(), 0, 0);
		pathNode->UpdateNodeState(PATH_STATE);
		m_vecPathNodes.push_back(pathNode);
	}
}


void CLevel::ClearOldPath()
{
	for (size_t i = 0; i < m_vecPathNodes.size(); i++)
	{
		delete m_vecPathNodes[i];
	}

	m_vecPathNodes.clear();
}
