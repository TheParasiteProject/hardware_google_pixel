/*
 * Copyright (C) 2019 The Android Open Source Project
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
#ifndef ANDROID_HARDWARE_VIBRATOR_TEST_MOCKS_H
#define ANDROID_HARDWARE_VIBRATOR_TEST_MOCKS_H

#include <aidl/android/hardware/vibrator/BnVibratorCallback.h>

#include "Vibrator.h"

class MockApi : public ::aidl::android::hardware::vibrator::Vibrator::HwApi {
  public:
    MOCK_METHOD0(destructor, void());
    MOCK_METHOD1(setF0, bool(uint32_t value));
    MOCK_METHOD1(setF0Offset, bool(uint32_t value));
    MOCK_METHOD1(setRedc, bool(uint32_t value));
    MOCK_METHOD1(setQ, bool(uint32_t value));
    MOCK_METHOD1(setActivate, bool(bool value));
    MOCK_METHOD1(setDuration, bool(uint32_t value));
    MOCK_METHOD1(getEffectCount, bool(uint32_t *value));
    MOCK_METHOD1(getEffectDuration, bool(uint32_t *value));
    MOCK_METHOD1(setEffectIndex, bool(uint32_t value));
    MOCK_METHOD1(setEffectQueue, bool(std::string value));
    MOCK_METHOD0(getContextScale, uint32_t());
    MOCK_METHOD0(getContextEnable, bool());
    MOCK_METHOD0(getContextSettlingTime, uint32_t());
    MOCK_METHOD0(getContextCooldownTime, uint32_t());
    MOCK_METHOD0(getContextFadeEnable, bool());
    MOCK_METHOD0(hasEffectScale, bool());
    MOCK_METHOD1(setEffectScale, bool(uint32_t value));
    MOCK_METHOD1(setGlobalScale, bool(uint32_t value));
    MOCK_METHOD1(setState, bool(bool value));
    MOCK_METHOD0(hasAspEnable, bool());
    MOCK_METHOD1(getAspEnable, bool(bool *value));
    MOCK_METHOD1(setAspEnable, bool(bool value));
    MOCK_METHOD1(setGpioFallIndex, bool(uint32_t value));
    MOCK_METHOD1(setGpioFallScale, bool(uint32_t value));
    MOCK_METHOD1(setGpioRiseIndex, bool(uint32_t value));
    MOCK_METHOD1(setGpioRiseScale, bool(uint32_t value));
    MOCK_METHOD2(pollVibeState, bool(uint32_t value, int32_t timeoutMs));
    MOCK_METHOD1(setClabEnable, bool(bool value));
    MOCK_METHOD1(getAvailablePwleSegments, bool(uint32_t *value));
    MOCK_METHOD0(hasPwle, bool());
    MOCK_METHOD1(setPwle, bool(std::string value));
    MOCK_METHOD1(setPwleRampDown, bool(uint32_t value));
    MOCK_METHOD1(debug, void(int fd));

    ~MockApi() override { destructor(); };
};

class MockCal : public ::aidl::android::hardware::vibrator::Vibrator::HwCal {
  public:
    MOCK_METHOD0(destructor, void());
    MOCK_METHOD1(getVersion, bool(uint32_t *value));
    MOCK_METHOD1(getF0, bool(uint32_t *value));
    MOCK_METHOD1(getRedc, bool(uint32_t *value));
    MOCK_METHOD1(getQ, bool(uint32_t *value));
    MOCK_METHOD1(getLongFrequencyShift, bool(int32_t *value));
    MOCK_METHOD1(getVolLevels, bool(std::array<uint32_t, 6> *value));
    MOCK_METHOD1(getTickVolLevels, bool(std::array<uint32_t, 2> *value));
    MOCK_METHOD1(getClickVolLevels, bool(std::array<uint32_t, 2> *value));
    MOCK_METHOD1(getLongVolLevels, bool(std::array<uint32_t, 2> *value));
    MOCK_METHOD0(isChirpEnabled, bool());
    MOCK_METHOD1(getDeviceMass, bool(float *value));
    MOCK_METHOD1(getLocCoeff, bool(float *value));
    MOCK_METHOD1(debug, void(int fd));

    ~MockCal() override { destructor(); };
};

class MockStats : public ::aidl::android::hardware::vibrator::Vibrator::StatsApi {
  public:
    MOCK_METHOD0(destructor, void());
    MOCK_METHOD1(logPrimitive, bool(uint16_t effectIndex));
    MOCK_METHOD2(logWaveform, bool(uint16_t effectIndex, int32_t duration));
    MOCK_METHOD1(logError, bool(uint16_t errorIndex));
    MOCK_METHOD1(logLatencyStart, bool(uint16_t latencyIndex));
    MOCK_METHOD0(logLatencyEnd, bool());
    MOCK_METHOD1(debug, void(int fd));

    ~MockStats() override { destructor(); };
};

class MockVibratorCallback : public aidl::android::hardware::vibrator::BnVibratorCallback {
  public:
    MOCK_METHOD(ndk::ScopedAStatus, onComplete, ());
};

#endif  // ANDROID_HARDWARE_VIBRATOR_TEST_MOCKS_H
