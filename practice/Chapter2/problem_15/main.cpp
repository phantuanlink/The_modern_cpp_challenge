#include <iostream>
#include <string>
#include <cstdint>
#include <array>


class Ipv4Address {
private:
    std::array<std::uint8_t, 4> data;

public:
    constexpr Ipv4Address() : data{ {0} } {}
    constexpr Ipv4Address(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : data{{a, b, c, d}} {}
    
    Ipv4Address(const Ipv4Address& other) noexcept : data(other.data) {}
    
    Ipv4Address& operator=(const Ipv4Address& other) noexcept {
        data = other.data;
        return *this;
    }


    friend std::ostream& operator<<(std::ostream& os, const Ipv4Address& address) {
        os << static_cast<int>(address.data[0]) << "." 
            << static_cast<int>(address.data[1]) << "."
            << static_cast<int>(address.data[2]) << "."
            << static_cast<int>(address.data[3]);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Ipv4Address& address) {
        char d1, d2, d3;
        int a, b, c, d;
        is >> a >> d1 >> b >> d2 >> c >> d3 >> d;
        
        if (d1 == '.' && d2 == '.' && d3 == '.') {
            address = Ipv4Address(a, b, c, d);
        }
        else {
            is.setstate(std::ios_base::failbit);
        }
        return is;

    }

};

int main(int argc, char** argv) {
    
    Ipv4Address a(168, 192, 0, 1);
    std::cout << a << std::endl;

    Ipv4Address b = a;
    Ipv4Address c;
    c = b;

    Ipv4Address ip;
    std::cout << ip << std::endl;
    std::cin >> ip;
    if (!std::cin.fail())
        std::cout << ip << std::endl;
    

    return 0;
}