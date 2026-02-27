#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

#define PEDAL_STROKE_MAX_VAL 4095 ///< Maximum pedal stroke value
#define PWM_SIGNAL_MAX_VAL 255 ///< Maximum PWM signal value

/**
 * @class StrokeToPwmNode
 * @brief ROS2 node that converts pedal stroke values to PWM signals
 * @author Brian Liang (brianliang0709@gmail.com)
 */
class StrokeToPwmNode : public rclcpp::Node
{
public:
    /**
    * @brief Constructor for the StrokeToPwmNode class 
    * Initializes the ROS2 node, creates subscription to the "pedal_stroke" topic and creates 
    * publisher for the "pwm_signal" topic
    * @author Brian Liang (brianliang0709@gmail.com)
    */
    StrokeToPwmNode() : Node("stroke_to_pwm_node")
    {
        subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "pedal_stroke", 20, std::bind(&StrokeToPwmNode::pedalStrokeCallback, this, std::placeholders::_1));
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("pwm_signal", 20);
    }
private:
    /**
    * @brief Callback function to process incoming pedal stroke values
    * Maps pedal stroke value to pwm signal linearly and publishes it 
    * @author Brian Liang (brianliang0709@gmail.com)
    * @param msg 
    */
    void pedalStrokeCallback(const std_msgs::msg::Int32::SharedPtr msg)
    {
        int pedal_stroke_value = msg->data;
        int pwm_signal = pedal_stroke_value * PWM_SIGNAL_MAX_VAL / PEDAL_STROKE_MAX_VAL;

        auto pwm_signal_msg = std_msgs::msg::Int32();
        pwm_signal_msg.data = pwm_signal;
        publisher_->publish(pwm_signal_msg);
        //RCLCPP_INFO(this->get_logger(), "PWM Signal: %d", pwm_signal);
    }

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_; ///< Subscription to the "pedal_stroke" topic
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_; ///< Publisher for the "pwm_signal" topic 
};

/**
 * @brief The main function to run the ROS2 node
 * @author Brian Liang (brianliang0709@gmail.com)
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<StrokeToPwmNode>());
    rclcpp::shutdown();
    return 0;
}