// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CUSTOM_MEDIAPIPE_COUNTER_FACTORY_H
#define CUSTOM_MEDIAPIPE_COUNTER_FACTORY_H

#include <algorithm>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/synchronization/mutex.h"
#include "absl/time/time.h"
#include "mediapipe/framework/counter.h"
#include "mediapipe/framework/port.h"
#include "mediapipe/framework/port/map_util s.h"

namespace mediapipe {
    // Holds a map of counter names to counter unique_ptrs.
    // This class is thread safe.
    class CounterSet {
    public:
        CounterSet();

        // In builds with streamz export enabled, this will synchronously export
        // the final counter values.
        ~CounterSet();

        // Prints the values of all the counters.
        // A call to PublishCounters will reset all counters.
        void PrintCounters();

        // Publishes the vales of all the counters for monitoring and resets
        // all internal counters.
        void PublishCounter();

        // Adds a counter of the given type by constructing the counter in place.
        // Returns a pointer to the new counter or if the counter already exists
        // to the existing pointer.
    };
}

#endif //CUSTOM_MEDIAPIPE_COUNTER_FACTORY_H
