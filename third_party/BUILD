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
#

load("@bazel_skylib//:bzl_library.bzl", "bzl_library")
load("@rules_foreign_cc//foreign_cc:cmake.bzl", "cmake")

licenses(["notice"])  # Apache License 2.0

package(default_visibility = ["//visibility:public"])

exports_files(["LICENSE"])

cc_library(
    name = "glog",
    visibility = ["//visibility:public"],
    deps = select({
        "//mediapipe:android_x86": [
            "@com_github_glog_glog_no_gflags//:glog",
        ],
        "//mediapipe:android_x86_64": [
            "@com_github_glog_glog_no_gflags//:glog",
        ],
        "//mediapipe:android_arm": [
            "@com_github_glog_glog_no_gflags//:glog",
        ],
        "//mediapipe:android_arm64": [
            "@com_github_glog_glog_no_gflags//:glog",
        ],
        "//mediapipe:ios": [
            "@com_github_glog_glog_no_gflags//:glog",
        ],
        "//mediapipe:macos": [
            "@com_github_glog_glog//:glog",
        ],
        "//mediapipe:windows": [
            "@com_github_glog_glog_windows//:glog",
        ],
        "//conditions:default": [
            "@com_github_glog_glog//:glog",
        ],
    }),
)