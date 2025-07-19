/*
 * Copyright 2025 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <gmock/gmock.h>
#include <powerhal_flags.h>

namespace aidl::google::hardware::power::mock::pixel {

class MockPowerHalFlagsProviderInterface : public powerhal::flags::flag_provider_interface {
  public:
    MOCK_METHOD(bool, test_flag, (), ());
    MOCK_METHOD(bool, gpu_load_up_for_blurs, (), ());
    MOCK_METHOD(bool, initial_hboost_severe, (), ());
};

}  // namespace aidl::google::hardware::power::mock::pixel
