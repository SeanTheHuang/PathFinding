#include "node.h"

#include "resource.h"
#include "utils.h"
#include "game.h"

CNode::CNode(int iX, int iY, int xCoord, int yCoord)
{
	m_iX = iX;
	m_iY = iY;

	m_iGCost = INT16_MAX;
	m_iHCost = INT16_MAX;

	m_iXCoord = xCoord;
	m_iYCoord = yCoord;

	m_previousNodeInPath = NULL;

	UpdateNodeState(EMPTY_STATE);
}

CNode::~CNode()
{

}

void CNode::Draw()
{
	CSprite::Draw();
}

void CNode::Process(float _fDeltaTick)
{
	CSprite::Process(_fDeltaTick);
}

bool CNode::UpdateNodeState(NODE_STATE newState)
{
	m_currentNodeState = newState;

	switch (newState)
	{
	case (EMPTY_STATE):
	{
		VALIDATE(CSprite::Initialise(IDB_EMPTY, IDB_EMPTY));
		break;
	}
	case (BLOCKED_STATE):
	{
		VALIDATE(CSprite::Initialise(IDB_BLOCKED, IDB_BLOCKED));
		break;
	}
	case (PLAYER_STATE):
	{
		VALIDATE(CSprite::Initialise(IDB_PLAYER, IDB_PLAYER));
		break;
	}
	case (TARGET_STATE):
	{
		VALIDATE(CSprite::Initialise(IDB_TARGET, IDB_TARGET));
		break;
	}
	case (PATH_STATE):
	{
		VALIDATE(CSprite::Initialise(IDB_PATH, IDB_PATH));
		break;
	}
	default:
		break;
	}

	return true;
}

int CNode::GCost() { return m_iGCost; }
int CNode::HCost() { return m_iHCost; }
int CNode::FCost() { return m_iGCost + m_iHCost; }

void CNode::SetGCost(int newVal) { m_iGCost = newVal; }
void CNode::SetHCost(int newVal) { m_iHCost = newVal; }

int CNode::XCoord() { return m_iXCoord; }
int CNode::YCoord() { return m_iYCoord; }

bool CNode::NodeIsWalkable() 
{ 
	return (m_currentNodeState != BLOCKED_STATE
		&& m_currentNodeState != PLAYER_STATE);

}

NODE_STATE CNode::CurrentNodeState() { return m_currentNodeState; }