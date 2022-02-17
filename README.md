# SemanticSegmentation

## Build
```
mkdir build
cd build
cmake ..
make publisher subscriber
ign gazebo sensor_launch.ign
```
## Run
to launch ros bridge
```
roslaunch launch/segmentation.launch
```

## To-do
introduce LiDAR
visualize LiDAR on camera segmentation
create node to automatically add & segment all the stairs
save segmented image and lidar points
combine pixel with point from pcl


create semantic pcl node for IGN?


export IGNITION_VERSION=fortress

blender --background --python off2obj.py -- off_meshes/ obj_meshes/


## Dataset
Converted to DAE files using 
https://gist.github.com/mariusud/6d880a2809475e03db51ad909dcd0fc5

converted to sdf using xml_parser.py

unexpected behaviour on 
stairs_0064

## LiDAR
xacro
urdf
sdf



running distributed? 

--distributed or -g 

ign gazebo -s --network-role=primary --network-secondaries=1 --distributed shapes.sdf

add some color to the stairs

add bosdyn spot
https://app.ignitionrobotics.org/OpenRobotics/fuel/models/bosdyn_spot


tuesday
bosdyn
bridge over segmentation image
combine pixel with pcl
bpy.ops.wm.collada_export(filepath='/Users/dave/test.dae', check_existing=False, filter_blender=False, filter_image=False, filter_movie=False, filter_python=False, filter_font=False, filter_sound=False, filter_text=False, filter_btx=False, filter_collada=True, filter_folder=True, filemode=8)


          <material>
            <ambient>0.3 0.0 0.0 1</ambient>
            <diffuse>0.7 0.0 0.0 1</diffuse>
            <specular>0.5 0.5 0.5 1</specular>
          </material>




next:
projection camera-pcl
colorize pcl with label
save pcl as txt file with x,y,z,color 



            <sensor name='gpu_lidar' type='gpu_lidar'>
            <pose>0 0 0 0 0 0</pose>
              <topic>lidar</topic>
              <update_rate>10</update_rate>
              <lidar>
                <scan>
                  <horizontal>
                    <samples>640</samples>
                    <resolution>1</resolution>
                    <min_angle>-3.14159265359</min_angle>
                    <max_angle>3.14159265359</max_angle>
                  </horizontal>
                  <vertical>
                    <samples>640</samples>
                    <resolution>1</resolution>
                    <min_angle>-0.261799</min_angle>
                    <max_angle>0.261799</max_angle>
                  </vertical>
                </scan>
                <range>
                  <min>0.7</min>
                  <max>10.0</max>
                  <resolution>0.001</resolution>
                </range>
                <noise>
                  <type>gaussian</type>
                  <mean>0</mean>
                  <stddev>0.008</stddev>
                </noise>
              </lidar>
              <alwaysOn>1</alwaysOn>
              <visualize>true</visualize>
            </sensor>



projected_pts = [cameraModel.project3dToPixel(list(pt)+[1]) for pt in corners]

fix tf transform for projections