#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>

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
        std::string get_hex_str() const;

        void inverse_bit(const int position);
        bool get_bit(const int position) const;
        void set_bit(const int position, const bool bit);

        void set_bit_field(int position, const BitVec &bitvector);

        template<typename Type>
        void set_bit_field(const int position, Type data) {
            static_assert(std::is_integral<Type>::value);

            std::size_t size_data = sizeof(data) * BYTE_SIZE;
            for (int index = position, index_2 = 0; index_2 < size_data && index < size_; ++index, ++index_2) {
                set_bit(index, static_cast<bool>((data << (size_data - 1 - index_2)) >> (size_data - 1) & 0b1));
            }
        }

        BitVec get_bit_field(const int position, const int deep_bit) const;
        void  show_bit_field(const int position, const int deep_bit) const;

        std::size_t bit_depth() const;

        public:
            template<typename Type>
            Type get_bit_field_func(int position, int deep_bit) const {
                static_assert(std::is_integral<Type>::value);
                Type target_data = 0;
                Type power_2 = 1;
                std::size_t size_data = sizeof(target_data)*BYTE_SIZE;

                for (int index = position, index_2 = 0; index_2 < deep_bit && index < size_ && index_2 < size_data; ++index, ++index_2, power_2 *= 2) {
                    if (get_bit(index)) {
                        target_data += power_2;
                    }
                }

                return target_data;

            }
};

struct get_bit_field_in_var {
    get_bit_field_in_var(int position, int deep_bit, const BitVec &bitvector) : position_(position), deep_bit_(deep_bit),  bitvector_(bitvector) {}

    template<typename Type> operator Type() {
        return bitvector_.get_bit_field_func<Type>(position_, deep_bit_);
    }

    private:
        int position_;
        int deep_bit_;
        BitVec bitvector_;
};

};