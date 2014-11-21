#include "oddbot_brain/dead_reckon.h"

dead_reckon::dead_reckon() {

	ros::NodeHandle nodeHandle;
	command_distance_pub = nodeHandle.advertise<geometry_msgs::Twist>("cmd_dist", 10);
  	dist_sub = nodeHandle.subscribe("distance_reporter", 1000, &dead_reckon::check_dist, this);
	target.linear.x = 0;
	target.linear.y = 0;
	lastpos.linear.x = 0;
 	lastpos.linear.y = 0;
	int actionpos = 0;
        //1000mm forward
	actions[0].linear.x = 1000;
	actions[0].linear.y = 1000;
	//Circle of turn is approx 1020 mm circumference
        //90 deg is +-255 for each wheel
	actions[1].linear.x = 1255;
	actions[1].linear.y = 745;
}

void dead_reckon::check_dist(const geometry_msgs::Twist::ConstPtr& dist_msg) {
	
	if (dist_msg->linear.x < (actions[actionpos].linear.x + 2) && dist_msg->linear.x > (actions[actionpos].linear.x - 2) && dist_msg->linear.y < (actions[actionpos].linear.y + 2) && dist_msg->linear.y > (actions[actionpos].linear.y - 2))
	{
		hit_target();
	}

	command_distance_pub.publish(target);
}

void dead_reckon::hit_target(){
	lastpos.linear.x = target.linear.x;
	lastpos.linear.y = target.linear.y;
	if (actions[++actionpos].linear.x || actions[actionpos].linear.y)
	{
		target.linear.x = actions[actionpos].linear.x + lastpos.linear.x;
		target.linear.y = actions[actionpos].linear.y + lastpos.linear.y;
	}
}


int main(int argc, char** argv) {
	ros::init(argc, argv, "dead_reckon_node");

	dead_reckon dr = dead_reckon();

	ROS_INFO("Dead Reckoning node started!");

	ros::Rate loop_rate(10);

	while(ros::ok()) {
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
