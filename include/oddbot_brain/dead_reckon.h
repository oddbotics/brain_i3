#ifndef DEAD_RECKON_H_
#define DEAD_RECKON_H_

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

class dead_reckon {
private:
 geometry_msgs::Twist actions[10];
 geometry_msgs::Twist target;
 geometry_msgs::Twist lastpos;
 int actionpos;
 ros::Publisher command_distance_pub;
 ros::Subscriber dist_sub;
public:
	dead_reckon();
	void check_dist(const geometry_msgs::Twist::ConstPtr& dist_msg);
	void hit_target();
};

int main(int argc, char** argv);


#endif
