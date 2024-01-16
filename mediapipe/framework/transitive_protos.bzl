"""Extract a cc_library compatible dependency with only top level proto rules"""

ProtoLibsInfo=provider(fields=["targets","out"])

def _get_proto_rules(deps,proto_rules=None):
    useful_deps=[dep for dep in deps if hasattr(dep,"proto_rules")]
    if proto_rules==None:
        proto_rules=depset()
    proto_rules=depset(
        transitive=[proto_rules] + [dep.proto_rules for dep in useful_deps],
    )
    return proto_rules