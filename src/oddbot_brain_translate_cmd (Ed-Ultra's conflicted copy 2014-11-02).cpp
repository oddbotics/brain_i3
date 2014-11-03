#include "oddbot_brain/oddbot_brain_translate_cmd.h"


oddbot_brain_translate_cmd::oddbot_brain_translate_cmd(){
	//subscribe to oddbot_boot
	//publish to oddbot_boot_stop
  ros::NodeHandle nodeHandle;
  od_pub = nodeHandle.advertise<nav_msgs::Odometry>("odom", 1000);
  vel_sub = nodeHandle.subscribe("cmd_vel", 1000, &oddbot_locom_test::get_info, this);
  char s[] = "/dev/ttymcx3";
}

// Callback message
void oddbot_locom_test::get_info(const geometry_msgs::Twist::ConstPtr& vel_msg){	
	ROS_INFO("Getting this forward vel: %f",vel_msg->linear.x);
}


void oddbot_brain_translate_cmd::send_od(){
  // Set the odom message
  od_msg.twist.twist.linear.x= 2;
	// Publish the odom message
  od_pub.publish(od_msg);
}


int main(int argc, char** argv){
	
	//stop when stop running flag is true
	ros::init(argc, argv, "oddbot_loc_test");

  oddbot_brain_translate_cmd tc = oddbot_brain_translate_cmd();
  
  ROS_INFO("oddbot brain translate node started!");  

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    lt.send_od();
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}
