#ifndef STATE_H_
#define STATE_H_

class CState
{

    bool m_bContinue;

public:

	virtual void Input() = 0;
	virtual void Think() = 0;
	virtual void Draw() = 0;

	virtual bool Continue() { return m_bContinue; }

	CState() : m_bContinue( true )
	{



	}

};

#endif
