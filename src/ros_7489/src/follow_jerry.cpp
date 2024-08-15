#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>

class FollowJerry : public rclcpp::Node {
public:
    FollowJerry() : Node("follow_jerry") {
        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            "Jerry_7489/pose", 10,
            std::bind(&FollowJerry::pose_callback, this, std::placeholders::_1));
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("Tom_7489/cmd_vel", 10);
    }

private:
    void pose_callback(const turtlesim::msg::Pose::SharedPtr/*msg*/) {
        auto follow_msg = geometry_msgs::msg::Twist();
        follow_msg.linear.x = 1.0;  // 设置速度
        follow_msg.angular.z = 0.0;  // 不旋转
        publisher_->publish(follow_msg);
    }

    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FollowJerry>());
    rclcpp::shutdown();
    return 0;
}
