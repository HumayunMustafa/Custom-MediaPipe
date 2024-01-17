"""Outputs a FileDescriptorSet with all transitive dependencies.
   Copied from tools/build_defs/proto/descriptor_set.bzl.
"""

TransitiveDescriptorInfo=provider(
    "The transitive descriptors from a set of protos.",
    fields=["descriptors"],
)

DirectDescriptorInfo=provider(
    "The direct descriptors from a set of protos.",
    fields = ["descriptors"],
)

def calculate_transitive_descriptor_set(actions,deps,output):
    """Calculates the transitive dependencies of the deps.

    Args:
      actions: the actions (typically ctx.actions) used to run commands
      deps: the deps to get the transitive dependencies of
      output: the output file the data will be written to

    Returns:
      The same output file passed as the input arg, for convenience.
    """