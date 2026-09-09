#pragma once
#include <vector>
#include <string>

struct Peak 
{
    double mz;
    double intensity;
};

class Spectrum 
{
public:
    std::vector<Peak> peaks;
    double precursor_mass = 0.0;
    std::string protein_name;
    u_int8_t charge;
};