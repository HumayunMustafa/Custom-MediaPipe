//
// Created by MSD on 27/07/2024.
//

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

#include "mediaipipe/framework/counter_factory.h"
#include <vector>
#include "absl/log/absl_log.h"
#include "absl/synchronization/mutex.h"
#include "absl/strings/string_view.h"

namespace mediapipe {
namespace {
    // Counter implementation when we're not using Flume.
    // TODO: Consider using Dax atomic counters instead of this.
    // This class is thread safe.
class BasicCounter : public Counter {
  public:
    explicit BasicCounter(const std::string& name) : value_(0) {}

    void Increment() ABSL_LOCKS_EXCLUDED(mu_) override{
      absl::WriterMutexLock lock(&mu_);
      ++value_;
    }
}
}
}
