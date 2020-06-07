#include "common.h"

int main() {

    spIJuiceMaker juice_maker;
    
    CCustomer customer1, customer2; 
    CCustomerWithPreference customer3, customer4, customer5;

    // Creating Juice Vender: MagicJuiceMaker
    auto magic_juice_maker = std::make_shared<MagicJuiceMaker>();
    juice_maker = magic_juice_maker;
    vFruitQuants v_fruits = { // Add fruits to the vendor collection, as fruit and number of count
                        {Fruit::Banana,    {10}},
                        {Fruit::Pineapple, {20}},
                        {Fruit::Apple,     {5}}
                      };
    juice_maker->AddRawMaterials(v_fruits);

    customer1.GotoJuiceMaker(juice_maker); // Customer 1 choices a vendor and goes to it: Magic Juice Maker
    vJuiceType order_list = {JuiceType::Standard};
    customer1.OrderJuice(order_list); // Customer orders "standard" Juice from the vendor
    customer1.ConsumeJuice(); // Customer consumes juice

    customer2.GotoJuiceMaker(juice_maker); // Customer 2 choices a vendor and goes to it: Magic Juice Maker
    order_list = {JuiceType::Special};
    customer2.OrderJuice(order_list); // Customer orders "special" Juice from the vendor
    customer2.ConsumeJuice(); // Customer consumes juice

    // Creating Juice Vender: SupremeJuiceMaker
    auto supre_juice_maker = std::make_shared<SupremeJuiceMaker>(); 
    juice_maker = supre_juice_maker;
    v_fruits = { // Add fruits to the vendor collection, as fruit and number of count
                        {Fruit::Banana, {15}},
                        {Fruit::Mango,  {15}},
                        {Fruit::Apple,  {15}}
                };
    juice_maker->AddRawMaterials(v_fruits);

    customer3.GotoJuiceMaker(juice_maker); // Customer 3 choices a vendor and goes to it: Supreme Juice Maker
//     vFruit fruit_preference_order = {Fruit::Apple, Fruit::Banana, Fruit::Pineapple, Fruit::Mango};
//     customer3.FruitPreference(fruit_preference_order);
    order_list = {JuiceType::Premium};
    customer3.OrderJuice(order_list); // Customer orders "premium" Juice from the vendor
    customer3.ConsumeJuice(); // Customer consumes juice

    customer4.GotoJuiceMaker(juice_maker); // Customer 4 choices a vendor and goes to it: Supreme Juice Maker
    order_list = {JuiceType::Special};
    customer4.OrderJuice(order_list); // Customer orders "special" Juice from the vendor
    customer4.ConsumeJuice(); // Customer consumes juice

    // Creating Juice Vender: AwesomeJuiceMaker
    auto awesome_juice_maker = std::make_shared<AwesomeJuiceMaker>();
    juice_maker = awesome_juice_maker;
    v_fruits = {// Add fruits to the vendor collection, as fruit and number of count
                        {Fruit::Banana,    {10}},
                        {Fruit::Mango,     {25}},
                        {Fruit::Pineapple, {10}}
                };
    juice_maker->AddRawMaterials(v_fruits);

    customer5.GotoJuiceMaker(juice_maker); // Customer 5 choices a vendor and goes to it: Awesome Juice Maker
//     fruit_preference_order = {Fruit::Banana, Fruit::Mango, Fruit::Apple, Fruit::Pineapple};
//     customer3.FruitPreference(fruit_preference_order);
    order_list = {JuiceType::Special};
    customer5.OrderJuice(order_list); // Customer orders "special" Juice from the vendor
    customer5.ConsumeJuice(); // Customer consumes juice

    return 0;
}