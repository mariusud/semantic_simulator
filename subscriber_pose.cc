#include <google/protobuf/message.h>
#include <iostream>
#include <string>
#include <ignition/transport.hh>
#include <csignal>
#include <random>
#include <ignition/msgs/twist.pb.h>
#include <ignition/msgs/laserscan.pb.h>

static std::atomic<bool> g_terminatePub(false);
std::string topic_pub = "/cmd_vel";
ignition::transport::Node node3;
auto pub = node3.Advertise<ignition::msgs::Twist>(topic_pub);
extern int sleeper = 0;
extern double x = 0;
extern double y = 0; 

void signal_handler(int _signal)
{
  if (_signal == SIGINT || _signal == SIGTERM)
    g_terminatePub = true;
}

bool check_pose(double x, double y)
{
  if (x > 20 || x < -20 || y > 20 || y < -20){
    return false;
    std::cout << "checkpose" << x << y;
  }
  else {
    return true;
  }
}

double random_gen(){
    return (double)rand() / RAND_MAX; // for generating random points between 0 to 1
}
double get_random(double min, double max) {
  return min + (max-min)*random_gen();
}

void random_walk_callback(const ignition::msgs::LaserScan &_msg)
{
  std::cout << "checkpose" << x << y;

  ignition::msgs::Twist data;
  bool allMore = true;
  for (int i = 0; i < _msg.ranges_size(); i++)
  {
    if (_msg.ranges(i) > 1.0 && !std::isinf(_msg.ranges(i))) // check for inf
    {
      std::cout << _msg.ranges(i);
      allMore = false;
      break;
    }
  }
  if (!check_pose(x,y) ) 
  {
    if (x > 20.0) {
      data.mutable_linear()->set_x(-2);
      data.mutable_angular()->set_z(0.0);
    }
    else if (x < -20.0) {
      data.mutable_linear()->set_x(2);
      data.mutable_angular()->set_z(0.0);
    }
    else if (y > 20.0) {
      data.mutable_linear()->set_x(-2);
      data.mutable_angular()->set_z(1.57);
    }
    else if (y < -20.0) {
      data.mutable_linear()->set_x(2);
      data.mutable_angular()->set_z(1.57);
    }
    else 
    {
      std::cerr << "failed to deliver pose"  << " x " << x << " y " << y << std::endl;
    }
    sleeper = 5000;
    std::cout << "failed pose, setting -1,0"  << " x " << x << " y " << y << std::endl;
 
  }
  else if (allMore && check_pose(x,y) ) //if sufficiently far away from everything and not outside area, do normal stuff
  {
    data.mutable_linear()->set_x(3.0);
    data.mutable_angular()->set_z(get_random(-0.5,0.5));
    sleeper = 3000;
  }

  else // if too close, but not outside of area, move out the way
  {
    data.mutable_linear()->set_x(-0.2);
    data.mutable_angular()->set_z(get_random(0,1));
    sleeper = 3000;
  }
  pub.Publish(data);
  std::this_thread::sleep_for(std::chrono::milliseconds(sleeper));
}

void cb(const ignition::msgs::Pose_V &_msg,
        const ignition::transport::MessageInfo &_info)
{
  ignition::msgs::Pose pose = _msg.pose(9);
  // std::cout << "Topic: [" << _msg.pose(9).name() << "]" << std::endl;
  x =  pose.position().x();
  y =  pose.position().y();
}

int main(int argc, char **argv)
{
  std::signal(SIGINT,  signal_handler);
  std::signal(SIGTERM, signal_handler);
  // Create a transport node and advertise a topic.
  ignition::transport::Node node;
  ignition::transport::Node node2;
  std::string topic = "/model/vehicle_blue/pose";
  std::string topic_lidar = "/gpu_lidar_collision_avoidance";   // subscribe to this topic
  if (!pub)
  {
    std::cerr << "Error advertising topic [" << topic << "]" << std::endl;
    return -1;
  } 
  if (!node.Subscribe(topic_lidar, random_walk_callback))
  {
    std::cerr << "Error subscribing to topic [" << topic_lidar << "]" << std::endl;
    return -1;
  }
  if (!node2.Subscribe(topic, cb))
  {
    std::cerr << "Error subscribing to topic [" << topic << "]" << std::endl;
    return -1;
  }
  ignition::transport::waitForShutdown();

  return 0;
}

