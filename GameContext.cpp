#include "GameContext.h"

	void CGameContextBase::BeginFrame()
	{

		m_BeginFrameTime = SDL_GetTicks();

	}

	void CGameContextBase::EndFrame()
	{

		m_FrameDelta = ( SDL_GetTicks() - m_BeginFrameTime ) * .001f;

	}
