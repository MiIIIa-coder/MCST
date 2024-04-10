#include "bitvec.hpp"

int main()
{
    std::vector<int> vec_data_bit{0, 1, 5, 7, 13, 29, 311};
    bitvec::BitVec B{312, vec_data_bit};
    B.show();

    bitvec::BitVec B1{35};
    B1.show();
    B1.set_bit(2, 1);
    B1.set_bit(5, 1);
    B1.set_bit(11, 1);
    B1.show();

    std::vector<unsigned char> vec_data{1, 4, 3, 55};
    bitvec::BitVec B2{vec_data};
    B2.show();
    B2.set_bit(3, 1);
    B2.set_bit(5, 1);
    B2.set_bit(9, 1);
    B2.show();
    std::cout << "bit nubmer 9 = " << B2.get_bit(9) << std::endl;
    B2.inverse_bit(9);
    std::cout << "bit nubmer 9 = " << B2.get_bit(9) << std::endl;
    B2.show();

    std::cout << "__________________________" << std::endl;
    B.set_bit_field(8, B2);
    B.show();

    std::cout << "__________________________" << std::endl;
    unsigned char u_char = 255;
    B.set_bit_field(8, u_char);
    B.set_bit_field(64, u_char);
    B.set_bit_field(228, u_char);
    B.show();

    std::cout << "__________________________" << std::endl;
    int integ = -255000;
    B.set_bit_field(72, integ);
    B.show();

    std::cout << "__________________________" << std::endl;
    unsigned long long ull = 255000255000;
    B.set_bit_field(120, ull);
    B.show();

    // std::cout << "__________________________" << std::endl;
    // bool bl = true;
    // B.set_bit_field(8, bl);
    // B.show();

    std::cout << "__________________________" << std::endl;
    bitvec::BitVec B3 = B.get_bit_field(8, 31);
    B3.show();

    std::cout << "__________________________" << std::endl;
    bitvec::BitVec B4 = B.get_bit_field(0, 15);
    B4.show();

    std::cout << "__________________________" << std::endl;
    B.show_bit_field(24, 24);

    std::cout << "__________________________" << std::endl;
    int data ;
    bitvec::get_bit_field_in_var bit_field{0, 32, B};
    data = bit_field;
    std::cout << data << std::endl;

    return 0;
}