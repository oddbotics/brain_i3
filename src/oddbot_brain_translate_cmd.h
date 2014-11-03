#include "oddbot_brain/oddbot_brain_translate_cmd.h"

oddbot_brain_translate_cmd::oddbot_brain_translate_cmd(){
	//subscribe to oddbot_boot
	//publish to oddbot_boot_stop
  ros::NodeHandle nodeHandle;
  
  //make the publishing topic a parameter at some point
  vel_trans = nodeHandle.advertise<geometry_msgs::Twist>("translated_vel", 1000);
  vel_sub = nodeHandle.subscribe("cmd_vel", 1000, &oddbot_brain_translate_cmd::get_info, this);
}

// Callback message
void oddbot_brain_translate_cmd::get_vel(const geometry_msgs::Twist::ConstPtr& vel_msg){	
	ROS_INFO("Getting this cmd vel: %f",vel_msg->linear.x);
	//make this change by parameters also
	trans_vel_msg.linear.x = (vel_msg->linear.x + 1.0) * 128.0;
	
	//make this change by parameters also
	trans_vel_msg.angular.z = (vel_msg->angular.z + 1.0) * 128.0;
	
	// Publish the trans message
    vel_trans.publish(trans_vel_msg);
}

void oddbot_brain_translate_cmd::send_trans_vel(){
  //More traditional Drewish publishing
}

int main(int argc, char** argv){
	
	//stop when stop running flag is true
	ros::init(argc, argv, "oddbot_brain_trans_node");

  oddbot_brain_translate_cmd tc = oddbot_brain_translate_cmd();
  
  ROS_INFO("oddbot brain translate node started!");  

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}
