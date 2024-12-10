#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) : 
		base1  (101, 584, "base.bmp",   CColor::Blue(), 0),
		spring1(116, 450, "spring.bmp", CColor::Blue(), 0),
		base2  (400, 584, "base.bmp",   CColor::Blue(), 0),
		spring2(400, 434, "spring.bmp", CColor::Blue(), 0),
		marker (400, 300, "marker.bmp", CColor::Blue(), 0)
{
	k1 = k2 = 1;
	spring1.SetPivot(116, 584);
	spring1.Rotate(-90);
	spring2.SetPivot(400, 568);
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	// user input
	if (IsKeyDown(SDLK_DOWN))	{ marker.SetVelocity(marker.GetVelocity().m_x, 0); marker.Move(0, -1); }
	else
	if (IsKeyDown(SDLK_UP))		{ marker.SetVelocity(marker.GetVelocity().m_x, 0); marker.Move(0, 1); }
	else
	if (IsKeyDown(SDLK_LEFT))	{ marker.SetVelocity(0, marker.GetVelocity().m_y); marker.Move(-1, 0); }
	else
	if (IsKeyDown(SDLK_RIGHT))	{ marker.SetVelocity(0, marker.GetVelocity().m_y); marker.Move(1, 0); }
	{
		// Implementation of the Hooke's Law - for the spring 1
		float x = marker.GetX() - 400;
		marker.Accelerate(-k1 * x, 0);

		// Implementation of the Hooke's Law - for the spring 2
		float y = marker.GetY() - 300;
		marker.Accelerate(0, -k2 * y);
	}
	marker.Update(t);

	// animate the spring1
	spring1.SetSize(32, marker.GetX() - 400 + 268);
	base2.SetX(marker.GetX());
	spring2.SetX(marker.GetX());

	// animate the spring2
	spring2.SetSize(32, 600-32-marker.GetY());

	// create trace
	trace.push_back(new CSpriteOval(marker.GetLeft(), marker.GetY(), 3, CColor::Red(192), t));

	if (trace.size() > 2000)
		trace.pop_front();
}

void CMyGame::OnDraw(CGraphics* g)
{
	*g << font(14) << top;
//	*g << "Spring coefficient k = " << k << endl;
//	*g << "Damp coefficient   d = " << d << endl;
	*g << bottom;
	*g << "K / D / Shift to modify coefficients" << endl;
	*g << "UP and DOWN arrows to move the spring" << endl;
	
	for each (CSprite *pSprite in trace)
		pSprite->Draw(g);
	base1.Draw(g);
	spring1.Draw(g);
	base2.Draw(g);
	spring2.Draw(g);
	marker.Draw(g);
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	StartGame();	// this allows to start the game immediately
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();

	if (sym == SDLK_k && (mod & KMOD_SHIFT) == 0)
		k1 += 0.1f;
	if (sym == SDLK_k && (mod & KMOD_SHIFT) != 0)
		k1 -= 0.1f;

	if (sym == SDLK_ESCAPE)
		trace.clear();

}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
