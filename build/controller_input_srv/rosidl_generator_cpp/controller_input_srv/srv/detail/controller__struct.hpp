// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from controller_input_srv:srv/Controller.idl
// generated code does not contain a copyright notice

#ifndef CONTROLLER_INPUT_SRV__SRV__DETAIL__CONTROLLER__STRUCT_HPP_
#define CONTROLLER_INPUT_SRV__SRV__DETAIL__CONTROLLER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__controller_input_srv__srv__Controller_Request __attribute__((deprecated))
#else
# define DEPRECATED__controller_input_srv__srv__Controller_Request __declspec(deprecated)
#endif

namespace controller_input_srv
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Controller_Request_
{
  using Type = Controller_Request_<ContainerAllocator>;

  explicit Controller_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->title = "";
    }
  }

  explicit Controller_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : title(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->title = "";
    }
  }

  // field types and members
  using _title_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _title_type title;

  // setters for named parameter idiom
  Type & set__title(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->title = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    controller_input_srv::srv::Controller_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const controller_input_srv::srv::Controller_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<controller_input_srv::srv::Controller_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<controller_input_srv::srv::Controller_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      controller_input_srv::srv::Controller_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<controller_input_srv::srv::Controller_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      controller_input_srv::srv::Controller_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<controller_input_srv::srv::Controller_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<controller_input_srv::srv::Controller_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<controller_input_srv::srv::Controller_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__controller_input_srv__srv__Controller_Request
    std::shared_ptr<controller_input_srv::srv::Controller_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__controller_input_srv__srv__Controller_Request
    std::shared_ptr<controller_input_srv::srv::Controller_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Controller_Request_ & other) const
  {
    if (this->title != other.title) {
      return false;
    }
    return true;
  }
  bool operator!=(const Controller_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Controller_Request_

// alias to use template instance with default allocator
using Controller_Request =
  controller_input_srv::srv::Controller_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace controller_input_srv


#ifndef _WIN32
# define DEPRECATED__controller_input_srv__srv__Controller_Response __attribute__((deprecated))
#else
# define DEPRECATED__controller_input_srv__srv__Controller_Response __declspec(deprecated)
#endif

namespace controller_input_srv
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Controller_Response_
{
  using Type = Controller_Response_<ContainerAllocator>;

  explicit Controller_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->title = "";
    }
  }

  explicit Controller_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : title(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->title = "";
    }
  }

  // field types and members
  using _title_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _title_type title;

  // setters for named parameter idiom
  Type & set__title(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->title = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    controller_input_srv::srv::Controller_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const controller_input_srv::srv::Controller_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<controller_input_srv::srv::Controller_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<controller_input_srv::srv::Controller_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      controller_input_srv::srv::Controller_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<controller_input_srv::srv::Controller_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      controller_input_srv::srv::Controller_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<controller_input_srv::srv::Controller_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<controller_input_srv::srv::Controller_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<controller_input_srv::srv::Controller_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__controller_input_srv__srv__Controller_Response
    std::shared_ptr<controller_input_srv::srv::Controller_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__controller_input_srv__srv__Controller_Response
    std::shared_ptr<controller_input_srv::srv::Controller_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Controller_Response_ & other) const
  {
    if (this->title != other.title) {
      return false;
    }
    return true;
  }
  bool operator!=(const Controller_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Controller_Response_

// alias to use template instance with default allocator
using Controller_Response =
  controller_input_srv::srv::Controller_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace controller_input_srv

namespace controller_input_srv
{

namespace srv
{

struct Controller
{
  using Request = controller_input_srv::srv::Controller_Request;
  using Response = controller_input_srv::srv::Controller_Response;
};

}  // namespace srv

}  // namespace controller_input_srv

#endif  // CONTROLLER_INPUT_SRV__SRV__DETAIL__CONTROLLER__STRUCT_HPP_
