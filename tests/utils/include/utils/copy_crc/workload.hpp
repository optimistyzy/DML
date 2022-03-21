/*******************************************************************************
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#ifndef DML_TESTING_COPY_CRC_WORKLOAD_HPP
#define DML_TESTING_COPY_CRC_WORKLOAD_HPP

#include <utils/memory.hpp>
#include <utils/operation.hpp>
#include <utils/workload.hpp>
#include <utils/workload_builder.hpp>

namespace dml::testing
{
    template <>
    class Workload<CopyCrcOperation>: public WorkloadBase
    {
    public:
        Workload() = delete;

        auto& get_src() noexcept
        {
            return memory_.get_region(0);
        }

        auto& get_dst() noexcept
        {
            return memory_.get_region(1);
        }

        auto& get_crc_seed() noexcept
        {
            return crc_seed_;
        }

        [[nodiscard]] auto get_bypass_reflection() const noexcept
        {
            return bypass_reflection_;
        }

        [[nodiscard]] auto get_bypass_data_reflection() const noexcept
        {
            return bypass_data_reflection_;
        }

        bool operator==(const Workload& other) const noexcept
        {
            return this->memory_ == other.memory_;
        }

    private:
        friend WorkloadBuilder<CopyCrcOperation>;

        Workload(Memory&&      memory,
                 std::uint32_t crc_seed,
                 bool          bypass_reflection,
                 bool          bypass_data_reflection) noexcept:
            WorkloadBase(std::move(memory)),
            crc_seed_(crc_seed),
            bypass_reflection_(bypass_reflection),
            bypass_data_reflection_(bypass_data_reflection)
        {
        }

    private:
        std::uint32_t crc_seed_;
        bool          bypass_reflection_;
        bool          bypass_data_reflection_;
    };
}  // namespace dml::testing

#endif  //DML_TESTING_COPY_CRC_WORKLOAD_HPP
