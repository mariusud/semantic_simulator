#include <cstdint>
#include <ignition/msgs.hh>
// #include <ignition/rendering.hh>
#include <ignition/transport.hh>
void OnNewLabelMap(const ignition::msgs::Image &_msg)
{
  auto width = _msg.width();
  auto height = _msg.height();
  auto buffer = _msg.data();
  for (uint32_t i = 0; i < height; ++i)
  {
    for (uint32_t j = 0; j < width; ++j)
    {
      auto index = (i * width + j) * 3;
      // label id of the pixel is in the last channel
      auto label = buffer[index + 2];

      std::cout << "label " << label <<std::endl;
      // In case of semantic segmentation, instance count is ignored.
      //
      // For panoptic segmentation, we can get the instance count as follows:
      // 16 bit value for instance count
      auto instanceCount1 = buffer[index + 1];
      auto instanceCount2 = buffer[index];
      // get the 16-bit decimal value from the two 8-bit values by left-shifting
      // instanceCount1 by 8 bits
      auto instanceCount = instanceCount1 * 256 + instanceCount2;
    }
  }
}

int main(int argc, char **argv)
{
  ignition::transport::Node node;
  if (!node.Subscribe("/segmentation/colored_map", &OnNewLabelMap))
  {
    std::cerr << "Error subscribing to the boundingbox camera topic"
              << std::endl;
    return -1;
  }
  ignition::transport::waitForShutdown();
  return 0;
}