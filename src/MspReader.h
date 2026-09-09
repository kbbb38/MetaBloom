#pragma once

#include <fstream>
#include "Spectrum.h"

class MspReader 
{
public:
    explicit MspReader(const std::string& filename) : file_(filename) {}

    bool next(Spectrum& spec);

private:
    std::ifstream file_;
    bool extractCommentInfo(const std::string& comment, Spectrum& spec);
};