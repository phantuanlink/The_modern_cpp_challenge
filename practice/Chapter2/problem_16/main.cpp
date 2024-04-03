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

    uint32_t to_ulong() const noexcept {
        return (static_cast<uint32_t>(data[0]) << 24) | (static_cast<uint32_t>(data[1]) << 16) | (static_cast<uint32_t>(data[2]) << 8) | static_cast<uint32_t>(data[3]);
    }


    // Pre-increament
    Ipv4Address& operator++() {
        for (int i = 3; i >= 0; --i) {
            if (data[i] < 255) {
                ++data[i];
                break; // Incremented, no need to continue
            }
            else {
                data[i] = 0; // Carry to the next byte
            }
        }
        return *this;
    }

    // Post-increament
    Ipv4Address& operator++(int) {
        Ipv4Address temp = *this;
        ++(*this);
        return temp;
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

    friend bool operator <= (const Ipv4Address& a, const Ipv4Address& b) 
    {
        return a.to_ulong() <= b.to_ulong();
    }

    friend bool operator > (const Ipv4Address& a, const Ipv4Address& b)
    {
        return a.to_ulong() > b.to_ulong();
    }
};

int main(int argc, char** argv) {
    
    Ipv4Address ip_lower_bound, ip_higher_bound;

    std::cin >> ip_lower_bound;
    if (!std::cin.fail())
        std::cout << ip_lower_bound << std::endl;
    std::cin >> ip_higher_bound;
    if (!std::cin.fail())
        std::cout << ip_higher_bound << std::endl;


    if (ip_higher_bound > ip_lower_bound)
    {
        for (Ipv4Address a = ip_lower_bound; a <= ip_higher_bound; a++)
        {
            std::cout << a << std::endl;
        }
    }
    else
    {
        std::cerr << "invalid range!" << std::endl;
    }

    return 0;
}