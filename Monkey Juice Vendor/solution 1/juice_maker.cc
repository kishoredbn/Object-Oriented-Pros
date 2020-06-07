#include "common.h"
#include "juice_maker.h"

// class CommonJuiceMaker
struct CommonJuiceMaker::PimplMember {
    vpICustomer vcustomers;
    umFruit umfruits;
};

CommonJuiceMaker::CommonJuiceMaker()
: m_member(std::make_shared<PimplMember>()) {
}

void CommonJuiceMaker::AddCustomer(ICustomer* customer) {
    assert(m_member);
    assert(customer);
    m_member->vcustomers.emplace_back(customer);
}

auto CommonJuiceMaker::PrepareJuice(JuiceType juice_type) -> std::vector<Fruit> {
    std::vector<Fruit> ret;

    switch (juice_type)
    {
        case JuiceType::Standard: ret = StdPrepareJuice(); break;
        case JuiceType::Premium : ret = PrmPrepareJuice(); break;
        case JuiceType::Special : ret = SplPrepareJuice(); break;
        default: break;
    }

    return ret;
}

void CommonJuiceMaker::AddRawMaterials(std::vector<std::tuple<Fruit, uint64_t>> &v_fruits) {
    assert(m_member);

    for(auto &iter : v_fruits) {
        m_member->umfruits[std::get<Fruit>(iter)] += std::get<uint64_t>(iter);
    }
}

void CommonJuiceMaker::GetOrder(ICustomer* customer) {
    assert(m_member);
    assert(customer);

    auto customer_iter = find_if(m_member->vcustomers.begin(),
                              m_member->vcustomers.end(), [&](auto &each_customer){
                                  return each_customer->GetCustomerId() == customer->GetCustomerId();
                              });
    
    if(customer_iter == m_member->vcustomers.end()) return;

    m_member->vcustomers.erase(customer_iter);

    auto cust_orders = customer->GetOrders();
    for(auto &iter : cust_orders) {
        auto juice = PrepareJuice(iter);
        customer->ServeOrders(juice);
    } 
}

// class MagicJuiceMaker
auto MagicJuiceMaker::StdPrepareJuice() -> std::vector<Fruit> {
    assert(m_member);

    std::vector<Fruit> ret;
    for(auto &iter : m_member->umfruits ) {
        if(iter.second) {
            iter.second--;
            ret.emplace_back(iter.first);
            break;
        }
    }
    return ret;
}

auto MagicJuiceMaker::PrmPrepareJuice() -> std::vector<Fruit> {
    std::vector<Fruit> ret;

    uint8_t count = 0;
    for(auto &iter : m_member->umfruits ) {
        if(iter.second) {
            iter.second--;
            ret.emplace_back(iter.first);
            if(count++ > 0) break;
        }
    }
    return ret;
}
auto MagicJuiceMaker::SplPrepareJuice() -> std::vector<Fruit> {
    std::vector<Fruit> ret;

    uint8_t count = 0;
    for(auto &iter : m_member->umfruits ) {
        if(iter.second) {
            iter.second--;
            ret.emplace_back(iter.first);
            if(count++ > 1) break;
        }
    }
    return ret;
}

// class SupremeJuiceMaker
auto SupremeJuiceMaker::StdPrepareJuice() -> std::vector<Fruit> {
    assert(m_member);

    std::vector<Fruit> ret;
    for(auto &iter : fruit_preference ) {
        auto find_fruit = m_member->umfruits.find(iter);
        if(find_fruit == m_member->umfruits.end()) continue;

        if(find_fruit->second) {
            find_fruit->second--;
            ret.emplace_back(find_fruit->first);
            break;
        }
    }
    return ret;
}

auto SupremeJuiceMaker::PrmPrepareJuice() -> std::vector<Fruit> {
    assert(m_member);

    uint8_t count = 0;
    std::vector<Fruit> ret;
    for(auto &iter : fruit_preference ) {
        auto find_fruit = m_member->umfruits.find(iter);
        if(find_fruit == m_member->umfruits.end()) continue;

        if(find_fruit->second) {
            find_fruit->second--;
            ret.emplace_back(find_fruit->first);
            if(count++ > 0) break;
        }
    }
    return ret;
}

auto SupremeJuiceMaker::SplPrepareJuice() -> std::vector<Fruit> {
    assert(m_member);

    uint8_t count = 0;
    std::vector<Fruit> ret;
    for(auto &iter : fruit_preference ) {
        auto find_fruit = m_member->umfruits.find(iter);
        if(find_fruit == m_member->umfruits.end()) continue;

        if(find_fruit->second) {
            find_fruit->second--;
            ret.emplace_back(find_fruit->first);
            if(count++ > 1) break;
        }
    }
    return ret;
}

// void SupremeJuiceMaker::SayFruitPreference(vFruit&) {
// }

// class AwesomeJuiceMaker
auto AwesomeJuiceMaker::StdPrepareJuice() -> std::vector<Fruit> {
    assert(m_member);

    std::vector<Fruit> ret;
    while(true) {
        auto fruit = GetRandomFruit();
        auto find_fruit = m_member->umfruits.find(fruit);
        if(find_fruit == m_member->umfruits.end()) continue;

        if(find_fruit->second) {
            find_fruit->second--;
            ret.emplace_back(find_fruit->first);
            break;
        }
    }
    return ret;
}

auto AwesomeJuiceMaker::PrmPrepareJuice() -> std::vector<Fruit> {
    assert(m_member);

    uint8_t count = 0;
    std::vector<Fruit> ret;
    while(true) {
        auto fruit = GetRandomFruit();
        auto find_fruit = m_member->umfruits.find(fruit);
        if(find_fruit == m_member->umfruits.end()) continue;

        if(find_fruit->second) {
            find_fruit->second--;
            ret.emplace_back(find_fruit->first);
            if(count++ > 0) break;
        }
    }
    return ret;
}
auto AwesomeJuiceMaker::SplPrepareJuice() -> std::vector<Fruit> {
    assert(m_member);

    uint8_t count = 0;
    std::vector<Fruit> ret;
    while(true) {
        auto fruit = GetRandomFruit();
        auto find_fruit = m_member->umfruits.find(fruit);
        if(find_fruit == m_member->umfruits.end()) continue;

        if(find_fruit->second) {
            find_fruit->second--;
            ret.emplace_back(find_fruit->first);
            if(count++ > 1) break;
        }
    }
    return ret;
}

auto AwesomeJuiceMaker::GetRandomFruit() -> Fruit {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_fruit_count(0, g_fruit_variety_count-1); // distribution in range [1, 6]

    return GetFruitFromId(dist_fruit_count(rng));
}


// void AwesomeJuiceMaker::SayFruitPreference(vFruit&) {
// }