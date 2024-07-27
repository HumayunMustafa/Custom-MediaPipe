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

load("@bazel_skylib//lib:selects.bzl", "selects")  # buildifier: disable=out-of-order-load
load("//mediapipe/gpu:metal.bzl", "metal_library")
load("@build_bazel_rules_apple//apple:ios.bzl", "ios_unit_test")
load("//mediapipe/framework/port:build_config.bzl", "mediapipe_proto_library")  # buildifier: disable=out-of-order-load
load("//mediapipe/framework:mediapipe_cc_test.bzl", "mediapipe_cc_test")  # buildifier: disable=out-of-order-load
load("//mediapipe/framework:more_selects.bzl", "more_selects")

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# Disabling GPU support is sometimes useful on desktop Linux because SwiftShader can
# interfere with desktop GL. b/73494271
config_setting(
    name = "disable_gpu",
    define_values = {
        "MEDIAPIPE_DISABLE_GPU": "1",
    },
    visibility = ["//visibility:public"],
)

