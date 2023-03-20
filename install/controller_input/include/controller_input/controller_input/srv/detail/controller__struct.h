// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from controller_input:srv/Controller.idl
// generated code does not contain a copyright notice

#ifndef CONTROLLER_INPUT__SRV__DETAIL__CONTROLLER__STRUCT_H_
#define CONTROLLER_INPUT__SRV__DETAIL__CONTROLLER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'title'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Controller in the package controller_input.
typedef struct controller_input__srv__Controller_Request
{
  rosidl_runtime_c__String title;
} controller_input__srv__Controller_Request;

// Struct for a sequence of controller_input__srv__Controller_Request.
typedef struct controller_input__srv__Controller_Request__Sequence
{
  controller_input__srv__Controller_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} controller_input__srv__Controller_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'title'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Controller in the package controller_input.
typedef struct controller_input__srv__Controller_Response
{
  rosidl_runtime_c__String title;
} controller_input__srv__Controller_Response;

// Struct for a sequence of controller_input__srv__Controller_Response.
typedef struct controller_input__srv__Controller_Response__Sequence
{
  controller_input__srv__Controller_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} controller_input__srv__Controller_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CONTROLLER_INPUT__SRV__DETAIL__CONTROLLER__STRUCT_H_
