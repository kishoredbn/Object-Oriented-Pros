#pragma once

static uint64_t g_unique_customer_id = 0;

#define TYPES_OF_FRUITS CODE(Banana,    "Banana")    \
                        CODE(Pineapple, "Pineapple") \
                        CODE(Apple,     "Apple")     \
                        CODE(Mango,     "Mango") 

#undef CODE
#define CODE(__fruit, __type) __fruit,
enum class Fruit : uint64_t { 
                                TYPES_OF_FRUITS
                                Default
                            };

#undef CODE
#define CODE(__fruit, __type) + 1
const uint8_t g_fruit_variety_count = 0
                              TYPES_OF_FRUITS + 0;

enum class JuiceType : uint64_t {Standard, // Juice made with 1 fruit
                                 Premium,  // Juice made with 2 fruits
                                 Special}; // Juice made with 3 fruits

#undef CODE
#define CODE(__fruit, __text) case Fruit::__fruit: return __text;
constexpr const char* GetJuiceText(const Fruit &fruit) {
    switch(fruit) {
    TYPES_OF_FRUITS
    default: break;
    }
    return "None";
}

#undef FRUIT_ID_COUNTER
#define FRUIT_ID_COUNTER  __COUNTER__
#undef CODE
#define CODE(__fruit, __text) case FRUIT_ID_COUNTER : return Fruit::__fruit;
constexpr const Fruit GetFruitFromId(const int id) {
    switch(id % g_fruit_variety_count) {
        TYPES_OF_FRUITS
        default: return Fruit::Banana;
    }
}

using vFruit = std::vector<Fruit>;
using umFruit = std::unordered_map<Fruit, uint64_t>;
using vJuiceType = std::vector<JuiceType>;
using vFruitQuants = std::vector<std::tuple<Fruit, uint64_t>>;

