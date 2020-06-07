#pragma once

static uint64_t g_unique_customer_id = 0;

#define ATTRIBUTES CODE(Banana,    "Banana")    \
                   CODE(Pineapple, "Pineapple") \
                   CODE(Apple,     "Apple")     \
                   CODE(Mango,     "Mango") 

#undef CODE
#define CODE(__fruit, __type) __fruit,
enum class Fruit : uint64_t { 
                                ATTRIBUTES
                                Default
                            };

#undef CODE
#define CODE(__fruit, __type) + 1
const uint8_t g_fruit_variety_count = 0 +
                              ATTRIBUTES + 0;

enum class JuiceType : uint64_t {Standard, // made with 1 fruit
                                 Premium,  // made with 2 fruits
                                 Special}; // made with 3 fruits

#undef CODE
#define CODE(__fruit, __text) case Fruit::__fruit: return __text;
constexpr const char* GetJuiceText(const Fruit &fruit) {
    switch(fruit) {
    ATTRIBUTES
    default: break;
    }
    return "None";
}

#undef FRUIT_ID_COUNTER
#define FRUIT_ID_COUNTER  __COUNTER__
#undef CODE
#define CODE(__fruit, __text) case FRUIT_ID_COUNTER : return Fruit::__fruit;
constexpr const Fruit GetFruitFromId(const int id) {
    switch(id) {
        ATTRIBUTES
        default: return Fruit::Banana;
    }
}

using vFruit = std::vector<Fruit>;
using umFruit = std::unordered_map<Fruit, uint64_t>;
using vJuiceType = std::vector<JuiceType>;
using vFruitQuants = std::vector<std::tuple<Fruit, uint64_t>>;

