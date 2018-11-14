#pragma once

class robot;

enum eRobotState
{
	eStart,
	eForward,
	eReverse,
	eAccel,
	eDeaccel,
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
	eRobotState currentState;
	robot* m_owner;
};