#pragma once

#include <string>
#include <vector>

#include "BitVector.h"
#include "Config.h"

class IBFIndex
{
    public:
        explicit IBFIndex(const Config& config) : config_(config) 
        {
            buildIndex();
        }

        ~IBFIndex() = default;

        IBFIndex(const IBFIndex&) = default;
        IBFIndex& operator=(const IBFIndex&) = delete;

        IBFIndex(IBFIndex&&) = default;
        IBFIndex& operator=(IBFIndex&&) = delete;

    private:
        const Config& config_;

        void buildIndex();
};