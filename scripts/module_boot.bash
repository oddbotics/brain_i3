#!/bin/bash
source /opt/ros/indigo/setup.bash
source /home/oddbot/catkin_ws/devel/setup.bash
export ROS_MASTER_URI=http://oddbot:11311
export ROS_HOSTNAME=oddbot


roslaunch brain_i3 module.launch 
