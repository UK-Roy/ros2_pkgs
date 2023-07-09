#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

class Msg2Bot : public rclcpp::Node
{
  public:
    Msg2Bot()
    : Node("msg_bot")
    {
      subscription_ = this->create_subscription<std_msgs::msg::String>(
      "pose_msg", 10, std::bind(&Msg2Bot::topic_callback, this, _1));
    }

  private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Pose Information: '%s'", msg->data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Msg2Bot>());
  rclcpp::shutdown();
  return 0;
}
