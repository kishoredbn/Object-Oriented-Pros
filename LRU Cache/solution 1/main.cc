#include <iostream>

#include "cache.h"

int main()
{
    // test case 1:
    Cache cache(2);
    cache.Set(3, 3);
    cache.Set(4, 4);
    std::cout<<cache.Get(3)<<"\n";
    std::cout<<cache.Get(2)<<"\n";
    cache.Set(2, 2);
    std::cout<<cache.Get(4)<<"\n";
    std::cout<<cache.Get(3)<<"\n";
    std::cout<<cache.Get(2)<<"\n";
    std::cout<<cache.Get(3)<<"\n";
    cache.Set(4, 4);
    std::cout<<cache.Get(2)<<"\n";
    std::cout<<cache.Get(4)<<"\n";

    // test case 2:
    Cache cache1(3);
    cache1.Set(3, 3);
    cache1.Set(4, 4);
    std::cout<<cache1.Get(3)<<"\n";
    std::cout<<cache1.Get(2)<<"\n";
    cache1.Set(2, 2);
    std::cout<<cache1.Get(4)<<"\n";
    std::cout<<cache1.Get(3)<<"\n";
    std::cout<<cache1.Get(2)<<"\n";
    std::cout<<cache1.Get(3)<<"\n";
    cache1.Set(4, 4);
    std::cout<<cache1.Get(2)<<"\n";
    std::cout<<cache1.Get(4)<<"\n";

    // test case 3:
    Cache cache2(3);
    cache2.Set(3, 3);
    cache2.Set(4, 4);
    std::cout<<cache2.Get(3)<<"\n";
    std::cout<<cache2.Get(2)<<"\n";
    cache2.Set(2, 2);
    std::cout<<cache2.Get(4)<<"\n";
    std::cout<<cache2.Get(3)<<"\n";
    std::cout<<cache2.Get(2)<<"\n";
    std::cout<<cache2.Get(3)<<"\n";
    cache2.Set(4, 5);
    std::cout<<cache2.Get(2)<<"\n";
    std::cout<<cache2.Get(4)<<"\n";

    return 0;
}