#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/String.h>
#include <std_msgs/Char.h>
#include <std_msgs/Int32MultiArray.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "image_publisher");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Publisher pub = it.advertise("camera/image", 1);
	cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
	//cv::waitKey(30);
	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();


	ros::Publisher pub_first = nh.advertise<std_msgs::String>("/comece_aqui", 1000);

	std_msgs::String pub1_msg;
	pub1_msg.data = "Next topic is /becker";
	
  ros::Rate loop_rate(5);
  while (nh.ok()) 
  {
  	pub_first.publish(pub1_msg);
  	
  
  
  
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}
