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
 * Robot is responsible for handling the robot cars driving behavior.
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

	// TORCS callback functions
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
	void Update();

	/** Get the allowed speed on the current track segment. */
	float GetTrackSegmentSpeed(tTrackSeg* Segment);

	/** Get the distance to the end of the current track segment. */
	float GetTrackSegmentEndDistance();

	/** Calculate acceleration. */
	float GetAcceleration();

	/** Calculate braking */
	float GetBraking();

	/** Calculate the steering angle. */
	float GetSteering();

	/** Calculate the current gear */
	int GetGear();

	/** Get the anti-lock breaking system for the brakes. */
	float GetABS(float brake);

	/** Get the traction control for the accelerator. */
	float GetTractionControl(float accel);

	/** Initialize the traction control setup for the car. */
	void InitTractionControl();

	/** Get traction control on the rear wheels. */
	float TCLRearWheelDrive();

	/** Get traction on the front wheels. */
	float TCLFrontWheelDrive();

	/** Get the traction control on all four wheels. */
	float TCLFourWheelDrive();

	/** Calculate the aerodynamic down force coefficient. */
	void CalculateDownForce();

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

	/** Pointer the the current situation. */
	tSituation* m_Situation;

	/** Current robot car acceleration */
	tdble m_Acceleration;

	/** Current robot car braking */
	tdble m_Brake;

	/** Current robot car gear */
	int m_Gear;

	/** Current steer angle. */
	tdble m_SteerAngle;

	/** Mass of the robot car, including the fuel. */
	float m_Mass;

	/** Mass of the robot car chassis only. */
	float m_BodyMass;

	/** The aerodynamic down force coefficient of the robot car. */
	float m_DownForce;

	/** The aerodynamic drag coefficient of the robot car. */
	float m_DragForce;

	/** Angle of the track. */
	float m_TrackAngle;

	/** Angle of the car to the track. */
	float m_CarAngle;

	/** Car index. */
	int m_Index;

	/** Max stuck count. */
	int m_MaxStuckCount;

	/** Current stuck count. */
	static int m_StuckCount;

	/** Function pointer to the wheel speed. */
	float (Robot::*GET_DRIVEN_WHEEL_SPEED)();

	// Robot car properties.
	static const float MAX_UNSTUCK_ANGLE;
	static const float UNSTUCK_TIME_LIMIT;
	static const float SHIFT;
	static const float SHIFT_MARGIN;
	static const float ABS_SLIP;
	static const float ABS_MINSPEED;
	static const float TCL_SLIP;
	static const float TCL_MINSPEED;
	const float GRAVITY_SCALE;
	const float FULL_ACCELERATION;
	const float STEERING_CONTROL;
	const float MAX_UNSTUCK_SPEED;
	const float MIN_UNSTUCK_DIST;
};