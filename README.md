# SemanticSegmentation

export LC_NUMERIC="C"



```
mkdir build
cd build
cmake ..
make publisher subscriber
ign gazebo sensor_launch.ign
```



To-do
introduce LiDAR
visualize LiDAR on camera segmentation
create node to automatically add & segment all the stairs
save segmented image and lidar points
combine pixel with point from pcl


create semantic pcl node for IGN?