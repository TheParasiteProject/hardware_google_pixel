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
#pragma once

#include "HardwareBase.h"
#include "Vibrator.h"

namespace aidl {
namespace android {
namespace hardware {
namespace vibrator {

class HwApi : public Vibrator::HwApi, private HwApiBase {
  public:
    HwApi() {
        open("device/f0_stored", &mF0);
        open("device/f0_offset", &mF0Offset);
        open("device/redc_stored", &mRedc);
        open("device/q_stored", &mQ);
        open("activate", &mActivate);
        open("duration", &mDuration);
        open("state", &mState);
        open("device/cp_trigger_duration", &mEffectDuration);
        open("device/cp_trigger_index", &mEffectIndex);
        open("device/cp_trigger_queue", &mEffectQueue);
        open("device/cp_dig_scale", &mEffectScale);
        open("device/dig_scale", &mGlobalScale);
        open("device/asp_enable", &mAspEnable);
        open("device/gpio1_fall_index", &mGpioFallIndex);
        open("device/gpio1_fall_dig_scale", &mGpioFallScale);
        open("device/gpio1_rise_index", &mGpioRiseIndex);
        open("device/gpio1_rise_dig_scale", &mGpioRiseScale);
        open("device/vibe_state", &mVibeState);
        open("device/num_waves", &mEffectCount);
        open("device/clab_enable", &mClabEnable);
        open("device/available_pwle_segments", &mAvailablePwleSegments);
        open("device/pwle", &mPwle);
        open("device/pwle_ramp_down", &mPwleRampDown);
    }

    bool setF0(uint32_t value) override { return set(value, &mF0); }
    bool setF0Offset(uint32_t value) override { return set(value, &mF0Offset); }
    bool setRedc(uint32_t value) override { return set(value, &mRedc); }
    bool setQ(uint32_t value) override { return set(value, &mQ); }
    bool setActivate(bool value) override { return set(value, &mActivate); }
    bool setDuration(uint32_t value) override { return set(value, &mDuration); }
    bool getEffectCount(uint32_t *value) override { return get(value, &mEffectCount); }
    bool getEffectDuration(uint32_t *value) override { return get(value, &mEffectDuration); }
    bool setEffectIndex(uint32_t value) override { return set(value, &mEffectIndex); }
    bool setEffectQueue(std::string value) override { return set(value, &mEffectQueue); }
    bool hasEffectScale() override { return has(mEffectScale); }
    uint32_t getContextScale() override {
        return utils::getProperty("persist.vendor.vibrator.hal.context.scale", 100);
    }
    bool getContextEnable() override {
        return utils::getProperty("persist.vendor.vibrator.hal.context.enable", false);
    }
    uint32_t getContextSettlingTime() override {
        return utils::getProperty("persist.vendor.vibrator.hal.context.settlingtime", 3000);
    }
    uint32_t getContextCooldownTime() override {
        return utils::getProperty("persist.vendor.vibrator.hal.context.cooldowntime", 1000);
    }
    bool getContextFadeEnable() override {
        return utils::getProperty("persist.vendor.vibrator.hal.context.fade", false);
    }
    bool setEffectScale(uint32_t value) override { return set(value, &mEffectScale); }
    bool setGlobalScale(uint32_t value) override { return set(value, &mGlobalScale); }
    bool setState(bool value) override { return set(value, &mState); }
    bool hasAspEnable() override { return has(mAspEnable); }
    bool getAspEnable(bool *value) override { return get(value, &mAspEnable); }
    bool setAspEnable(bool value) override { return set(value, &mAspEnable); }
    bool setGpioFallIndex(uint32_t value) override { return set(value, &mGpioFallIndex); }
    bool setGpioFallScale(uint32_t value) override { return set(value, &mGpioFallScale); }
    bool setGpioRiseIndex(uint32_t value) override { return set(value, &mGpioRiseIndex); }
    bool setGpioRiseScale(uint32_t value) override { return set(value, &mGpioRiseScale); }
    bool pollVibeState(uint32_t value, int32_t timeoutMs) override {
        return poll(value, &mVibeState, timeoutMs);
    }
    bool setClabEnable(bool value) override { return set(value, &mClabEnable); }
    bool getAvailablePwleSegments(uint32_t *value) override {
        return get(value, &mAvailablePwleSegments);
    }
    bool hasPwle() override { return has(mPwle); }
    bool setPwle(std::string value) override { return set(value, &mPwle); }
    bool setPwleRampDown(uint32_t value) override { return set(value, &mPwleRampDown); }
    void debug(int fd) override { HwApiBase::debug(fd); }

  private:
    std::ofstream mF0;
    std::ofstream mF0Offset;
    std::ofstream mRedc;
    std::ofstream mQ;
    std::ofstream mActivate;
    std::ofstream mDuration;
    std::ifstream mEffectCount;
    std::ifstream mEffectDuration;
    std::ofstream mEffectIndex;
    std::ofstream mEffectQueue;
    std::ofstream mEffectScale;
    std::ofstream mGlobalScale;
    std::ofstream mState;
    std::fstream mAspEnable;
    std::ofstream mGpioFallIndex;
    std::ofstream mGpioFallScale;
    std::ofstream mGpioRiseIndex;
    std::ofstream mGpioRiseScale;
    std::ifstream mVibeState;
    std::ofstream mClabEnable;
    std::ifstream mAvailablePwleSegments;
    std::ofstream mPwle;
    std::ofstream mPwleRampDown;
};

class HwCal : public Vibrator::HwCal, private HwCalBase {
  private:
    static constexpr char VERSION[] = "version";
    static constexpr char F0_CONFIG[] = "f0_measured";
    static constexpr char REDC_CONFIG[] = "redc_measured";
    static constexpr char Q_CONFIG[] = "q_measured";
    static constexpr char Q_INDEX[] = "q_index";
    static constexpr char VOLTAGES_CONFIG[] = "v_levels";
    static constexpr char TICK_VOLTAGES_CONFIG[] = "v_tick";
    static constexpr char CLICK_VOLTAGES_CONFIG[] = "v_click";
    static constexpr char LONG_VOLTAGES_CONFIG[] = "v_long";

    static constexpr uint32_t Q_FLOAT_TO_FIXED = 1 << 16;
    static constexpr float Q_INDEX_TO_FLOAT = 1.5f;
    static constexpr uint32_t Q_INDEX_TO_FIXED = Q_INDEX_TO_FLOAT * Q_FLOAT_TO_FIXED;
    static constexpr uint32_t Q_INDEX_OFFSET = 2.0f * Q_FLOAT_TO_FIXED;

    static constexpr uint32_t VERSION_DEFAULT = 1;
    static constexpr int32_t DEFAULT_FREQUENCY_SHIFT = 0;
    static constexpr float DEFAULT_DEVICE_MASS = 0.21;
    static constexpr float DEFAULT_LOC_COEFF = 0.5;
    static constexpr uint32_t Q_DEFAULT = 15.5 * Q_FLOAT_TO_FIXED;
    static constexpr std::array<uint32_t, 6> V_LEVELS_DEFAULT = {60, 70, 80, 90, 100, 76};
    static constexpr std::array<uint32_t, 2> V_TICK_DEFAULT = {10, 70};
    static constexpr std::array<uint32_t, 2> V_CTICK_DEFAULT = {10, 70};
    static constexpr std::array<uint32_t, 2> V_LONG_DEFAULT = {10, 70};

  public:
    HwCal() {}

    bool getVersion(uint32_t *value) override {
        if (getPersist(VERSION, value)) {
            return true;
        }
        *value = VERSION_DEFAULT;
        return true;
    }
    bool getLongFrequencyShift(int32_t *value) override {
        return getProperty("long.frequency.shift", value, DEFAULT_FREQUENCY_SHIFT);
    }
    bool getDeviceMass(float *value) override {
        return getProperty("device.mass", value, DEFAULT_DEVICE_MASS);
    }
    bool getLocCoeff(float *value) override {
        return getProperty("loc.coeff", value, DEFAULT_LOC_COEFF);
    }
    bool getF0(uint32_t *value) override { return getPersist(F0_CONFIG, value); }
    bool getRedc(uint32_t *value) override { return getPersist(REDC_CONFIG, value); }
    bool getQ(uint32_t *value) override {
        if (getPersist(Q_CONFIG, value)) {
            return true;
        }
        if (getPersist(Q_INDEX, value)) {
            *value = *value * Q_INDEX_TO_FIXED + Q_INDEX_OFFSET;
            return true;
        }
        *value = Q_DEFAULT;
        return true;
    }
    bool getVolLevels(std::array<uint32_t, 6> *value) override {
        if (getPersist(VOLTAGES_CONFIG, value)) {
            return true;
        }
        *value = V_LEVELS_DEFAULT;
        return true;
    }
    bool getTickVolLevels(std::array<uint32_t, 2> *value) override {
        if (getPersist(TICK_VOLTAGES_CONFIG, value)) {
            return true;
        }
        *value = V_TICK_DEFAULT;
        return true;
    }
    bool getClickVolLevels(std::array<uint32_t, 2> *value) override {
        if (getPersist(CLICK_VOLTAGES_CONFIG, value)) {
            return true;
        }
        *value = V_CTICK_DEFAULT;
        return true;
    }
    bool getLongVolLevels(std::array<uint32_t, 2> *value) override {
        if (getPersist(LONG_VOLTAGES_CONFIG, value)) {
            return true;
        }
        *value = V_LONG_DEFAULT;
        return true;
    }
    bool isChirpEnabled() override {
        return utils::getProperty("persist.vendor.vibrator.hal.chirp.enabled", false);
    }
    void debug(int fd) override { HwCalBase::debug(fd); }
};

}  // namespace vibrator
}  // namespace hardware
}  // namespace android
}  // namespace aidl
