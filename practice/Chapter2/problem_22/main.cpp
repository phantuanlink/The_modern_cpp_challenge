#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <assert.h>
#include <algorithm>



namespace temperature {
    enum class scale {
        fahrenheit,
        celsius,
        kelvin
    };


    template<scale S>
    class Temperature {
        const double value_;
    public:
        explicit constexpr Temperature(double value) : value_(value) {}

        constexpr double getValue() const { return value_; }
    };


    bool areEqual(const double a, const double b, const double epsilon = 0.001) {
        return (std::abs(a - b) < epsilon);
    }



    // overloading the operator == for comparison
    template<scale S>
    bool operator==(const Temperature<S>& a, const Temperature<S>& b) {
        return areEqual(a.getValue(),b.getValue());
    }


    template <scale S, scale R>
    struct conversion_traits
    {
        static double convert(double const value) = delete;
    };

    template <>
    struct conversion_traits<scale::celsius, scale::kelvin>
    {
        static double convert(double const value)
        {
            return value + 273.15;
        }
    };

    template <>
    struct conversion_traits<scale::kelvin, scale::celsius>
    {
        static double convert(double const value)
        {
            return value - 273.15;
        }
    };

    template <>
    struct conversion_traits<scale::celsius, scale::fahrenheit>
    {
        static double convert(double const value)
        {
            return (value * 9) / 5 + 32;;
        }
    };

    template <>
    struct conversion_traits<scale::fahrenheit, scale::celsius>
    {
        static double convert(double const value)
        {
            return (value - 32) * 5 / 9;
        }
    };

    template <>
    struct conversion_traits<scale::fahrenheit, scale::kelvin>
    {
        static double convert(double const value)
        {
            return (value + 459.67) * 5 / 9;
        }
    };

    template <>
    struct conversion_traits<scale::kelvin, scale::fahrenheit>
    {
        static double convert(double const value)
        {
            return (value * 9) / 5 - 459.67;
        }
    };


    template<scale R, scale S>
    constexpr Temperature<R> temperature_cast(Temperature<S> temp) {
        return Temperature<R>(static_cast<double>(conversion_traits<R, S>::convert(temp.getValue())));
    }
    

    namespace temperature_scale_literals {
        constexpr Temperature<scale::celsius> operator""_deg(const long double value) {
            return Temperature<scale::celsius>(static_cast<double>(value));
        }

        constexpr Temperature<scale::fahrenheit> operator""_f(const long double value) {
            return Temperature<scale::fahrenheit>(static_cast<double>(value));
        }

        constexpr Temperature<scale::kelvin> operator""_k(long double value) {
            return Temperature<scale::kelvin>(static_cast<double>(value));
        }
    }
}



int main()
{
   using namespace temperature;
   using namespace temperature_scale_literals;

   auto t1{ 36.5_deg };
   auto t2{ 79.0_f };
   auto t3{ 100.0_k };

   auto testf = temperature_cast<scale::fahrenheit>(t1);
   auto testc = temperature_cast<scale::celsius>(testf);

   
   {
      auto tf = temperature_cast<scale::fahrenheit>(t1);
      auto tc = temperature_cast<scale::celsius>(tf);
      assert(t1 == tc);
   }


   {
      auto tk = temperature_cast<scale::kelvin>(t1);
      auto tc = temperature_cast<scale::celsius>(tk);
      assert(t1 == tc);
   }

   {
      auto tc = temperature_cast<scale::celsius>(t2);
      auto tf = temperature_cast<scale::fahrenheit>(tc);
      assert(t2 == tf);
   }

   {
      auto tk = temperature_cast<scale::kelvin>(t2);
      auto tf = temperature_cast<scale::fahrenheit>(tk);
      assert(t2 == tf);
   }

   {
      auto tc = temperature_cast<scale::celsius>(t3);
      auto tk = temperature_cast<scale::kelvin>(tc);
      assert(t3 == tk);
   }

   {
      auto tf = temperature_cast<scale::fahrenheit>(t3);
      auto tk = temperature_cast<scale::kelvin>(tf);
      assert(t3 == tk);
   }
}
