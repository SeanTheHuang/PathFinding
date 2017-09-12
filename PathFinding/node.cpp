#include "node.h"

#include "resource.h"
#include "utils.h"
#include "game.h"

CNode::CNode(int iX, int iY)
{
	m_iX = iX;
	m_iY = iY;
	
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
