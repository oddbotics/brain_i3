/*
 * \oddbot_boot_brain.h
 *
 * \author Chris Dunkers, CMU - cmdunkers@cmu.edu
 * \date October 13, 2014
 */

#ifndef ODDBOT_BRAIN_LOCTEST_H_
#define ODDBOT_BRAIN_LOCTEST_H_

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"

class oddbot_brain_loctest
{
	public:
		oddbot_brain_loctest();
	private:
		ros::Publisher vel_pub;
		ros::Subscriber od_sub;
		void get_info(const nav_msgs::Odometry::ConstPtr& od_msg);
};

int main(int argc, char** argv);

#endif
