#include <rclcpp/rclcpp.hpp>
#include <turtlesim/srv/set_pen.hpp>

class SetBackgroundColor : public rclcpp::Node {
public:
    SetBackgroundColor() : Node("set_background_color") {
        client_ = this->create_client<turtlesim::srv::SetPen>("set_pen");

        // 等待服务可用
        while (!client_->wait_for_service(std::chrono::seconds(1))) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Waiting for set_pen service...");
        }

        // 创建请求并设置背景颜色为绿色
        auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
        request->r = 0;    // 红色分量
        request->g = 255;  // 绿色分量
        request->b = 0;    // 蓝色分量
        request->width = 10;
        request->off = 0;  // 开启笔

        // 发送请求
        auto result_future = client_->async_send_request(request);
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result_future) ==
            rclcpp::FutureReturnCode::SUCCESS) {
            RCLCPP_INFO(this->get_logger(), "Background color set to green");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Failed to call service set_pen");
        }
    }

private:
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr client_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SetBackgroundColor>());
    rclcpp::shutdown();
    return 0;
}
