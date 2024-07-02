#include <ros/ros.h>
#include <stdlib.h>

namespace smb_highlevel_controller{
    class SmbHighlevelController{
        private:
            ros::NodeHandle nodeHandle_;
            ros::Subscriber subscriber;
            std::string topic_name;
            int queue_size;
        public:
            SmbHighlevelController(ros::NodeHandle& nodeHandle_);
            void ScanCallBack(const sensor_msgs::LaserScan::ConstPtr& msg);
    }
}