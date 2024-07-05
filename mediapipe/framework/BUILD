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
    name = "port",
    hdrs = ["port.h"],
    defines = select({
                  "//conditions:default": [],
              }) + select({
                  "//conditions:default": [],
                  "//mediapipe/gpu:disable_gpu": ["MEDIAPIPE_DISABLE_GPU=1"],
              }) +
              select({
                  "//conditions:default": [],
                  "//mediapipe/framework/port:disable_opencv": ["MEDIAPIPE_DISABLE_OPENCV=1"],
              }) + select({
        "//conditions:default": [],
        # TODO: Improve this. This only sets MEDIAPIPE_DISABLE_OPENCV as a "defines" Make
        # value, not as a bazel "--define" variable, which has effects in C++ code but not in
        # select() statements.
        "//mediapipe/framework/port:enable_halide": [
            "MEDIAPIPE_ENABLE_HALIDE=1",
            "MEDIAPIPE_DISABLE_OPENCV=1",
        ],
    }) + select({
        "//conditions:default": [],
        "//mediapipe/framework:disable_rtti_and_exceptions": [
            "MEDIAPIPE_HAS_RTTI=0",
        ],
        # Excludes AHardwareBuffer features from vendor processes
        "//mediapipe/framework:android_no_jni": ["MEDIAPIPE_NO_JNI"],
        # unless they're linked against nativewindow.
        "//mediapipe/framework/formats:android_link_native_window": [
            "MEDIAPIPE_ANDROID_LINK_NATIVE_WINDOW",
            "MEDIAPIPE_NO_JNI",
        ],
    }),
    visibility = [
        "//fitbit/research/sensing/mobisense:__subpackages__",
        "//mediapipe/calculators:__subpackages__",
        "//mediapipe/framework:__subpackages__",
        "//mediapipe/framework/port:__pkg__",
        "//mediapipe/gpu:__pkg__",
        "//mediapipe/util:__subpackages__",
    ],
)

# Defines Packet, a data carrier used throughout the framework.
cc_library(
    name = "packet",
    srcs = ["packet.cc"],
    hdrs = ["packet.h"],
    visibility = ["//visibility:public"],
    deps=[
        ":port",
    ],
)

cc_library(
    name = "graph_service",
    hdrs = ["graph_service.h"],
    visibility = [":mediapipe_internal"],
    deps = [
        ":packet",
    ]
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