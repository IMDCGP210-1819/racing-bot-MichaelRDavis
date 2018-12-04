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

protected:
	/** Robot BehaviorTree. */
	std::unique_ptr<BehaviorTree> m_BehaviorTree;

	/** Pointer to the car structure. */
	tCarElt* m_Car;

	float m_AngleToTrack;
	const float STEERING_CONTROL = 1.0f;
};