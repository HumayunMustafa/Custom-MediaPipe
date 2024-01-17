"""Provide build macros for mediapipe
"""
load("@tensorflow//tensorflow/lite/core/shims:cc_library_with_tflite.bzl","cc_library_with_tflite")
load("//mediapipe/framework:transitive_protos.bzl","transitive_protos")
load("//mediapipe/framework/deps:descriptor_set.bzl","direct_descriptor_set","transitive_descriptor_set")