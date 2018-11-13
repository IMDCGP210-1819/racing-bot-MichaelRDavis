#pragma once

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

/* List of robot behaviors */
enum ERobotBehavior
{
	EDrive,
	EStuck,
};

/* Robot final state machine */
class RobotFSM
{
public:
	/* Robot constructor */
	RobotFSM()
	{
		currentState = ERobotBehavior::EDrive;
	}

	/* Robot destructor */
	~RobotFSM()
	{

	}

	/* Calculate the robots behavior */
	void calculate(int index, tCarElt* car, tSituation *s)
	{
		if (currentState == ERobotBehavior::EDrive)
		{
			float angle;
			const float SC = 1.0f;
			angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
			NORM_PI_PI(angle);
			angle -= SC * car->_trkPos.toMiddle / car->_trkPos.seg->width;

			car->_steerCmd = angle / car->_steerLock;
			car->ctrl.gear = 1;
			car->ctrl.brakeCmd = 0.0;
			car->ctrl.accelCmd = 0.5f;
		}
		else if (currentState == ERobotBehavior::EStuck)
		{

		}
	}

	/* Set the behavior of the robot */
	void setState(ERobotBehavior newState)
	{
		currentState = newState;
	}

	/* Get the current state of robots behavior */
	ERobotBehavior getCurrentState()
	{
		return currentState;
	}

private:
	/* Current state of robots behavior */
	ERobotBehavior currentState;
};