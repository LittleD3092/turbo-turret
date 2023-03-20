// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from controller_input:srv/Controller.idl
// generated code does not contain a copyright notice

#ifndef CONTROLLER_INPUT__SRV__DETAIL__CONTROLLER__BUILDER_HPP_
#define CONTROLLER_INPUT__SRV__DETAIL__CONTROLLER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "controller_input/srv/detail/controller__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace controller_input
{

namespace srv
{

namespace builder
{

class Init_Controller_Request_title
{
public:
  Init_Controller_Request_title()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::controller_input::srv::Controller_Request title(::controller_input::srv::Controller_Request::_title_type arg)
  {
    msg_.title = std::move(arg);
    return std::move(msg_);
  }

private:
  ::controller_input::srv::Controller_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::controller_input::srv::Controller_Request>()
{
  return controller_input::srv::builder::Init_Controller_Request_title();
}

}  // namespace controller_input


namespace controller_input
{

namespace srv
{

namespace builder
{

class Init_Controller_Response_title
{
public:
  Init_Controller_Response_title()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::controller_input::srv::Controller_Response title(::controller_input::srv::Controller_Response::_title_type arg)
  {
    msg_.title = std::move(arg);
    return std::move(msg_);
  }

private:
  ::controller_input::srv::Controller_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::controller_input::srv::Controller_Response>()
{
  return controller_input::srv::builder::Init_Controller_Response_title();
}

}  // namespace controller_input

#endif  // CONTROLLER_INPUT__SRV__DETAIL__CONTROLLER__BUILDER_HPP_
