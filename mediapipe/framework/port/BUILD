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
# Description:
#  Port of various libraries and utilities.

licenses(["notice"])

package(
    default_visibility = ["//visibility:public"],
    features = ["-parse_headers"],
)

cc_library(
    name = "integral_types",
    hdrs = ["integral_types.h"],
)

# Enable Halide when defining MEDIAPIPE_ENABLE_HALIDE to 1 in bazel command.
# This will  automatically disable opencv, i.e. will set MEDIAPIPE_DISABLE_OPENCV to 1.
# Note that this only applies to a select few calculators/framework components currently.
# TODO: Improve this. This only sets MEDIAPIPE_DISABLE_OPENCV as a "defines" Make value,
# not as a bazel "--define" variable, which has effects in C++ code but not in select() statements.
config_setting(
    name = "enable_halide",
    define_values = {
        "MEDIAPIPE_ENABLE_HALIDE": "1",
    },
)