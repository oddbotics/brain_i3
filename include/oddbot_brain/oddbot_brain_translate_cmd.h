#ifndef ODDBOT_BRAIN_TRANSLATE_CMD_H_
#define ODDBOT_BRAIN_TRANSLATE_CMD_H_

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"

class oddbot_brain_translate_cmd
{
	public:
		oddbot_brain_translate_cmd();
	private:
		ros::Publisher vel_trans;
		ros::Subscriber vel_sub;
		void get_vel(const geometry_msgs::Twist::ConstPtr& trans_vel_msg);
};

int main(int argc, char** argv);

#endif
