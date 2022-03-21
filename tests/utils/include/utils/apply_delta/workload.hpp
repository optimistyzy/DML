/*******************************************************************************
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#ifndef DML_TESTING_APPLY_DELTA_WORKLOAD_HPP
#define DML_TESTING_APPLY_DELTA_WORKLOAD_HPP

#include <utils/memory.hpp>
#include <utils/operation.hpp>
#include <utils/workload.hpp>
#include <utils/workload_builder.hpp>

namespace dml::testing
{
    template <>
    class Workload<ApplyDeltaOperation>: public WorkloadBase
    {
    public:
        Workload() = delete;

        auto& get_delta() noexcept
        {
            return memory_.get_region(0);
        }

        auto& get_dst() noexcept
        {
            return memory_.get_region(1);
        }

        bool operator==(const Workload& other) const noexcept
        {
            return this->memory_ == other.memory_;
        }

    private:
        friend WorkloadBuilder<ApplyDeltaOperation>;

        explicit Workload(Memory&& memory) noexcept:
            WorkloadBase(std::move(memory))
        {
        }
    };
}  // namespace dml::testing

#endif  //DML_TESTING_APPLY_DELTA_WORKLOAD_HPP
