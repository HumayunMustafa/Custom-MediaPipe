load("@bazel_skylib//:bzl_library.bzl","bzl_library")
load("//mediapipe/framework/port:build_config.bzl","mediapipe_proto_library")
package(default_visibility=["//visibility:private"])

package_group(
    name="mediapipe_internal",
    packages=[
        "//mediapipe/...",
    ],
)

cc_library(
    name="calculator_state",
    srcs=["calculator_state.cc"],
    hdrs=["calculator_state.h"],
    visibility=[":mediapipe_internal"],
    deps=[
        ":calculator_cc_proto",
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