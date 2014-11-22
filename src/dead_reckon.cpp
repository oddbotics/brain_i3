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
	position_tolerance = 2;

	for (int i = 0; i < num_actions; i++) {

		// Move forward 1000 mm first
		if (i % 2 == 0) {
			actions[i].linear.x = 1000;
			actions[i].linear.y = 1000;
		}
		// Then turn 135 degrees
		else {
			/* Circle of turn is approx 1020 mm circumference 90 
			   deg is +-255 for each wheel 135 deg is +-382 for each wheel */
			actions[i].linear.x = 382;
			actions[i].linear.y = -382;
		}
	}
}

void dead_reckon::check_dist(const geometry_msgs::Twist::ConstPtr& dist_msg) {
	// If you are within your position tolerance, you have hit your target
	if (dist_msg->linear.x < (actions[actionpos].linear.x + position_tolerance) && 
		dist_msg->linear.x > (actions[actionpos].linear.x - position_tolerance) && 
		dist_msg->linear.y < (actions[actionpos].linear.y + position_tolerance) && 
		dist_msg->linear.y > (actions[actionpos].linear.y - position_tolerance))
	{
		hit_target();
	}

	command_distance_pub.publish(target);
}

/* If there is still an action position, set the new encoder target to it in addition to the current position */
void dead_reckon::hit_target(){
	lastpos.linear.x = target.linear.x;
	lastpos.linear.y = target.linear.y;
	// Increment the action position to the next position
	++actionpos;

	if (actions[actionpos].linear.x || actions[actionpos].linear.y)
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
