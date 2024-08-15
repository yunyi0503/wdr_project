#include <memory>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <turtlesim/srv/spawn.hpp>

class SpawnJerry : public rclcpp::Node {
public:
    SpawnJerry() : Node("spawn_jerry") {
        // 创建一个客户端，用于请求生成小海龟
        client_ = this->create_client<turtlesim::srv::Spawn>("spawn");

        // 等待服务可用
        while (!client_->wait_for_service(std::chrono::seconds(1))) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Waiting for spawn service...");
        }

        // 创建请求并设置参数
        auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
        request->x = 5.5;  // 设置 x 坐标
        request->y = 5.5;  // 设置 y 坐标
        request->name = "Jerry_7489";  // 设置小海龟的名字

        // 发送请求并处理响应
        auto result_future = client_->async_send_request(request);
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result_future) ==
            rclcpp::FutureReturnCode::SUCCESS) {
            RCLCPP_INFO(this->get_logger(), "Spawned turtle named %s", request->name.c_str());
        } else {
            RCLCPP_ERROR(this->get_logger(), "Failed to call service spawn");
        }
    }

private:
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr client_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SpawnJerry>());
    rclcpp::shutdown();
    return 0;
}
