#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <assert.h>
#include <algorithm>

template<class C, typename T>
bool contains(C& c, const T value) {
    if (std::find(c.begin(), c.end(), value) == std::end(c)) {
        return false;
    }
    else {
        return true;
    }
}


template<class C, typename... Args>
bool contains_any(C& c, const Args&... args) {
    bool theres_any = (contains(c, args) || ...);
    return theres_any;
}

template<class C, typename... Args>
bool contains_all(C& c, const Args&... args) {
    bool theres_any = (contains(c, args) && ...);
    return theres_any;
}

template<class C, typename... Args>
bool contains_none(C& c, const Args&... args) {
    bool theres_any = (contains(c, args) || ...);
    return !theres_any;
}



int main()
{
   std::vector<int> v{ 1,2,3,4,5,6 };
   std::array<int, 6> a{ { 1,2,3,4,5,6 } };
   std::list<int> l{ 1,2,3,4,5,6 };

   assert(contains(v, 3));
   assert(contains(a, 5));
   assert(contains(l, 3));

   assert(!contains(v, 30));
   assert(!contains(v, 30));
   assert(!contains(v, 30));



   assert(contains_any(v, 0, 3, 30));
   assert(contains_any(a, 0, 3, 30));
   assert(contains_any(l, 0, 3, 30));

   assert(!contains_any(v, 0, 30));
   assert(!contains_any(a, 0, 30));
   assert(!contains_any(l, 0, 30));

   assert(contains_all(v, 1, 3, 6));
   assert(contains_all(a, 1, 3, 6));
   assert(contains_all(l, 1, 3, 6));

   assert(!contains_all(v, 0, 1, 6, 4));
   assert(!contains_all(a, 0, 1, 5, 3));
   assert(!contains_all(l, 0, 1));

   assert(contains_none(v, 0, 7));
   assert(contains_none(a, 0, 7));
   assert(contains_none(l, 0, 7));

   assert(!contains_none(v, 0, 6, 7));
   assert(!contains_none(a, 0, 6, 7));
   assert(!contains_none(l, 0, 6, 7));

   std::cout << "Finish\n";
}
