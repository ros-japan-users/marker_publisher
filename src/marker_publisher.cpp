#include <cmath>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#define DEFAULT_RATE 20

int main(int argc, char *argv[]){
    ros::init(argc, argv, "test");
    ros::NodeHandle n;
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
    visualization_msgs::Marker line_strip;
    line_strip.header.frame_id = "practice";
    line_strip.ns = "practice";
    line_strip.id = 1;
    
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    line_strip.action = visualization_msgs::Marker::ADD;
    
    line_strip.scale.x = 0.1;
    line_strip.color.b = 1.0;
    line_strip.color.a = 1.0;
    float phai = 0.0;
    n.setParam("/rate", DEFAULT_RATE);

    for(int i=0; i <= 10; i++){
        const float radius = i % 2 ? 6.0 : 3.0;
        const float theta = (72.0 * (i/2) + (i%2) * 36.0) * M_PI / 180.0;
        geometry_msgs::Point vertex;
        vertex.x = radius * cos(theta);
        vertex.y = radius * sin(theta);
        line_strip.points.push_back(vertex);
    }

    while(ros::ok()){
        int val = DEFAULT_RATE;
        if(n.getParam("/rate", val)){
            std::cout << "val = " << val << std::endl;
        }
        ros::Rate r(val);
        line_strip.header.stamp = ros::Time::now();
        line_strip.pose.orientation.z = sin(phai / 2);
        line_strip.pose.orientation.w = cos(phai / 2);

        marker_pub.publish(line_strip);
        phai += 0.05;
        if(phai > 2 * M_PI) phai -= 2 * M_PI;
        r.sleep();
    }
    return 0;
}
