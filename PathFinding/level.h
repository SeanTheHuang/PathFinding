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

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>
#include <stack>

// Local Includes
#include "node.h"

// Types

// Constants

// Prototypes
class CFPSCounter;
class CBackGround;
class CLevel
{
	// Member Functions
public:
	CLevel();
	virtual ~CLevel();

	virtual bool Initialise(int _iWidth, int _iHeight);

	void Draw();
	void Process(float);

	void ProcessUserClick(int, int, NODE_STATE);

protected:
	void ChangeNodeState(int, NODE_STATE);
	void UpdatePath();


private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

	// Member Variables
public:

protected:


private:
	std::vector<CNode*> m_vecNode;
	int m_iWidth;
	int m_iHeight;

	int m_iNodesPerRow;
	int m_iNodesPerCol;

	int m_iXOffset;
	int m_iYOffset;

	int m_iNodeSize;

	CNode* m_startNode;
	CNode* m_endNode;

	std::stack<CNode*> m_pathStack;

	CFPSCounter* m_fpsCounter;
};

#endif    // __LEVEL_H__
