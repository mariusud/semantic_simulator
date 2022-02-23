#include <google/protobuf/message.h>
#include <iostream>
#include <string>
#include <ignition/transport.hh>


void cb(const google::protobuf::Message &_msg,
        const ignition::transport::MessageInfo &_info)
{
  std::cout << "Topic: [" << _info.Type() << "]" << std::endl;
  // std::cout << _msg.DebugString() << std::endl;
}
int main(int argc, char **argv)
{
  std::signal(SIGINT,  signal_handler);
  std::signal(SIGTERM, signal_handler);
  // Create a transport node and advertise a topic.
  ignition::transport::Node node;
  ignition::transport::Node node2;
  std::string topic = "/world/segmentation_world/dynamic_pose/info";
  // Subscribe to a topic by registering a callback.
  if (!node2.Subscribe(topic, cb))
  {
    std::cerr << "Error subscribing to topic [" << topic << "]" << std::endl;
    return -1;
  }
  std::string topic = "/camera_pose";
  auto pub = node.Advertise<ignition::msgs::StringMsg>(topic);
  if (!pub)
  {
    std::cerr << "Error advertising topic [" << topic << "]" << std::endl;
    return -1;
  }
  // Prepare the message.
  ignition::msgs::StringMsg msg;
  msg.set_data("HELLO");

  // Publish messages at 1Hz.
  while (!g_terminatePub)
  {
    if (!pub.Publish(msg))
      break;
    std::cout << "Publishing hello on topic [" << topic << "]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return 0;
}
