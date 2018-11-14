#include "../robot_base_davis/robot.h"
#include "../robot_base_davis/robot_behavior.h"

robot::robot(int index, tCarElt* car, tSituation *s)
	: m_index(index)
	, m_car(car)
	, m_situation(m_situation)
{
	robotAI = new robotFSM(this);
}

robot::~robot()
{
	delete robotAI;
}

void robot::run()
{
	if (robotAI != nullptr)
	{
		robotAI->update();
	}
}

void robot::driveRobotForward()
{
	angle = RtTrackSideTgAngleL(&(m_car->_trkPos)) - m_car->_yaw;
	NORM_PI_PI(angle);
	angle -= SC * m_car->_trkPos.toMiddle / m_car->_trkPos.seg->width;

	m_car->_steerCmd = angle / m_car->_steerLock;
	m_car->ctrl.gear = 1;
	m_car->ctrl.brakeCmd = 0.0;
	m_car->ctrl.accelCmd = 0.8f;
}

void robot::driveRobotBackward()
{
	angle = -RtTrackSideTgAngleL(&(m_car->_trkPos)) - m_car->_yaw;
	NORM_PI_PI(angle);

	m_car->_steerCmd = angle / m_car->_steerLock;
	m_car->ctrl.gear = -1;
	m_car->ctrl.brakeCmd = 0.0;
	m_car->ctrl.accelCmd = 0.3f;
}

void robot::accelRobot()
{

}

void robot::deAccelRobot()
{

}

void robot::avoidance()
{

}

bool robot::isStuck()
{
	angle = RtTrackSideTgAngleL(&(m_car->_trkPos)) - m_car->_yaw;
	NORM_PI_PI(angle);
	if (fabs(angle) < 30.0f / 180.0f * PI)
	{
		m_stuckCount = 0;
		return false;
	}
	if (m_stuckCount < 100)
	{
		m_stuckCount++;
		return false;
	}
	else
	{
		return true;
	}
}

bool robot::canDrive()
{
	if (isStuck())
		return false;
	return true;
}

float robot::getSpeed(trackSeg* segment)
{
	return 0.0f;
}
