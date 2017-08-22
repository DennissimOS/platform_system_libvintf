/*
 * Copyright (C) 2017 The Android Open Source Project
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

#ifndef ANDROID_VINTF_MATRIX_KERNEL_H
#define ANDROID_VINTF_MATRIX_KERNEL_H

#include <string>
#include <vector>
#include <utility>

#include "KernelConfigTypedValue.h"
#include "Version.h"

namespace android {
namespace vintf {

struct KernelConfigKey : public std::string {
    KernelConfigKey() : std::string() {}
    KernelConfigKey(const std::string &other) : std::string(other) {}
    KernelConfigKey(std::string &&other) : std::string(std::forward<std::string>(other)) {}
};

using KernelConfig = std::pair<KernelConfigKey, KernelConfigTypedValue>;

// A kernel entry to a compatibility matrix
struct MatrixKernel {

    MatrixKernel() {}
    MatrixKernel(KernelVersion &&minLts, std::vector<KernelConfig> &&configs)
            : mMinLts(std::move(minLts)), mConfigs(std::move(configs)) {}

    bool operator==(const MatrixKernel &other) const;

    inline const KernelVersion &minLts() const { return mMinLts; }

    // Return an iterable on all kernel configs. Use it as follows:
    // for (const KernelConfig &config : kernel.configs()) {...}
    const std::vector<KernelConfig> &configs() const { return mConfigs; }

    // Return an iterable on all kernel config conditions. Use it as follows:
    // for (const KernelConfig &config : kernel.conditions()) {...}
    const std::vector<KernelConfig>& conditions() const { return mConditions; }

   private:
    friend struct MatrixKernelConverter;
    friend struct MatrixKernelConditionsConverter;
    friend class AssembleVintf;

    KernelVersion mMinLts;
    std::vector<KernelConfig> mConfigs;
    std::vector<KernelConfig> mConditions;
};

} // namespace vintf
} // namespace android

#endif // ANDROID_VINTF_MATRIX_KERNEL_H
