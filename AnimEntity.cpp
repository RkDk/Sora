#include "AnimEntity.h"

void CAnimEntity::Update()
{

    bool bSpriteThink = true;

    if( m_AnimType & ANIMTYPE_KILLONEND )
    {

        if( m_Sprite.IsOnLastFrame() )
        {

            m_bKillMe = true;
            bSpriteThink = false;

        }

    }

    if( bSpriteThink )
        m_Sprite.Think();

}

void CAnimEntity::Draw()
{

    BaseDraw();

}

