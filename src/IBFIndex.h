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
        
    private:
        const Config& config_;

        void buildIndex();
};