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

	/** Robot constructor that sets the robot index. */
	Robot(int Index);

	/** Default Robot destructor. */
	virtual ~Robot();

	/** TORCS callback functions. */
	void InitTrack(tTrack* Track, void* CarHandle, void** CarParamHandle, tSituation* Situation);
	void NewRace(tCarElt* Car, tSituation* Situation);
	void Drive(tCarElt* Car, tSituation* Situation);
	int PitCommand(tCarElt* Car, tSituation* Situation);
	void EndRace(tCarElt* Car, tSituation* Situation);

	/** Create the robot BehaviorTree. */
	void CreateBehaviorTree();

	/** Update robot car BehvaiorTree, called once per frame. */
	void UpdateBehaviorTree();

	/** Drive robot car forward. */
	void OnDrive();

private:
	/** Update robot car, called once per frame. */
	void Update(tCarElt* Car, tSituation* Situation);

	/** Check to see if the robot car is stuck. */
	bool IsStuck() const;

	/** Check to see if the car can drive. */
	bool CanDrive() const;

	/** Robot BehaviorTree. */
	std::unique_ptr<BehaviorTree> m_BehaviorTree;

	/** Pointer to the car structure. */
	tCarElt* m_Car;

	/** Pointer to the track the robot car is currently is driving on. */
	tTrack* m_Track;

	/* Robot car properties */
	float m_TrackAngle;
	float m_CarAngle;
	int m_Index;
	int m_MaxStuckCount;
	static int m_StuckCount;
	static const float MAX_UNSTUCK_ANGLE;
	static const float UNSTUCK_TIME_LIMIT;
	const float STEERING_CONTROL;
	const float MAX_UNSTUCK_SPEED;
	const float MIN_UNSTUCK_DIST;
	const int MAX_UNSTUCK_COUNT;
};