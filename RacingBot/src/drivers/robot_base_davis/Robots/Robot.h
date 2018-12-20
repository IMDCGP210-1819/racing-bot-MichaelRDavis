#pragma once

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

#include <memory>

class BehaviorTree;

/**
 * This class is responsible for handling the cars driving behavior.
 */
class Robot
{
public:
	/** Default Robot constructor. */
	Robot();

	/** Default Robot destructor. */
	virtual ~Robot();

	/** Create BehviorTree. */
	void CreateBehaviorTree();
	
	/** Initialize robot car. */
	void Initialize(tCarElt* Car);

	/** Update robot car, ideally called once per frame. */
	void Update();

	/** Drive robot car forward. */
	void Drive();

	/** Check to see if the robot car is stuck. */
	bool IsStuck() const;

	/** Check to see if the car can drive. */
	bool CanDrive() const;

protected:
	/** Robot BehaviorTree. */
	std::unique_ptr<BehaviorTree> m_BehaviorTree;

	/** Pointer to the car structure. */
	tCarElt* m_Car;

	/* Robot car properties */
	float m_AngleToTrack;
	static int m_StuckCount;
	const float STEERING_CONTROL = 1.0f;
	const float MAX_UNSTUCK_SPEED = 5.0f;
	const float MIN_UNSTUCK_DIST = 3.0f;
	const float MAX_UNSTUCK_ANGLE = 30.0f;
	const int MAX_UNSTUCK_COUNT = 100;
};