# include "oddbot_brain/oddbot_brain_loctest.h"

oddbot_brain_loctest::oddbot_brain_loctest(){
  //the main node handle
  ros::NodeHandle nh;

  //grab the parameters
  //ros::NodeHandle private_node_handle_("~");
  //private_node_handle_.param<double>("param", variable, value);
  
  //initialize the publishers and subscribers
  vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
  od_sub = nh.subscribe("odom", 1000, &oddbot_brain_loctest::get_info, this);
}

void oddbot_brain_loctest::get_info(const nav_msgs::Odometry::ConstPtr& od_msg){
	
	geometry_msgs::Twist vel_msg;
	vel_msg.linear.x = 100;
	//od_msg.subnet = boot_msg->subnet;
	ROS_INFO("This is info from odometry: %f", od_msg->twist.twist.linear.x);
	vel_pub.publish(vel_msg);
}

int main(int argc, char** argv){
  
  ros::init(argc, argv, "oddbot_brain_loctest");

  oddbot_brain_loctest obl = oddbot_brain_loctest();
  
  ROS_INFO("oddbot boot brain node started!");	

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
