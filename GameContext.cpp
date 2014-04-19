#include "GameContext.h"

void CGameContext::BeginFrame()
{

	m_BeginFrameTime = SDL_GetTicks();

}

void CGameContext::EndFrame()
{

	m_FrameDelta = ( SDL_GetTicks() - m_BeginFrameTime ) * .001f;

}