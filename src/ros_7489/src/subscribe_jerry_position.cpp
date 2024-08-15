#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>

class SubscribeJerryPosition : public rclcpp::Node {
public:
    SubscribeJerryPosition() : Node("subscribe_jerry_position") {
        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            "Jerry_7489/pose", 10,
            std::bind(&SubscribeJerryPosition::pose_callback, this, std::placeholders::_1));
    }

private:
    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Jerry_7489 position: (%.2f, %.2f)", msg->x, msg->y);
    }
    
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SubscribeJerryPosition>());
    rclcpp::shutdown();
    return 0;
}
