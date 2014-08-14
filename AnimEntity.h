#ifndef ANIMENTITY_H_
#define ANIMENTITY_H_

#include "WorldEntity.h"

enum
{

    ANIMTYPE_ENDLESS = 0x00,
    ANIMTYPE_KILLONEND = 0x01

};

class CAnimEntity : public CWorldEntity
{

private:

    int m_AnimType;

public:

    CAnimEntity() : CWorldEntity(), m_AnimType( ANIMTYPE_ENDLESS )
    {


    }

    void SetAnimType( int i )
    {

        m_AnimType = i;

    }

    int GetAnimType()
    {

        return m_AnimType;

    }

    void Update();
    void Draw();

    virtual ~CAnimEntity() { }


};

#endif
