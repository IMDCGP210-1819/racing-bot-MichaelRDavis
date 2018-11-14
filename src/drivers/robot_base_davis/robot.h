#pragma once

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

class robotFSM;

/* Robot handles driving commands for the car */
class robot
{
public:
	/* Robot constructor */
	robot(int index, tCarElt* car, tSituation *s);
	~robot();

	void run();

	void driveRobotForward();
	void driveRobotBackward();
	void accelRobot();
	void deAccelRobot();

	void avoidance();

	bool isStuck();
	bool canDrive();

	float getSpeed(trackSeg* segment);

private:
	robotFSM* robotAI;
	tCarElt* m_car;
	tSituation* m_situation;
	const float SC = 1.0f;
	float angle;
	int m_index;
	int m_stuckCount;
};