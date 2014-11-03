/*
 * \oddbot_boot_brain.h
 *
 * \author Chris Dunkers, CMU - cmdunkers@cmu.edu
 * \date October 13, 2014
 */

#ifndef ODDBOT_BOOT_BRAIN_H_
#define ODDBOT_BOOT_BRAIN_H_

#include "ros/ros.h"
#include "oddbot_msgs/OddbotBoot.h"
#include "oddbot_msgs/OddbotBootStop.h"

class oddbot_boot_brain
{
	public:
		oddbot_boot_brain();
	private:
		ros::Publisher stop_pub;
		ros::Subscriber boot_sub;
		void get_info(const oddbot_msgs::OddbotBoot::ConstPtr& boot_msg);
};

int main(int argc, char** argv);

#endif
