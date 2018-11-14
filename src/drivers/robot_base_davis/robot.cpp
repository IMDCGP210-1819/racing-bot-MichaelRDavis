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

void robot::driveRobot()
{
	angle = RtTrackSideTgAngleL(&(m_car->_trkPos)) - m_car->_yaw;
	NORM_PI_PI(angle);
	angle -= SC * m_car->_trkPos.toMiddle / m_car->_trkPos.seg->width;

	m_car->_steerCmd = angle / m_car->_steerLock;
	m_car->ctrl.gear = 1;
	m_car->ctrl.brakeCmd = 0.0;
	m_car->ctrl.accelCmd = 0.8f;
}

void robot::reverseRobot()
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
	float accelSpeed = getTrackSpeed(m_car->_trkPos.seg);
	float gearRatio = m_car->_gearRatio[m_car->_gear + m_car->_gearOffset];
	float revs = m_car->priv.enginerpmRedLine;
	if (accelSpeed > m_car->pub.DynGCg.vel.x + 1.0f)
	{
		m_car->ctrl.accelCmd = 1.0f;
	}
	else
	{
		float result = accelSpeed / m_car->_wheelRadius(REAR_RGT) * gearRatio / revs;
		m_car->ctrl.accelCmd = result;
	}
}

void robot::brakeRobot()
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
	if (isStuck() || canAccel())
		return false;
	return true;
}

bool robot::canAccel()
{
	if (m_car->priv.enginerpmRedLine > 0.9f)
		return true;

	return false;
}

float robot::getTrackSpeed(trackSeg* segment)
{
	if (segment->type == TR_STR)
	{
		return FLT_MAX;
	}
	else
	{
		float friction = segment->surface->kFriction;
		float speed = sqrt(friction * m_gravityScale * segment->radius);
		return speed;
	}
}

float robot::getSegmentEndDistance()
{
	if (m_car->_trkPos.seg->type == TR_STR)
	{
		return m_car->_trkPos.seg->length - m_car->_trkPos.toStart;
	}
	else
	{
		return 0.0f;
	}
}
