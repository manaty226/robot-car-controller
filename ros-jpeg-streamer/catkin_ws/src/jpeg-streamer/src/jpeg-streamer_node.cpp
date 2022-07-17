#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <nadjieb/mjpeg_streamer.hpp>

using MJPEGStreamer = nadjieb::MJPEGStreamer;

cv::Mat image;
MJPEGStreamer streamer;
std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 90};
std::vector<uchar> buff_bgr;


void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
        cv::imencode(".jpg", image, buff_bgr, params);
        streamer.publish("/stream", std::string(buff_bgr.begin(), buff_bgr.end()));
    }
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

int main(int argc, char** argv) {

    streamer.start(8080);

    ros::init (argc, argv, "img_subscriber");
    ros::NodeHandle nh("~");
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber image_sub = it.subscribe("/img_publisher/image", 5, imageCallback);

    std::cout << "jpeg stream server starts." << std::endl;

    ros::spin();

    streamer.stop();
    return 0;
}