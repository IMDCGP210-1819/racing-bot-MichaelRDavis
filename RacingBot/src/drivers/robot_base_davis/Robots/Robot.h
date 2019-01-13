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
 * This class is responsible for handling the robot cars driving behavior.
 */
class Robot
{
public:
	/** Default Robot constructor. */
	Robot();

	/** Robot constructor that sets the robot car index. */
	Robot(int Index);

	/** Default Robot destructor. */
	virtual ~Robot();

	/** TORCS callback functions. */
	void InitTrack(tTrack* Track, void* CarHandle, void** CarParamHandle, tSituation* Situation);
	void NewRace(tCarElt* Car, tSituation* Situation);
	void Drive(tCarElt* Car, tSituation* Situation);
	int PitCommand(tCarElt* Car, tSituation* Situation);
	void EndRace(tCarElt* Car, tSituation* Situation);
	
	/** Create the robot car Blackboard. */
	void CreateBlackboard();

	/** Create the robot car BehaviorTree. */
	void CreateBehaviorTree();

	/** Update robot car BehvaiorTree, called once per frame. */
	void UpdateBehaviorTree();

	/** Drive the robot car forward. */
	void OnDrive();

	/** Reverse the robot car backwards. */
	void OnReverse();

	/** Update robot car, called once per frame. */
	void Update(tCarElt* Car, tSituation* Situation);

	/** Get the allowed speed on the current track segment. */
	float GetTrackSegmentSpeed(tTrackSeg* Segment);

	/** Get the distance to the end of the current track segment. */
	float GetTrackSegmentEndDistance(tCarElt* Car);

	/** Calculate acceleration. */
	float GetAcceleration(tCarElt* Car);

	/** Calculate braking */
	float GetBraking(tCarElt* Car);

	/** Calculate the current gear */
	int GetGear(tCarElt* Car);

	/** Calculate the aerodynamic downforce coefficient. */
	void CalculateDownforce();

	/** Calculate the aerodynamic drag coefficient. */
	void CalculateDrag();

	/** Check to see if the robot car is stuck. */
	bool IsStuck() const;

	/** Check to see if the robot car can drive. */
	bool CanDrive() const;

	/** RobotTasks can access Robots private members. */
	friend class DriveTask;
	friend class ReverseTask;
	friend class AccelerateTask;
	friend class BrakeTask;
	friend class ShiftGearTask;
	friend class SteerTask;

private:
	/** Robot BehaviorTree. */
	std::unique_ptr<BehaviorTree> m_BehaviorTree;

	/** Pointer to the car structure. */
	tCarElt* m_Car;

	/** Pointer to the track the robot car is currently driving on. */
	tTrack* m_Track;

	/** Current robot car acceleration */
	tdble m_Acceleration;

	/** Current robot car braking */
	tdble m_Brake;

	/** Current robot car gear */
	int m_Gear;

	/** Mass of the robot car, including the fuel. */
	float m_Mass;

	/** Mass of the robot car chassis only. */
	float m_BodyMass;

	/** The aerodynamic downforce coefficient of the robot car. */
	float m_Downforce;

	/** The aerodynamic drag coefficient of the robot car. */
	float m_DragForce;

	/* Robot car properties */
	float m_TrackAngle;
	float m_CarAngle;
	int m_Index;
	int m_MaxStuckCount;
	static int m_StuckCount;
	static const float MAX_UNSTUCK_ANGLE;
	static const float UNSTUCK_TIME_LIMIT;
	static const float SHIFT;
	static const float SHIFT_MARGIN;
	const float GRAVITY_SCALE;
	const float FULL_ACCELERATION;
	const float STEERING_CONTROL;
	const float MAX_UNSTUCK_SPEED;
	const float MIN_UNSTUCK_DIST;
	const int MAX_UNSTUCK_COUNT;
};