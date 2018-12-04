#include "../robot_base_davis/Robot.h"
#include "../robot_base_davis/BehaviorTree/BehaviorTree.h"
#include "../robot_base_davis/BTCompositeSelector.h"
#include "../robot_base_davis/DriveTask.h"

Robot::Robot()
{
	m_BehaviorTree = std::make_unique<BehaviorTree>();
}

Robot::~Robot()
{

}

void Robot::CreateBehaviorTree()
{
	auto sequence = std::make_shared<BTCompositeSelector>();
	sequence->InsertChildNode(std::make_shared<DriveTask>(this));
	m_BehaviorTree->SetRootNode(sequence);
}

void Robot::Initialize(tCarElt* Car)
{
	m_Car = Car;
}

void Robot::Update()
{
	m_BehaviorTree->Update();
}

void Robot::Drive()
{
	m_AngleToTrack = RtTrackSideTgAngleL(&(m_Car->_trkPos)) - m_Car->_yaw;
	NORM_PI_PI(m_AngleToTrack);
	m_AngleToTrack -= STEERING_CONTROL * m_Car->_trkPos.toMiddle / m_Car->_trkPos.seg->width;

	m_Car->ctrl.steer = m_AngleToTrack / m_Car->_steerLock;
	m_Car->ctrl.gear = 1;
	m_Car->ctrl.accelCmd = 0.3f;
	m_Car->ctrl.brakeCmd = 0.0f;
}
