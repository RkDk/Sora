#ifndef STATE_H_
#define STATE_H_

class CState
{

public:

	virtual void Input() = 0;
	virtual void Think() = 0;
	virtual void Draw() = 0;

};

#endif
