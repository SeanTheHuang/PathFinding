//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: framecounter.h
// Description	: defintion of framecounter class
// Author		: Sean Huang
// Mail			: sean.hua7281@mediadesign.school.nz
//

#pragma once

#ifndef _FPSCOUNTER_H_
#define _FPSCOUNTER_H_

// Library Includes
#include <Windows.h>
#include <string>

// Local Includes


// Types

// Constants

// Prototypes

class CFPSCounter
{
	//Member Functions
public:
	CFPSCounter();
	~CFPSCounter();

	void CountFramesPerSecond(float _fDeltaTime);
	bool Initialise();

	void UpdateFPSText();
	void DrawFPSText(HDC _hdc, int _iWidth, int _iHeight);

protected:

private:

	//Member Variables
public:

protected:

private:
	int m_iFrameCount;
	float m_fTimeElapsed;
	float m_fFrameRate;
	std::wstring m_strFPS;
};


#endif // 
