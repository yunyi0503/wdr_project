#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>  // 确保包含这个头文件

class RotateJerry : public rclcpp::Node {
public:
    RotateJerry() : Node("rotate_jerry") {
        // 创建发布者，发布速度命令到"/jerry_7489/cmd_vel"话题
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("jerry_7489/cmd_vel", 10);

        // 设置定时器，每100毫秒发布一次速度命令
        timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&RotateJerry::rotate, this));
    }

private:
    void rotate() {
        auto msg = geometry_msgs::msg::Twist();
        
        // 设定线速度，假设为0.5
        double linear_speed = 0.5;  
        // 半径
        double radius = 1.25;        
        // 计算角速度
        double angular_speed = linear_speed / radius;  

        // 设置线速度为0，角速度为负值以实现顺时针旋转
        msg.linear.x = 0.0; 
        msg.angular.z = -angular_speed;  // 顺时针旋转，设为负值

        publisher_->publish(msg);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RotateJerry>());
    rclcpp::shutdown();
    return 0;
}
