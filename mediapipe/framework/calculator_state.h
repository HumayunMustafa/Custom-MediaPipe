//
// Created by MSD on 27/07/2024.
//

#ifndef CUSTOM_MEDIAPIPE_CALCULATOR_STATE_H
#define CUSTOM_MEDIAPIPE_CALCULATOR_STATE_H

#include <map>
#include <memory>
#include <string>

// TODO: Move protos in another CL after the C++ code migration.
#include "absl/base/macros.h"
#include "absl/status/status.h"
#include "mediapipe/framework/calculator.pb.h"
#include "mediapipe/framework/counter.h"
#include "mediapipe/framework/counter_factory.h"
#include "mediapipe/framework/graph_service.h"
#include "mediapipe/framework/graph_service_manager.h"
#include "mediapipe/framework/packet.h"
#include "mediapipe/framework/packet_set.h"
#include "mediapipe/framework/port.h"
#include "mediapipe/framework/port/any_proto.h"
#include "mediapipe/framework/resources.h"
#include "mediapipe/framework/tool/options_map.h"

namespace mediapipe {
 class ProfilingContext;
}

#endif //CUSTOM_MEDIAPIPE_CALCULATOR_STATE_H
