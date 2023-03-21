// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from controller_input_srv:srv/Controller.idl
// generated code does not contain a copyright notice

#ifndef CONTROLLER_INPUT_SRV__SRV__DETAIL__CONTROLLER__TRAITS_HPP_
#define CONTROLLER_INPUT_SRV__SRV__DETAIL__CONTROLLER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "controller_input_srv/srv/detail/controller__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace controller_input_srv
{

namespace srv
{

inline void to_flow_style_yaml(
  const Controller_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: title
  {
    out << "title: ";
    rosidl_generator_traits::value_to_yaml(msg.title, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Controller_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: title
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "title: ";
    rosidl_generator_traits::value_to_yaml(msg.title, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Controller_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace controller_input_srv

namespace rosidl_generator_traits
{

[[deprecated("use controller_input_srv::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const controller_input_srv::srv::Controller_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  controller_input_srv::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use controller_input_srv::srv::to_yaml() instead")]]
inline std::string to_yaml(const controller_input_srv::srv::Controller_Request & msg)
{
  return controller_input_srv::srv::to_yaml(msg);
}

template<>
inline const char * data_type<controller_input_srv::srv::Controller_Request>()
{
  return "controller_input_srv::srv::Controller_Request";
}

template<>
inline const char * name<controller_input_srv::srv::Controller_Request>()
{
  return "controller_input_srv/srv/Controller_Request";
}

template<>
struct has_fixed_size<controller_input_srv::srv::Controller_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<controller_input_srv::srv::Controller_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<controller_input_srv::srv::Controller_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace controller_input_srv
{

namespace srv
{

inline void to_flow_style_yaml(
  const Controller_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: title
  {
    out << "title: ";
    rosidl_generator_traits::value_to_yaml(msg.title, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Controller_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: title
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "title: ";
    rosidl_generator_traits::value_to_yaml(msg.title, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Controller_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace controller_input_srv

namespace rosidl_generator_traits
{

[[deprecated("use controller_input_srv::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const controller_input_srv::srv::Controller_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  controller_input_srv::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use controller_input_srv::srv::to_yaml() instead")]]
inline std::string to_yaml(const controller_input_srv::srv::Controller_Response & msg)
{
  return controller_input_srv::srv::to_yaml(msg);
}

template<>
inline const char * data_type<controller_input_srv::srv::Controller_Response>()
{
  return "controller_input_srv::srv::Controller_Response";
}

template<>
inline const char * name<controller_input_srv::srv::Controller_Response>()
{
  return "controller_input_srv/srv/Controller_Response";
}

template<>
struct has_fixed_size<controller_input_srv::srv::Controller_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<controller_input_srv::srv::Controller_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<controller_input_srv::srv::Controller_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<controller_input_srv::srv::Controller>()
{
  return "controller_input_srv::srv::Controller";
}

template<>
inline const char * name<controller_input_srv::srv::Controller>()
{
  return "controller_input_srv/srv/Controller";
}

template<>
struct has_fixed_size<controller_input_srv::srv::Controller>
  : std::integral_constant<
    bool,
    has_fixed_size<controller_input_srv::srv::Controller_Request>::value &&
    has_fixed_size<controller_input_srv::srv::Controller_Response>::value
  >
{
};

template<>
struct has_bounded_size<controller_input_srv::srv::Controller>
  : std::integral_constant<
    bool,
    has_bounded_size<controller_input_srv::srv::Controller_Request>::value &&
    has_bounded_size<controller_input_srv::srv::Controller_Response>::value
  >
{
};

template<>
struct is_service<controller_input_srv::srv::Controller>
  : std::true_type
{
};

template<>
struct is_service_request<controller_input_srv::srv::Controller_Request>
  : std::true_type
{
};

template<>
struct is_service_response<controller_input_srv::srv::Controller_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // CONTROLLER_INPUT_SRV__SRV__DETAIL__CONTROLLER__TRAITS_HPP_
