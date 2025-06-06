# Copyright 2019 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load("@bazel_skylib//:bzl_library.bzl", "bzl_library")
load("//mediapipe/framework/port:build_config.bzl", "mediapipe_proto_library")

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# For direct MediaPipe internal proto usage. Please only add your package
# here if necessary and using
# "//mediapipe/framework:calculator_framework" is not sufficient
# (e.g. auto generated code for serialization etc.)
package_group(
    name = "mediapipe_internal_proto_users",
    packages = [
            "//mediapipe/...",
        ],
)

# The MediaPipe internal package group. No mediapipe users should be added to this group.
package_group(
    name = "mediapipe_internal",
    packages = [
        "//mediapipe/...",
    ],
)

# When --copt=-fno-rtti is set, MEDIAPIPE_HAS_RTTI is cleared in port.h.
# To explicitly clear MEDIAPIPE_HAS_RTTI, compile with:
#   bazel build --define=disable_rtti_and_exceptions=true
config_setting(
    name = "disable_rtti_and_exceptions",
    define_values = {
      "disable_rtti_and_exceptions" : "true"
    },
    visibility = ["//visibility:public"],
)

# It is for pure-native Android builds where the library can't have any dependency on libandroid.so
config_setting(
    name = "android_no_jni",
    define_values = {
        "MEDIAPIPE_NO_JNI" : "1"
    },
    values = {"crosstool_top": "//external:android/crosstool"},
    visibility = ["//visibility:public"],
)

cc_library(
    name = "graph_service",
    hdrs = ["graph_service.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":packet",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/port:statusor",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/strings",
    ]
)

cc_library(
    name = "port",
    hdrs = ["port.h"],
    defines = select({
                    "//conditions:default" : [],
               }) + select({
                   "//conditions:default" : [],
                   "//mediapipe/gpu:disable_gpu": ["MEDIAPIPE_DISABLE_GPU=1"],
               }) + select({
                   "//conditions:default" : [],
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
               })
               ,
    visibility = [
                "//fitbit/research/sensing/mobisense:__subpackages__",
                "//mediapipe/calculators:__subpackages__",
                "//mediapipe/framework:__subpackages__",
                "//mediapipe/framework/port:__pkg__",
                "//mediapipe/gpu:__pkg__",
                "//mediapipe/util:__subpackages__",
    ],
)

cc_library(
    name = "counter_factory",
    srcs = ["counter_factory.cc"],
    hdrs = ["counter_factory.h"],
    visibility = ["//visibility:public"],
    deps = [":counter",
            ":port",
            "//mediapipe/framework/port:integral_types",
            "@com_google_absl//absl/base:core_headers",
            "@com_google_absl//absl/log:absl_check",
            "@com_google_absl//absl/log:absl_log",
            "@com_google_absl//absl/strings",
            "@com_google_absl//absl/synchronization",
            "@com_google_absl//absl/time",
            ],
)

cc_library(
    name = "counter",
    hdrs = ["counter.h"],
    deps = ["//mediapipe/framework/port:integral_types"],
)

cc_library(
    name = "calculator_state",
    srcs = ["calculator_state.cc"],
    hdrs = ["calculator_state.h"],
    visibility = [":mediapipe_internal"],
    deps = [
        ":calculator_cc_proto", # TODO Dont know from where it is coming
        ":counter",
        ":counter_factory",
        ":graph_service"
    ],
)

cc_library(
    name = "calculator_context",
    srcs = ["calculator_context.cc"],
    hdrs = ["calculator_context.h"],
    visibility = [":mediapipe_internal"],
    deps = [
        ":calculator_state",
    ],
)

cc_library(
    name = "calculator_base",
    srcs = ["calculator_base.cc"],
    hdrs = ["calculator_base.h"],
    visibility = [":mediapipe_internal"],
    deps = [":calculator_context"],
)

cc_library(
    name = "calculator_framework",
    hdrs = ["calculator_framework.h"],
    visibility = ["//visibility:public"],
    deps = [
    ":calculator_base",
    ],
)