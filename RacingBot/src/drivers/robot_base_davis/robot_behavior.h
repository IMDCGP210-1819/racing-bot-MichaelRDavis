#pragma once

class Robot;

/** Robot states */
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

/** Controls the behavioral states of the robot car. */
class robotFSM
{
public:
	/** RobotFSM constructor. */
	robotFSM(Robot* owner);

	/** RobotFSM destructor. */
	~robotFSM();

	/** Update robot states, called once per frame. */
	void update();

	/** Change robot state to a new state. */
	void setState(eRobotState newState);

	/** Get the current state of the state machine. */
	eRobotState getCurrentState() const;

private:
	/** Owner of the state machine. */
	Robot* m_owner;

	/** Current state of the state machine. */
	eRobotState m_currentState;
};