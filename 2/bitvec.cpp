#include "bitvec.hpp"

namespace bitvec {

    byte_t byte_reverse(byte_t const &byte) {
        byte_t tmp = byte;
        for (int i = 0; i < BYTE_SIZE; ++i) {
            tmp[i] = byte[BYTE_SIZE - i - 1];
        }
        return tmp;
    }

    BitVec::BitVec(std::size_t size, std::vector<int> bitvec) {
        size_ = size;
        bitvec_.resize(size/BYTE_SIZE + (size % BYTE_SIZE ? 1 : 0), 0);
        for (auto & bit_pos : bitvec) {
            if (bit_pos < size && bit_pos >= 0) {  //correct number bit
                this->set_bit(bit_pos, 1);
            }
        }
    }

    void BitVec::show() const {
        std::cout << "size = " << size_ << std::endl;

        for (std::vector<unsigned char>::const_iterator it = (bitvec_.end()-1); it >= bitvec_.begin(); --it) {
            std::cout << (static_cast<byte_t>(*it)) << " ";
        }
        std::cout << std::endl;
    }

    std::size_t BitVec::bit_depth() const {
        return size_;
    }

    void BitVec::inverse_bit(int position) {
        int byte_idx = position / BYTE_SIZE;
        int bit_idx  = position % BYTE_SIZE;

        byte_t byte = bitvec_[byte_idx];
        byte_t mask = 0b10000000;

        byte ^= (mask >> (BYTE_SIZE - bit_idx - 1));
        bitvec_[byte_idx] = static_cast<unsigned char>(byte.to_ulong());

    }

    bool BitVec::get_bit(int position) const {
        int byte_idx = position / BYTE_SIZE;
        int  bit_idx = position % BYTE_SIZE;

        byte_t byte = bitvec_[byte_idx];
        byte_t mask = 0b10000000;

        byte &= (mask >> (BYTE_SIZE - bit_idx - 1));
        if (byte.count() > 0)
            return true;
        return false;
    }

    void BitVec::set_bit(int position, bool bit) {
        int byte_idx = position / BYTE_SIZE;
        int  bit_idx = position % BYTE_SIZE;

        byte_t byte = bitvec_[byte_idx];

        byte[bit_idx] = bit;

        bitvec_[byte_idx] = static_cast<unsigned char>(byte.to_ulong());
    }

    void BitVec::set_bit_field(int position, const BitVec &bitvector) {
        for (int index = position, index_2 = 0; index_2 < bitvector.bit_depth() && index < size_; ++index, ++index_2) {
            set_bit(index, bitvector.get_bit(index_2));
        }
    }

    BitVec BitVec::get_bit_field(int position, int deep_bit) const {
        std::size_t size_new_bitvec = deep_bit >= size_ - position ? size_ - position : deep_bit;
        std::vector<int> new_bitvec_data;
        for (int index = position, index_2 = 0; index_2 < deep_bit && index < size_; ++index, ++index_2) {
            if (get_bit(index))
                new_bitvec_data.push_back(index_2);
        }

        return BitVec{size_new_bitvec, new_bitvec_data};
    }
    
} // namespace bitvec
