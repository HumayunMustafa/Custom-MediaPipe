load("@bazel_skylib//:bzl_library.bzl","bzl_library")
load("//mediapipe/framework/port:build_config.bzl","mediapipe_proto_library")
package(default_visibility=["//visibility:private"])

package_group(
    name="mediapipe_internal",
    packages=[
        "//mediapipe/...",
    ],
)

mediapipe_proto_library(
    name = "calculator_proto",
    srcs = ["calculator.proto"],
    visibility = ["//visibility:public"],
    deps = [
        ":calculator_options_proto",
        ":mediapipe_options_proto",
        ":packet_factory_proto",
        ":packet_generator_proto",
        ":status_handler_proto",
        ":stream_handler_proto",
        "@com_google_protobuf//:any_proto",
    ],
)

mediapipe_proto_library(
    name = "calculator_options_proto",
    srcs = ["calculator_options.proto"],
    visibility = ["//visibility:public"],
)

mediapipe_proto_library(
    name = "mediapipe_options_proto",
    srcs = ["mediapipe_options.proto"],
    visibility = [
        ":mediapipe_internal_proto_users",
    ],
)

mediapipe_proto_library(
    name = "packet_factory_proto",
    srcs = ["packet_factory.proto"],
    visibility = ["//visibility:public"],
)

mediapipe_proto_library(
    name = "packet_generator_proto",
    srcs = ["packet_generator.proto"],
    visibility = ["//visibility:public"],
)

mediapipe_proto_library(
    name = "status_handler_proto",
    srcs = ["status_handler.proto"],
    visibility = [":mediapipe_internal_proto_users"],
    deps = [":mediapipe_options_proto"],
)

mediapipe_proto_library(
    name = "stream_handler_proto",
    srcs = ["stream_handler.proto"],
    visibility = [":mediapipe_internal_proto_users"],
    deps = [":mediapipe_options_proto"],
)

cc_library(
    name = "counter",
    hdrs = ["counter.h"],
    visibility = ["//visibility:public"],
    deps = ["//mediapipe/framework/port:integral_types"],
)

cc_library(
    name="calculator_state",
    srcs=["calculator_state.cc"],
    hdrs=["calculator_state.h"],
    visibility=[":mediapipe_internal"],
    deps=[
        ":calculator_cc_proto",
        ":counter",
    ],
)

cc_library(
    name="calculator_context",
    srcs=["calculator_context.cc"],
    hdrs=["calculator_context.h"],
    visibility=[":mediapipe_internal"],
    deps=[
        ":calculator_state",
    ],
)

cc_library(
    name="calculator_base",
    srcs=["calculator_base.cc"],
    hdrs=["calculator_base.h"],
    visibility=["//visibility:public"],
    deps=[
        ":calculator_context",
    ],
)

cc_library(
    name="calculator_framework",
    hdrs=["calculator_framework.h"],
    visibility=["//visibility:public"],
    deps=[
        ":calculator_base",
    ],
)