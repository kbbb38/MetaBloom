#include "MspReader.h"

#include <sstream>
#include <cctype>

bool MspReader::next(Spectrum& spec) 
{
    if (!file_.is_open())
        return false;

    std::string line;

    // Skip any lines until we find the start of a spectrum ("Name:")
    while (std::getline(file_, line)) 
    {
        if (line.rfind("Name:", 0) == 0) 
        {
            // Found a spectrum
            break;
        }
    }

    // No more spectra
    if (file_.eof()) return false;

    // Reset the output spectrum
    spec.peaks.clear();
    spec.protein_name.clear();
    spec.precursor_mass = 0.0;
    spec.charge = 0;

    int numPeaks = 0;
    int peaksRead = 0;
    bool inPeaksSection = false;

    // Parse header lines and peaks until we have all peaks.
    while (std::getline(file_, line)) 
    {
        if (line.empty()) continue;

        if (line.rfind("Comment:", 0) == 0) 
        {
            std::string comment = line.substr(8);
            extractCommentInfo(comment, spec);
            continue;
        }

        if (line.rfind("Num peaks:", 0) == 0) 
        {
            std::istringstream iss(line.substr(10));
            iss >> numPeaks;
            spec.peaks.reserve(numPeaks);
            inPeaksSection = true;
            peaksRead = 0;
            continue;
        }

        // If we are in the peak list section, parse peak lines.
        if (inPeaksSection) 
        {
            if (peaksRead >= numPeaks) 
            {
                // Should not happen normally, but break if it does.
                break;
            }

            std::istringstream iss(line);
            double mz, intensity;
            if (iss >> mz >> intensity) 
            {
                spec.peaks.push_back({mz, intensity});
                ++peaksRead;
            } 
            else 
            {
                // Malformed peak line – abort parsing for this spectrum.
                return false;
            }

            // If we've read all expected peaks, we are done with this spectrum.
            if (peaksRead == numPeaks) 
            {
                // File pointer is at the next line (or EOF).
                return true;
            }
        }
    }
    return false;
}

bool MspReader::extractCommentInfo(const std::string& comment, Spectrum& spec) 
{
    // Extract protein name: Protein="..."
    size_t pos = comment.find("Protein=\"");
    if (pos != std::string::npos) 
    {
        pos += 9;
        size_t end = comment.find('"', pos);
        if (end != std::string::npos) 
        {
            spec.protein_name = comment.substr(pos, end - pos);
        }
    }

    // Extract precursor mass: ...
    pos = comment.find("Parent=");
    if (pos != std::string::npos) 
    {
        pos += 7;
        size_t end = comment.find_first_of(" \t", pos);
        if (end == std::string::npos) end = comment.length();
        std::string parentStr = comment.substr(pos, end - pos);
        try 
        {
            spec.precursor_mass = std::stod(parentStr);
        } 
        catch (...) { }
    }

    // Extract charge: Charge=2
    pos = comment.find("Charge=");
    if (pos != std::string::npos) 
    {
        pos += 7;
        size_t end = comment.find_first_of(" \t", pos);
        if (end == std::string::npos) end = comment.length();
        std::string chargeStr = comment.substr(pos, end - pos);
        try 
        {
            int charge = std::stoi(chargeStr);
            if (charge >= 0 && charge <= 255) 
            {
                spec.charge = static_cast<u_int8_t>(charge);
            }
        } catch (...) { }
    }
    return true;
}