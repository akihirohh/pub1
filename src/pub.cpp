#include <ros/ros.h>
#include <ros/package.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/String.h>
#include <std_msgs/Char.h>
#include <std_msgs/Int32MultiArray.h>
#include <sensor_msgs/BatteryState.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "image_publisher");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Publisher pub = it.advertise("becker", 1);
	std::string fig_path = ros::package::getPath("pub1") + "/include/.becker.png";
	cv::Mat image = cv::imread(fig_path, CV_LOAD_IMAGE_COLOR);
	//cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();


	ros::Publisher pub_first = nh.advertise<std_msgs::String>("/start_here", 1000);
	ros::Publisher pub_daniel = nh.advertise<std_msgs::Char>("/daniel", 1000);
	ros::Publisher pub_glauco = nh.advertise<std_msgs::Int32MultiArray>("/glauco", 1000);
	ros::Publisher pub_adriano = nh.advertise<sensor_msgs::BatteryState>("/adriano", 1000);

	std_msgs::String pub1_msg;
	pub1_msg.data = "Next topic is /adriano. Check the different fields of the message. The hidden phrase is between # characters and has less than 500 characters.";
	
	std_msgs::Char daniel_msg;
	char buf[] = "#Next topic is /glauco. You need to divide the obtained numbers by the closest integer to /glauco's publishing rate.#";
	
	std_msgs::Int32MultiArray glauco_msg;
	char buf2[] = "The next topic is /becker. Run rosrun image_view image_view image:=<insert your topic here>";
	;
	for(int j = 0; j < sizeof(buf2)/sizeof(char); j++)
	{
		glauco_msg.data.push_back(buf2[j]*100);
	}
	
	sensor_msgs::BatteryState adriano_msg;
	adriano_msg.location = "Next topic is /daniel.";
	adriano_msg.serial_number = "You need to convert every number using ASCII.";
	
	//becker
  ros::Rate loop_rate(100);
  int i = 0;
  while (nh.ok()) 
  {
  	pub_first.publish(pub1_msg);
  	
  	daniel_msg.data = buf[i];
  	i++;
  	if(i > sizeof(buf)/sizeof(char)) i = 0;
  	pub_daniel.publish(daniel_msg);
  	
  	pub_glauco.publish(glauco_msg);
  
  	pub_adriano.publish(adriano_msg);
  
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}
