#include <memory>
#include<chrono>
#include<functional>
#include<string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;
using namespace std::chrono_literals;

class Msg2Bot : public rclcpp::Node
{
  public:
    Msg2Bot()
    : Node("msg_bot"), count_(0)
    {
      subscription_ = this->create_subscription<std_msgs::msg::String>(
      "pose_msg", 10, std::bind(&Msg2Bot::topic_callback, this, _1));
      publisher = this->create_publisher<std_msgs::msg::String>("streaming_pose", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Msg2Bot::timer_callback, this));

    }

  private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Pose Information: '%s'", msg->data.c_str());
    }
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Pose Data: " + std::to_string(count_++);
      // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher->publish(message);
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Msg2Bot>());
  rclcpp::shutdown();
  return 0;
}
