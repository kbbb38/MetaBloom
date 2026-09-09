#include "include/CLI11.hpp"
#include "src/Config.h"
#include "src/IBFIndex.h"
#include "src/MspReader.h"
#include "src/Spectrum.h"

#include <map>
#include <iostream>

int main(int argc, char** argv) 
{
    /*
        Option handling
    */

    CLI::App app{"MetaBloom"};
    argv = app.ensure_utf8(argv);

    Config config;

    // Options
    // Indexing
    auto* index_cmd = app.add_subcommand("index", "Build a new index");

    index_cmd->add_option("-i, --input", config.index, "Input Spectral Database")->required();
    index_cmd->add_option("-o, --output", config.output, "Path to the output index")->required();

    // Querying
    auto* query_cmd = app.add_subcommand("query", "Query an existing index");

    query_cmd->add_option("-i, --index", config.index, "Path to the index")->required();
    query_cmd->add_option("-q, --query", config.query, "Query spectra")->required();
    query_cmd->add_option("-o, --output", config.output, "Path to the output index")->required();

    // Parse
    app.parse(argc, argv);

    std::cout << "\033[1;32m"; 
    std::cout << "╔════════════════════╗" << std::endl;
    std::cout << "║     MetaBloom      ║" << std::endl;
    std::cout << "╚════════════════════╝" << std::endl;
    std::cout << "\033[0m";

    if (index_cmd->parsed()) 
    {
        MspReader reader(config.index);
        Spectrum spectrum;

        std::map<std::string, size_t> index;

        while (reader.next(spectrum)) 
        {
            index[spectrum.protein_name]++;
        }

        for (const auto& [protein, count] : index) 
        {
            std::cout << protein << ": " << count << " spectra" << std::endl;
        }
    }
}