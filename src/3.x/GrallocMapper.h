/*
 * Copyright (C) 2018-2020 ARM Limited. All rights reserved.
 *
 * Copyright 2016 The Android Open Source Project
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
#ifndef ANDROID_HARDWARE_GRAPHICS_MAPPER_V3_x_GRALLOC_MAPPER_H
#define ANDROID_HARDWARE_GRAPHICS_MAPPER_V3_x_GRALLOC_MAPPER_H

#include <android/hardware/graphics/mapper/3.0/IMapper.h>

#include "hidl_common/Mapper.h"

namespace arm {
namespace mapper {

using android::hardware::graphics::mapper::V3_0::Error;
using android::hardware::graphics::mapper::V3_0::BufferDescriptor;
using android::hardware::graphics::mapper::V3_0::YCbCrLayout;
using android::hardware::graphics::mapper::V3_0::IMapper;
using android::hardware::Return;
using android::hardware::hidl_handle;

class GrallocMapper : public IMapper
{
public:

	/**
	 * IMapper constructor. All the state information required for the Gralloc
	 * private module is populated in its default constructor. Gralloc 3.x specific
	 * state information can be populated here.
	 */
	GrallocMapper();

	/*
	 * IMapper destructor. All the resources aquired for Gralloc private module
	 * (in the IMapper context) are released
	 */
	~GrallocMapper();

	/* Override the public IMapper 3.0 interface */
	Return<void> createDescriptor(const BufferDescriptorInfo& descriptorInfo,
	                              createDescriptor_cb hidl_cb) override;

	Return<void> importBuffer(const hidl_handle& rawHandle,
	                          importBuffer_cb hidl_cb) override;

	Return<Error> freeBuffer(void* buffer) override;

	Return<void> lock(void* buffer, uint64_t cpuUsage,
	                  const IMapper::Rect& accessRegion,
	                  const hidl_handle& acquireFence,
	                  lock_cb hidl_cb) override;

	Return<void> lockYCbCr(void* buffer, uint64_t cpuUsage,
	                       const IMapper::Rect& accessRegion,
	                       const hidl_handle& acquireFence,
	                       lockYCbCr_cb hidl_cb) override;

	Return<void> unlock(void* buffer, unlock_cb hidl_cb) override;

	Return<Error> validateBufferSize(void* buffer,
	                                 const BufferDescriptorInfo& descriptorInfo,
	                                 uint32_t stride) override;

	Return<void> getTransportSize(void* buffer, getTransportSize_cb _hidl_cb) override;

	Return<void> isSupported(const BufferDescriptorInfo& description,
	                         isSupported_cb _hidl_cb) override;
};

} // namespace mapper
} // namespace arm
#endif // ANDROID_HARDWARE_GRAPHICS_MAPPER_V3_x_GRALLOC_MAPPER_H
