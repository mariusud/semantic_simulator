#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <thread>
#include <ignition/msgs.hh>
#include <ignition/transport.hh>
#include <stdlib.h>     /* srand, rand */
#include <random>
#include <iostream>

std::uniform_real_distribution<> uniform_distribution(-1.0, 2.0);

double get_random(double min, double max) {
  /* Returns a random double between min and max */
  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); 
  return uniform_distribution(gen);
}

static std::atomic<bool> g_terminatePub(false);
void signal_handler(int _signal)
{
  if (_signal == SIGINT || _signal == SIGTERM)
    g_terminatePub = true;
}
int main(int argc, char **argv)
{
  // Install a signal handler for SIGINT and SIGTERM.
  std::signal(SIGINT,  signal_handler);
  std::signal(SIGTERM, signal_handler);
  // Create a transport node and advertise a topic.
  ignition::transport::Node node;
  std::cout << "testing";
  std::string topic = "/cmd_vel";
  auto pub = node.Advertise<ignition::msgs::Twist>(topic);
  if (!pub)
  {
    std::cerr << "Error advertising topic [" << topic << "]" << std::endl;
    return -1;
  }
  // Prepare the message.
  ignition::msgs::Twist msg;
  ignition::msgs::Vector3d angularmsg;
  ignition::msgs::Vector3d linearmsg;
  
  
  msg.set_allocated_angular(&angularmsg);
  msg.set_allocated_linear(&linearmsg);

  // Publish messages at 10Hz.
  while (!g_terminatePub)
  {
    if (!pub.Publish(msg))
      break;
    std::cout << "Publishing on topic [" << topic << "]" << std::endl;
    angularmsg.set_z(get_random(-1,1));
    linearmsg.set_x(get_random(-1,1));

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }
  return 0;
}