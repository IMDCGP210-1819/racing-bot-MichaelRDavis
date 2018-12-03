#include "../robot_base_davis/robot.h"
#include "../robot_base_davis/robot_behavior.h"

Robot::Robot(int index, tCarElt* car, tSituation *s)
	: m_index(index)
	, m_car(car)
	, m_situation(m_situation)
{
	m_robotAI = new robotFSM(this);
	m_stuckCount = 0;
}

Robot::~Robot()
{
	delete m_robotAI;
}

void Robot::run()
{
	if (m_robotAI != nullptr)
	{
		m_robotAI->update();
	}
}

void Robot::driveRobot()
{
	m_angle = RtTrackSideTgAngleL(&(m_car->_trkPos)) - m_car->_yaw;
	NORM_PI_PI(m_angle);
	m_angle -= m_SteeringControl * m_car->_trkPos.toMiddle / m_car->_trkPos.seg->width;

	m_car->_steerCmd = m_angle / m_car->_steerLock;
	m_car->ctrl.gear = 1;
	m_car->ctrl.brakeCmd = 0.0;
	m_car->ctrl.accelCmd = 0.3f;
}

void Robot::reverseRobot()
{
	m_angle = -RtTrackSideTgAngleL(&(m_car->_trkPos)) - m_car->_yaw;
	NORM_PI_PI(m_angle);

	m_car->_steerCmd = m_angle / m_car->_steerLock;
	m_car->ctrl.gear = -1;
	m_car->ctrl.brakeCmd = 0.0;
	m_car->ctrl.accelCmd = 0.3f;
}

void Robot::accelRobot()
{
	float accelSpeed = getTrackSpeed(m_car->_trkPos.seg);
	float gearRatio = m_car->_gearRatio[m_car->_gear + m_car->_gearOffset];
	float revs = m_car->priv.enginerpmRedLine;
	if (accelSpeed > m_car->_speed_x + 1.0f)
	{
		m_car->ctrl.accelCmd = 1.0f;
	}
	else
	{
		float result = accelSpeed / m_car->_wheelRadius(REAR_RGT) * gearRatio / revs;
		m_car->ctrl.accelCmd = result;
	}
}

void Robot::deAccelRobot()
{

}

int Robot::shiftGear()
{
	if (m_car->ctrl.gear <= 0)
	{
		return 1;
	}

	float gearUp = m_car->priv.gearRatio[m_car->ctrl.gear + m_car->priv.gearOffset];
	float gearConstraint = m_car->priv.enginerpmRedLine / gearUp;
	float wheelRadius = m_car->_wheelRadius(2);
	if (gearConstraint * wheelRadius * m_GearShift < m_car->_speed_x)
	{
		return m_car->_gear + 1;
	}
	else
	{
		float gearDown = m_car->priv.gearRatio[m_car->priv.gear + m_car->priv.gearOffset - 1];
		gearConstraint = m_car->priv.enginerpmRedLine / gearDown;
		if (m_car->priv.gear > 1 && gearConstraint * wheelRadius * m_GearShift > m_car->_speed_x + m_GearShiftMargin)
		{
			return m_car->_gear - 1;
		}

		return m_car->_gear;
	}
}

void Robot::brakeRobot()
{

}

void Robot::avoidance()
{

}

bool Robot::isStuck()
{
	m_angle = RtTrackSideTgAngleL(&(m_car->_trkPos)) - m_car->_yaw;
	NORM_PI_PI(m_angle);
	if (fabs(m_angle) < 30.0f / 180.0f * PI)
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

bool Robot::canDrive()
{
	if (isStuck())
	{
		return false;
	}

	if (canAccel())
	{
		return false;
	}

	return true;
}

bool Robot::canAccel()
{
	if (m_car->priv.enginerpmRedLine)
		return true;
	return false;
}

bool Robot::canShiftGear()
{
	if (canAccel())
		return true;
	return false;
}

bool Robot::canBrake()
{
	return true;
}

bool Robot::lowFuel()
{
	return true;
}

bool Robot::repair()
{
	return true;
}

float Robot::getTrackSpeed(trackSeg* segment)
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

float Robot::getSegmentEndDistance()
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
