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
	CNode(int, int);
	CNode() = default;
	~CNode();

	void Draw();
	void Process(float);

	bool UpdateNodeState(NODE_STATE);



private:
	NODE_STATE m_currentNodeState;

};