/*******************************************************************************
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#ifndef DML_TESTING_MEM_MOVE_WORKLOAD_BUILDER_HPP
#define DML_TESTING_MEM_MOVE_WORKLOAD_BUILDER_HPP

#include <utils/mem_move/workload.hpp>
#include <utils/memory.hpp>
#include <utils/operation.hpp>

namespace dml::testing
{
    template <>
    class WorkloadBuilder<MemMoveOperation>
    {
    public:
        WorkloadBuilder() noexcept:
            transfer_size_(1),
            src_alignment_(1),
            dst_alignment_(1),
            offset_(0),
            swap_(false)
        {
        }

        auto& set_transfer_size(std::uint32_t size) noexcept
        {
            transfer_size_ = size;

            return *this;
        }

        auto& set_src_alignment(std::uint32_t size) noexcept
        {
            src_alignment_ = size;

            return *this;
        }

        auto& set_dst_alignment(std::uint32_t size) noexcept
        {
            dst_alignment_ = size;

            return *this;
        }

        auto& set_offset(std::int32_t offset) noexcept
        {
            offset_ = offset;

            return *this;
        }

        auto& set_swap_regions(bool value) noexcept
        {
            swap_ = value;

            return *this;
        }

        [[nodiscard]] auto build()
        {
            auto src_config =
                RegionConfiguration().set_size(transfer_size_).set_alignment(src_alignment_);
            auto dst_config =
                RegionConfiguration().set_size(transfer_size_).set_alignment(dst_alignment_);

            auto memory = MemoryBuilder()
                              .add_region(swap_ ? src_config : dst_config)
                              .add_region((swap_ ? dst_config : src_config).set_offset(offset_))
                              .build();

            constexpr auto pattern_0 = 0x2u;
            constexpr auto pattern_1 = 0x3u;

            std::fill(memory.get_region(swap_ ? 0 : 1).begin(),
                      memory.get_region(swap_ ? 0 : 1).end(),
                      pattern_0);
            std::fill(memory.get_region(swap_ ? 1 : 0).begin(),
                      memory.get_region(swap_ ? 1 : 0).end(),
                      pattern_1);

            return Workload<MemMoveOperation>(
                std::move(memory),
                swap_ ? 0 : 1,
                swap_ ? 1 : 0);
        }

    private:
        std::uint32_t transfer_size_;
        std::uint32_t src_alignment_;
        std::uint32_t dst_alignment_;
        std::int32_t  offset_;
        bool          swap_;
    };
}  // namespace dml::testing

#endif  //DML_TESTING_MEM_MOVE_WORKLOAD_BUILDER_HPP
