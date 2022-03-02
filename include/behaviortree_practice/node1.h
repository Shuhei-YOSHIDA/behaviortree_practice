/**
 * @file node1.h
 */

#ifndef INCLUDE_BEHAVIORTREE_PRACTICE_NODE_1_H
#define INCLUDE_BEHAVIORTREE_PRACTICE_NODE_1_H

#include <behaviortree_cpp_v3/behavior_tree.h>
#include <behaviortree_cpp_v3/bt_factory.h>

namespace DummyNodes1
{

BT::NodeStatus CheckBattery();

BT::NodeStatus CheckTemperature();
BT::NodeStatus SayHello();

class GripperInterface
{
public:
  GripperInterface() : _opened(true)
  {
  }

  BT::NodeStatus open();

  BT::NodeStatus close();

private:
  bool _opened;
};

class ApproachObject : public BT::SyncActionNode
{
public:
  ApproachObject(const std::string& name) :
    BT::SyncActionNode(name, {})
  {
  }

  BT::NodeStatus tick() override;
};

class SaySomething : public BT::SyncActionNode
{
public:
  SaySomething(const std::string& name, const BT::NodeConfiguration& config)
    : BT::SyncActionNode(name, config)
  {
  }

  BT::NodeStatus tick() override;

  static BT::PortsList providedPorts()
  {
    return{ BT::InputPort<std::string>("message") };
  }
};


BT::NodeStatus SaySomethingSimple(BT::TreeNode& self);


inline void RegisterNodes(BT::BehaviorTreeFactory& factory)
{
  static GripperInterface grip_singleton;

  factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));
  factory.registerSimpleCondition("CheckTemperature", std::bind(CheckTemperature));
  factory.registerSimpleAction("SayHello", std::bind(SayHello));
  factory.registerSimpleAction("OpenGripper", std::bind(&GripperInterface::open, &grip_singleton));
  factory.registerSimpleAction("CloseGripper", std::bind(&GripperInterface::close, &grip_singleton));
  factory.registerNodeType<ApproachObject>("ApproachObject");
  factory.registerNodeType<SaySomething>("SaySomething");
}

} // namespace DummyNode1

#endif /* ifndef INCLUDE_BEHAVIORTREE_PRACTICE_NODE_1_H */
