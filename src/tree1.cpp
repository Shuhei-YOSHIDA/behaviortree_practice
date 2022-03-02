/**
 * @file tree1.cpp
 */

#include "behaviortree_practice/node1.h"

using namespace BT;

// clang-format off
static const char* xml_text = R"(
 <root main_tree_to_execute = "MainTree" >
     <BehaviorTree ID="MainTree">
        <Sequence name="root_sequence">
            <CheckBattery   name="battery_ok"/>
            <OpenGripper    name="open_gripper"/>
            <ApproachObject name="approach_object"/>
            <CloseGripper   name="close_gripper"/>
        </Sequence>
     </BehaviorTree>
 </root>
 )";

// clang-format on

int main(int argc, char** argv)
{
  BehaviorTreeFactory factory;

//#ifdef MANUAL_STATIC_LINKING

  using namespace DummyNodes1;

  factory.registerNodeType<ApproachObject>("ApproachObject");

  factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));

  GripperInterface gripper;
  factory.registerSimpleAction("OpenGripper", std::bind(&GripperInterface::open, &gripper));
  factory.registerSimpleAction("CloseGripper", std::bind(&GripperInterface::close, &gripper));

//#else
//  factory.registerFromPlugin("./libdummy_nodes_dyn.so");
//#endif

  auto tree = factory.createTreeFromText(xml_text);

  tree.tickRoot();

  return 0;
}

