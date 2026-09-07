#include "include/CLI11.hpp"
#include "src/Index.h"
#include "src/Config.h"

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

    query_cmd->add_option("-i --index", config.index, "Path to the index")->required();
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
        std::cout << "Building index from: " << config.index << std::endl;
        // Call the function to build the index
        IBF_Index index;
        std::cout << "Output index saved to: " << config.output << std::endl;
    }
}