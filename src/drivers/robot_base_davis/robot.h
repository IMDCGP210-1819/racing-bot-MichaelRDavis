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

	void driveRobot();
	void reverseRobot();
	void accelRobot();
	void brakeRobot();

	/** Avoid any other robot cars. */
	void avoidance();

	/** Retunrs true if robot car is stuck upon a surface. */
	bool isStuck();

	/** Returns true if robot car can drive. */
	bool canDrive();

	/** Returns true if robot can accelerate. */
	bool canAccel();

	/** Returns the speed of a track segment. */
	float getTrackSpeed(trackSeg* segment);

	/** Retunrs the distance to the end the current track segment. */
	float getSegmentEndDistance();

private:
	/** Robot car AI behavior. */
	robotFSM* robotAI;

	/** Robot car. */
	tCarElt* m_car;

	/** Robot situation. */
	tSituation* m_situation;

	/** Robot car steering control. */
	const float SC = 1.0f;

	/** Robot car angle to track. */
	float angle;

	/** Robot car index. */
	int m_index;

	/** Robot car stuck count */
	int m_stuckCount;

	/** Robot car gravity scale. */
	const float m_gravityScale = 9.807f;
};