/*
 * Copyright (C) 2018-2020 ARM Limited. All rights reserved.
 *
 * Copyright 2016 The Android Open Source Project
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

#include "GrallocMapper.h"
#include "hidl_common/BufferDescriptor.h"
#include "allocator/mali_gralloc_ion.h"


namespace arm {
namespace mapper {

using android::hardware::graphics::mapper::V3_0::Error;
using android::hardware::graphics::mapper::V3_0::BufferDescriptor;
using android::hardware::graphics::mapper::V3_0::YCbCrLayout;
using android::hardware::graphics::mapper::V3_0::IMapper;
using android::hardware::Return;
using android::hardware::hidl_handle;
using android::hardware::Void;

GrallocMapper::GrallocMapper()
{
}

GrallocMapper::~GrallocMapper()
{
	mali_gralloc_ion_close();
}

Return<void> GrallocMapper::createDescriptor(
             const BufferDescriptorInfo& descriptorInfo,
             createDescriptor_cb hidl_cb)
{
	if (common::validateDescriptorInfo(descriptorInfo))
	{
		hidl_cb(Error::NONE, common::grallocEncodeBufferDescriptor<uint32_t>(descriptorInfo));
	}
	else
	{
		MALI_GRALLOC_LOGE("Invalid attributes to create descriptor for Mapper 3.0");
		hidl_cb(Error::BAD_VALUE, BufferDescriptor());
	}

	return Void();
}

Return<void> GrallocMapper::importBuffer(const hidl_handle& rawHandle,
                                         importBuffer_cb hidl_cb)
{
	common::importBuffer(rawHandle, hidl_cb);
	return Void();
}

Return<Error> GrallocMapper::freeBuffer(void* buffer)
{
	return common::freeBuffer(buffer);
}

Return<void> GrallocMapper::lock(void* buffer, uint64_t cpuUsage,
                                 const IMapper::Rect& accessRegion,
                                 const hidl_handle& acquireFence,
                                 lock_cb hidl_cb)
{
	common::lock(buffer, cpuUsage, accessRegion, acquireFence, hidl_cb);
	return Void();
}

Return<void>
GrallocMapper::lockYCbCr(
	void* buffer,
	uint64_t cpuUsage,
	const IMapper::Rect& accessRegion,
	const hidl_handle& acquireFence,
	lockYCbCr_cb hidl_cb)
{
	common::lockYCbCr(buffer, cpuUsage, accessRegion, acquireFence, hidl_cb);
	return Void();
}

Return<void> GrallocMapper::unlock(void* buffer, unlock_cb hidl_cb)
{
	common::unlock(buffer, hidl_cb);
	return Void();
}

Return<Error> GrallocMapper::validateBufferSize(void* buffer,
                                                const BufferDescriptorInfo& descriptorInfo,
                                                uint32_t in_stride)
{
	/* All Gralloc allocated buffers must be conform to local descriptor validation */
	if (!common::validateDescriptorInfo<BufferDescriptorInfo>(descriptorInfo))
	{
		MALI_GRALLOC_LOGE("Invalid descriptor attributes for validating buffer size");
		return Error::BAD_VALUE;
	}
	return common::validateBufferSize(buffer, descriptorInfo, in_stride);
}

Return<void> GrallocMapper::getTransportSize(void* buffer, getTransportSize_cb hidl_cb)
{
	common::getTransportSize(buffer, hidl_cb);
	return Void();
}

Return<void> GrallocMapper::isSupported(const BufferDescriptorInfo& description,
                                        isSupported_cb hidl_cb)
{
	if (!common::validateDescriptorInfo<BufferDescriptorInfo>(description))
	{
		MALI_GRALLOC_LOGE("Invalid descriptor attributes for validating buffer size");
		hidl_cb(Error::BAD_VALUE, false);
	}
	common::isSupported(description, hidl_cb);
	return Void();
}

} // namespace mapper
} // namespace arm

extern "C" IMapper* HIDL_FETCH_IMapper(const char* /* name */)
{
	MALI_GRALLOC_LOGV("Arm Module IMapper 3.0 , pid = %d ppid = %d ", getpid(), getppid());
	return new arm::mapper::GrallocMapper();
}