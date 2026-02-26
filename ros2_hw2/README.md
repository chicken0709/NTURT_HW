# Part 1

## Question 1-1

Topic communimcation is used to move data between different nodes in a ROS2 system. A node can pusblish messages to a topic or subscribe to a topic to receive messages. The form of topic communication is not limited to one-to-one, it can also be one-to-many, many-to-one, or many-to-many. 

## Question 1-2

```C++
#include "rclcpp/rclcpp.hpp"
// Fill the missing line of code
// Hint: include the ROS2 integer 32 bit library for messaging
#include "std_msgs/msg/int32.hpp"

int main(int argc, char** argv)
{
    // initialize ROS2
    rclcpp::init(argc, argv); // Explain this line
    // create a ROS2 node with the name "publisher_node"
    auto node = rclcpp::Node::make_shared("publisher_node"); // Explain this line
    // create a publisher for "node" that publishes to the "count_values" topic
    // the message type it publishes is int32 and the queue size is 10
    auto publisher = node->create_publisher<std_msgs::msg::Int32>("count_values", 10); // Explain this line
    
    // 
    rclcpp::Rate loop_rate(1);
        
    int count = 1;
    while (rclcpp::ok() && count <= 5)
    {
        auto msg = std_msgs::msg::Int32();
        // Fill the missing line of code
        // Hint: makes the content of "msg" to be the value of "count" variable
        msg.data = count;

        publisher->publish(msg);
        RCLCPP_INFO(node->get_logger(), "Publishing: %d", msg.data); // Explain this line
        // Fill the missing line of code
        // Hint: execute the callback function under the "node" node
        rclcpp::spin_some(node);

        loop_rate.sleep();
        count++;
    }
    
    rclcpp::shutdown();
    return 0;    
}

```