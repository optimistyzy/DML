/*******************************************************************************
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#ifndef DML_TESTING_WORKLOAD_BUILDER_HPP
#define DML_TESTING_WORKLOAD_BUILDER_HPP

#include <type_traits>

namespace dml::testing
{
    template <typename Operation>
    class WorkloadBuilder
    {
        static_assert(!std::is_same_v<Operation, Operation>,
                      "No workload builder defined for operation");
    };
}  // namespace dml::testing

#endif  //DML_TESTING_WORKLOAD_BUILDER_HPP
