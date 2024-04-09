#include <iostream>
#include <vector>
#include <bitset>

#define BYTE_SIZE 8

namespace bitvec {

typedef std::bitset<BYTE_SIZE> byte_t;

byte_t byte_reverse(byte_t const &byte);

class BitVec final {
    private:
        std::vector<unsigned char> bitvec_;
        std::size_t size_;
    
    public:
        BitVec(std::size_t size) : bitvec_(size/BYTE_SIZE + (size % BYTE_SIZE ? 1 : 0)), size_(size) {}
        BitVec(std::vector<unsigned char> bitvec) : bitvec_(bitvec), size_(bitvec.size()*8) {} 
        BitVec(std::size_t size, std::vector<int> bitvec);  //incorrect bits will ignored

    public:
        void show() const;
        void inverse_bit(int position);
        bool get_bit(int position) const;
        void set_bit(int position, bool bit);

        void set_bit_field(int position, const BitVec &bitvector);

        template<typename Type>
        void set_bit_field(int position, Type data) {
            static_assert(std::is_integral<Type>::value);

            std::size_t size_data = sizeof(data) * BYTE_SIZE;
            for (int index = position, index_2 = 0; index_2 < size_data && index < size_; ++index, ++index_2) {
                set_bit(index, static_cast<bool>((data << (size_data - 1 - index_2)) >> (size_data - 1) & 0b1));
            }
        }

        BitVec get_bit_field(int position, int deep_bit) const;

        std::size_t bit_depth() const;
};

};