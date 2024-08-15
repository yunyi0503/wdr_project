#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <turtlesim/msg/pose.hpp>

class BroadcastTF : public rclcpp::Node {
public:
    BroadcastTF() : Node("broadcast_tf") {
        tf_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            "Jerry_7489/pose", 10,
            std::bind(&BroadcastTF::pose_callback, this, std::placeholders::_1));
    }

private:
    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg) {
        geometry_msgs::msg::TransformStamped transform;
        transform.header.stamp = this->get_clock()->now();
        transform.header.frame_id = "world";
        transform.child_frame_id = "Jerry_7489";
        transform.transform.translation.x = msg->x;
        transform.transform.translation.y = msg->y;
        transform.transform.rotation.w = 1.0;  // 假设没有旋转

        tf_broadcaster_->sendTransform(transform);
    }

    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_broadcaster_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BroadcastTF>());
    rclcpp::shutdown();
    return 0;
}
