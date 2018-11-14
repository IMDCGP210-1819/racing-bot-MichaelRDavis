#pragma once

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

class robotFSM;

class robot
{
public:
	robot(int index, tCarElt* car, tSituation *s);
	~robot();

	void run();

	void driveRobot();
	bool isStuck();
	bool canDrive();

private:
	robotFSM* robotAI;
	int m_index;
	tCarElt* m_car;
	tSituation* m_situation;
	float angle;
	const float SC = 1.0f;
};