#pragma once

class robot;

enum eRobotState
{
	eStart,
	eForward,
	eReverse,
	eAccel,
	eDeaccel,
	eLowFuel,
	eDamage,
	eStop
};

class robotFSM
{
public:
	robotFSM(robot* owner);
	~robotFSM();

	void update();
	void setState(eRobotState newState);

	eRobotState getCurrentState() const;

private:
	robot* m_owner;
	eRobotState currentState;
};