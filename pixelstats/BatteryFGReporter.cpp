/*
 * Copyright (C) 2024 The Android Open Source Project
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

#define LOG_TAG "pixelstats: BatteryFGReporter"

#include <log/log.h>
#include <time.h>
#include <utils/Timers.h>
#include <cinttypes>
#include <cmath>

#include <android-base/file.h>
#include <pixelstats/BatteryFGReporter.h>
#include <pixelstats/StatsHelper.h>
#include <hardware/google/pixel/pixelstats/pixelatoms.pb.h>

namespace android {
namespace hardware {
namespace google {
namespace pixel {

using aidl::android::frameworks::stats::VendorAtom;
using aidl::android::frameworks::stats::VendorAtomValue;
using android::base::ReadFileToString;
using android::hardware::google::pixel::PixelAtoms::BatteryFuelGaugeReported;


BatteryFGReporter::BatteryFGReporter() {}

int64_t BatteryFGReporter::getTimeSecs() {
    return nanoseconds_to_seconds(systemTime(SYSTEM_TIME_BOOTTIME));
}

void BatteryFGReporter::reportFGEvent(const std::shared_ptr<IStats> &stats_client,
                                      struct BatteryFGPipeline &data) {
    // Load values array
    std::vector<VendorAtomValue> values(5);
    std::vector<int32_t> fg_data_vec;
    BatteryFuelGaugeReported report_msg;

    if (data.event >= kNumMaxEvents) {
        ALOGE("Exceed max number of events, expected=%d, event=%d",
               kNumMaxEvents, data.event);
        return;
    }

    /* save time when trigger, calculate duration when clear */
    if (data.state == 1 && ab_trigger_time_[data.event] == 0) {
        ab_trigger_time_[data.event] = getTimeSecs();
    } else {
        data.duration = getTimeSecs() - ab_trigger_time_[data.event];
        ab_trigger_time_[data.event] = 0;
    }

    ALOGD("reportEvent: event=%d, state=%d, duration=%d, addr01=%04X, data01=%04X, "
          "addr02=%04X, data02=%04X, addr03=%04X, data03=%04X, addr04=%04X, data04=%04X, "
          "addr05=%04X, data05=%04X, addr06=%04X, data06=%04X, addr07=%04X, data07=%04X, "
          "addr08=%04X, data08=%04X, addr09=%04X, data09=%04X, addr10=%04X, data10=%04X, "
          "addr11=%04X, data11=%04X, addr12=%04X, data12=%04X, addr13=%04X, data13=%04X, "
          "addr14=%04X, data14=%04X, addr15=%04X, data15=%04X, addr16=%04X, data16=%04X",
          data.event, data.state, data.duration, data.addr01, data.data01,
          data.addr02, data.data02, data.addr03, data.data03, data.addr04, data.data04,
          data.addr05, data.data05, data.addr06, data.data06, data.addr07, data.data07,
          data.addr08, data.data08, data.addr09, data.data09, data.addr10, data.data10,
          data.addr11, data.data11, data.addr12, data.data12, data.addr13, data.data13,
          data.addr14, data.data14, data.addr15, data.data15, data.addr16, data.data16);


    /*
     * state=0 -> untrigger, state=1 -> trigger
     * Since atom enum reserves unknown value at 0, offset by 1 here
     * state=1-> untrigger, state=2 -> trigger
     */
    data.state += 1;

    report_msg.set_unix_time_sec(data.duration);
    report_msg.set_data_type(EvtFGAbnormalEvent);
    report_msg.set_data_event(data.event);
    report_msg.set_fg_index(BatteryFuelGaugeReported::PRIMARY);
    report_msg.add_fg_data(data.state);
    report_msg.add_fg_data(data.addr01);
    report_msg.add_fg_data(data.data01);
    report_msg.add_fg_data(data.addr02);
    report_msg.add_fg_data(data.data02);
    report_msg.add_fg_data(data.addr03);
    report_msg.add_fg_data(data.data03);
    report_msg.add_fg_data(data.addr04);
    report_msg.add_fg_data(data.data04);
    report_msg.add_fg_data(data.addr05);
    report_msg.add_fg_data(data.data05);
    report_msg.add_fg_data(data.addr06);
    report_msg.add_fg_data(data.data06);
    report_msg.add_fg_data(data.addr07);
    report_msg.add_fg_data(data.data07);
    report_msg.add_fg_data(data.addr08);
    report_msg.add_fg_data(data.data08);
    report_msg.add_fg_data(data.addr09);
    report_msg.add_fg_data(data.data09);
    report_msg.add_fg_data(data.addr10);
    report_msg.add_fg_data(data.data10);
    report_msg.add_fg_data(data.addr11);
    report_msg.add_fg_data(data.data11);
    report_msg.add_fg_data(data.addr12);
    report_msg.add_fg_data(data.data12);
    report_msg.add_fg_data(data.addr13);
    report_msg.add_fg_data(data.data13);
    report_msg.add_fg_data(data.addr14);
    report_msg.add_fg_data(data.data14);
    report_msg.add_fg_data(data.addr15);
    report_msg.add_fg_data(data.data15);
    report_msg.add_fg_data(data.addr16);
    report_msg.add_fg_data(data.data16);

    values[0].set<VendorAtomValue::longValue>(report_msg.unix_time_sec());
    values[1].set<VendorAtomValue::intValue>(report_msg.data_type());
    values[2].set<VendorAtomValue::intValue>(report_msg.data_event());
    values[3].set<VendorAtomValue::intValue>(report_msg.fg_index());

    for (int32_t val : report_msg.fg_data()) {
        fg_data_vec.push_back(val);
    }
    values[4].set<VendorAtomValue::repeatedIntValue>(fg_data_vec);

    VendorAtom event = {.reverseDomainName = "",
                        .atomId = PixelAtoms::Atom::kBatteryFuelGaugeReported,
                        .values = std::move(values)};
    reportVendorAtom(stats_client, event);
}

void BatteryFGReporter::checkAndReportFGAbnormality(const std::shared_ptr<IStats> &stats_client,
                                                    const std::vector<std::string> &paths) {
    std::string path;
    struct timespec boot_time;
    std::vector<std::vector<uint32_t>> events;

    if (paths.empty())
        return;

    for (int i = 0; i < paths.size(); i++) {
        if (fileExists(paths[i])) {
            path = paths[i];
            break;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &boot_time);
    readLogbuffer(path, kNumFGPipelineFields, EvtFGAbnormalEvent, FormatOnlyVal, last_ab_check_,
                  events);
    for (int seq = 0; seq < events.size(); seq++) {
        if (events[seq].size() == kNumFGPipelineFields) {
            struct BatteryFGPipeline data;
            std::copy(events[seq].begin(), events[seq].end(), (int32_t *)&data);
            reportFGEvent(stats_client, data);
        } else {
            ALOGE("Not support %zu fields for FG abnormal event", events[seq].size());
        }
    }

    last_ab_check_ = (unsigned int)boot_time.tv_sec;
}

}  // namespace pixel
}  // namespace google
}  // namespace hardware
}  // namespace android
