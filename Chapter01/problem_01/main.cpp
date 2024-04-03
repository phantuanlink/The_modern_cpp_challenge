#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>


int main()
{
    unsigned int limit = 0;
    std::cout << "Upper limit:";
    std::cin >> limit;

    spdlog::stopwatch sw;
    unsigned long long sum = 0;
    for (unsigned int i = 3; i < limit; ++i)
    {
        if (i % 3 == 0 || i % 5 == 0)
            sum += i;
    }

    std::cout << "sum=" << sum << std::endl;
    spdlog::info("Stopwatch: {} seconds", sw);
}
