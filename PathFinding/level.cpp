//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Sean Huang
// Mail			: sean.hua7281@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include <math.h>
#include <time.h>

// This Include
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
	for (size_t i = 0; i < m_vecNode.size(); i++)
	{
		delete m_vecNode[i];
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
	CNode* newNode = new CNode(0, 0);
	m_iNodeSize = newNode->GetWidth();
	delete newNode;

	int xLimit = _iWidth - m_iNodeSize;
	int yLimit = _iHeight - m_iNodeSize - 30; //Includes offset of menu bar at top

	m_iXOffset = (int)(m_iNodeSize / 2) + 16;
	m_iYOffset = (int)(m_iNodeSize / 2) + 20;

	m_iNodesPerRow = 1 + (int)(xLimit - m_iXOffset) / m_iNodeSize;
	m_iNodesPerCol = 1 + (int)(yLimit - m_iYOffset) / m_iNodeSize;


	//Done with temp node, start filling up screen

	//Start placing nodes
	int xPos = m_iXOffset;
	int yPos = m_iYOffset;

	//Fill window, row by row
	while (yPos < yLimit)
	{
		newNode = new CNode(xPos, yPos);
		m_vecNode.push_back(newNode);

		xPos += newNode->GetWidth();

		if (xPos >= xLimit)
		{
			xPos = m_iXOffset;
			yPos += newNode->GetHeight();
		}
	}
	
	return (true);
}

void CLevel::Draw()
{
	for (size_t i = 0; i < m_vecNode.size(); i++)
	{
		m_vecNode[i]->Draw();
	}
}

void CLevel::Process(float _fDeltaTick)
{
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

void CLevel::ChangeNodeState(int index, NODE_STATE newState)
{
	m_vecNode[index]->UpdateNodeState(newState);
}

void CLevel::ProcessUserClick(int mouseX, int mouseY, NODE_STATE state)
{
	//Check if user pressed within node population;
	mouseX -= (m_iXOffset - m_iNodeSize/2);
	mouseY -= (m_iYOffset - m_iNodeSize / 2);

	if (mouseX < 0 || mouseY < 0)
	{
		return;
	}
	else if (mouseX > (m_iNodesPerRow * m_iNodeSize)
		|| mouseY > (m_iNodesPerCol * m_iNodeSize))
	{
		return;
	}

	//User pressed in range, figure out which node
	int xPos, yPos, index;

	xPos = mouseX / m_iNodeSize;
	yPos = mouseY / m_iNodeSize;

	index = xPos + (yPos * m_iNodesPerRow);

	//Check if updating singleton blocks
	if (state == PLAYER_STATE)
	{
		//Change old position to empty (if exists)
		if (m_startNode != NULL)
		{
			m_startNode->UpdateNodeState(EMPTY_STATE);
		}

		m_startNode = m_vecNode[index];
		m_startNode->UpdateNodeState(state);
	}
	else if (state == TARGET_STATE)
	{
		//Change old position to empty (if exists)
		if (m_endNode != NULL)
		{
			m_endNode->UpdateNodeState(EMPTY_STATE);
		}

		m_endNode = m_vecNode[index];
		m_endNode->UpdateNodeState(state);
	}
	else
	{
		m_vecNode[index]->UpdateNodeState(state);

		//Make sure if change start node/end node state, the pointers say consistent
		if (m_vecNode[index] == m_startNode)
		{
			m_startNode = NULL;
		}
		else if (m_vecNode[index] == m_endNode)
		{
			m_endNode = NULL;
		}
	}
	

	//Signal update path
	UpdatePath();
}

void CLevel::UpdatePath()
{
	//No start node or end node == NO PATH
	if (m_startNode == NULL || m_endNode == NULL)
	{
		return;
	}


}