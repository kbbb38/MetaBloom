#include <vector>
#include <cstdint>
#include <cstddef>
#include <bit>

class BitVector 
{
    std::vector<std::uint64_t> words;
    const std::size_t num_bits = 0;

    static constexpr std::size_t bits_per_word = 64;

    static std::size_t word_count(std::size_t bits) 
    {
        return (bits + bits_per_word - 1) / bits_per_word;
    }

public:
    explicit BitVector(std::size_t bits = 0): words(word_count(bits)), num_bits(bits) {}

    std::size_t size() const 
    {
        return num_bits;
    }

    bool get(std::size_t i) const 
    {
        return (words[i / bits_per_word] >> (i % bits_per_word)) & 1ULL;
    }

    void flip(std::size_t i) {
        words[i / bits_per_word] ^= 1ULL << (i % bits_per_word);
    }
};