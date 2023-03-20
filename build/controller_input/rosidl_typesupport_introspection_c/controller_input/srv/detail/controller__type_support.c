// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from controller_input:srv/Controller.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "controller_input/srv/detail/controller__rosidl_typesupport_introspection_c.h"
#include "controller_input/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "controller_input/srv/detail/controller__functions.h"
#include "controller_input/srv/detail/controller__struct.h"


// Include directives for member types
// Member `title`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  controller_input__srv__Controller_Request__init(message_memory);
}

void controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_fini_function(void * message_memory)
{
  controller_input__srv__Controller_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_message_member_array[1] = {
  {
    "title",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(controller_input__srv__Controller_Request, title),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_message_members = {
  "controller_input__srv",  // message namespace
  "Controller_Request",  // message name
  1,  // number of fields
  sizeof(controller_input__srv__Controller_Request),
  controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_message_member_array,  // message members
  controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_message_type_support_handle = {
  0,
  &controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_controller_input
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, controller_input, srv, Controller_Request)() {
  if (!controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_message_type_support_handle.typesupport_identifier) {
    controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &controller_input__srv__Controller_Request__rosidl_typesupport_introspection_c__Controller_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "controller_input/srv/detail/controller__rosidl_typesupport_introspection_c.h"
// already included above
// #include "controller_input/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "controller_input/srv/detail/controller__functions.h"
// already included above
// #include "controller_input/srv/detail/controller__struct.h"


// Include directives for member types
// Member `title`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  controller_input__srv__Controller_Response__init(message_memory);
}

void controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_fini_function(void * message_memory)
{
  controller_input__srv__Controller_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_message_member_array[1] = {
  {
    "title",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(controller_input__srv__Controller_Response, title),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_message_members = {
  "controller_input__srv",  // message namespace
  "Controller_Response",  // message name
  1,  // number of fields
  sizeof(controller_input__srv__Controller_Response),
  controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_message_member_array,  // message members
  controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_message_type_support_handle = {
  0,
  &controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_controller_input
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, controller_input, srv, Controller_Response)() {
  if (!controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_message_type_support_handle.typesupport_identifier) {
    controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &controller_input__srv__Controller_Response__rosidl_typesupport_introspection_c__Controller_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "controller_input/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "controller_input/srv/detail/controller__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_service_members = {
  "controller_input__srv",  // service namespace
  "Controller",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_Request_message_type_support_handle,
  NULL  // response message
  // controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_Response_message_type_support_handle
};

static rosidl_service_type_support_t controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_service_type_support_handle = {
  0,
  &controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, controller_input, srv, Controller_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, controller_input, srv, Controller_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_controller_input
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, controller_input, srv, Controller)() {
  if (!controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_service_type_support_handle.typesupport_identifier) {
    controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, controller_input, srv, Controller_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, controller_input, srv, Controller_Response)()->data;
  }

  return &controller_input__srv__detail__controller__rosidl_typesupport_introspection_c__Controller_service_type_support_handle;
}
