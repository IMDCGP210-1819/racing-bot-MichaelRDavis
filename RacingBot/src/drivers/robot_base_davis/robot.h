#pragma once

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

class robotFSM;

/* Robot handles driving commands for the car. */
class Robot
{
public:
	/* Robot constructor. */
	Robot(int index, tCarElt* car, tSituation *s);

	/** Robot destructor. */
	~Robot();

	/** Update the robot behavior, called once per frame. */
	void run();

	/** Drive robot car forward */
	void driveRobot();

	/** Drive robot cat backward */
	void reverseRobot();

	/** Accelerate robot car */
	void accelRobot();

	/** De-Accelerate robot car */
	void deAccelRobot();

	/** Change robot car gear */
	int shiftGear();

	/** Apply the robot cars brakes */
	void brakeRobot();

	/** Avoid any other robot cars. */
	void avoidance();

	/** Returns true if robot car is stuck upon a surface. */
	bool isStuck();

	/** Returns true if robot car can drive. */
	bool canDrive();

	/** Returns true if robot can accelerate. */
	bool canAccel();

	/** Returns true if can shift gear. */
	bool canShiftGear();

	/** Returns true if robot car can brake. */
	bool canBrake();

	/** Returns true if car is low on fuel */
	bool lowFuel();

	/** Returns true if car need repairing */
	bool repair();

	/** Returns the speed of a track segment. */
	float getTrackSpeed(trackSeg* segment);

	/** Retunrs the distance to the end the current track segment. */
	float getSegmentEndDistance();

private:
	/** Robot car AI behavior. */
	robotFSM* m_robotAI;

	/** Robot car. */
	tCarElt* m_car;

	/** Robot situation. */
	tSituation* m_situation;

	/** Robot car steering control. */
	const float m_SteeringControl = 1.0f;

	/** Robot car angle to track. */
	float m_angle;

	/** Robot car index. */
	int m_index;

	/** Robot car stuck count */
	int m_stuckCount;

	/* Robot cars current gear */
	int m_currentGear;

	/** Robot car gravity scale. */
	const float m_gravityScale = 9.807f;

	const float m_GearShift = 0.9f;
	const float m_GearShiftMargin = 4.0f;
};