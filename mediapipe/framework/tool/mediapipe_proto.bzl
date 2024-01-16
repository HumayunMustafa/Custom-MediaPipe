"""Build macros for mediapipe proto buffers
"""

load("@com_google_protobuf//:protobuf.bzl","cc_proto_library","py_proto_library")
load("@rules_proto//proto:defs.bzl","proto_library")
load("@rules_proto_grpc//js:defs.bzl","js_proto_library")
load("//mediapipe/framework/tool:mediapipe_graph.bzl","mediapipe_options_library")
load("//mediapipe//framework/tool:mediapipe_proto_allowlist.bzl","rewrite_target_list")