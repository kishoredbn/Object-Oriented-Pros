#pragma once

static uint64_t g_unique_customer_id = 0;

#define TYPES_OF_FRUITS CODE(Banana)    \
                        CODE(Pineapple) \
                        CODE(Apple)     \
                        CODE(Mango) 

// ***************************************
// ******** Auto-Generated Codes *********
#undef CODE
#define CODE(__fruit) __fruit,
enum class Fruit : uint64_t { 
                                TYPES_OF_FRUITS
                                Default
                            };

#undef CODE
#define CODE(__fruit) + 1
const uint8_t g_fruit_variety_count = 0 // expands here as fruit counter
                              TYPES_OF_FRUITS;

#undef CODE
#define CODE(__fruit) case Fruit::__fruit: return #__fruit;
constexpr const char* GetJuiceText(const Fruit &fruit) {
    switch(fruit) {
    TYPES_OF_FRUITS // expands here as switch-case
    default: break;
    }
    return "None";
}

#undef FRUIT_ID_COUNTER
#define FRUIT_ID_COUNTER  __COUNTER__
#undef CODE
#define CODE(__fruit) case FRUIT_ID_COUNTER : return Fruit::__fruit;
constexpr const Fruit GetFruitFromId(const int id) {
    switch(id % g_fruit_variety_count) {
        TYPES_OF_FRUITS // expands here as switch-case return
        default: return Fruit::Banana;
    }
}
// ******** Auto-Generated Codes *********
// ***************************************

enum class JuiceType : uint64_t {Standard, // Juice made with 1 fruit
                                 Premium,  // Juice made with 2 fruits
                                 Special}; // Juice made with 3 fruits

using vFruit = std::vector<Fruit>;
using umFruit = std::unordered_map<Fruit, uint64_t>;
using vJuiceType = std::vector<JuiceType>;
using vFruitQuants = std::vector<std::tuple<Fruit, uint64_t>>;

