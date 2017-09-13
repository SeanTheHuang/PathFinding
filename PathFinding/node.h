#pragma once

#include "sprite.h"

enum NODE_STATE
{
	NO_STATE = -1,
	EMPTY_STATE,
	BLOCKED_STATE,
	PLAYER_STATE,
	TARGET_STATE,
	PATH_STATE
};

class CNode : public CSprite
{
public:
	CNode(int, int, int, int);
	CNode() = default;
	~CNode();

	void Draw();
	void Process(float);

	bool UpdateNodeState(NODE_STATE);

	int GCost();
	int HCost();
	int FCost();

	void SetGCost(int);
	void SetHCost(int);

	int XCoord();
	int YCoord();

	bool NodeIsWalkable();

	CNode* m_previousNodeInPath;
	NODE_STATE CurrentNodeState();

private:
	NODE_STATE m_currentNodeState;
	int m_iXCoord;
	int m_iYCoord;

	int m_iGCost;
	int m_iHCost;

};