#include "common.h"
#include "juice_customer.h"

struct CCustomer::PimplMember {
    uint64_t id;
    spIJuiceMaker juice_vendor;
    std::vector<JuiceType> orders_unserved;
    std::vector<std::vector<Fruit>> orders_served;
    PimplMember(const uint64_t id) : id(id) {}
};

CCustomer::CCustomer() 
: m_member(std::make_shared<PimplMember>(g_unique_customer_id++)) {
}

auto CCustomer::GetCustomerId() -> uint64_t {
    assert(m_member);
    return m_member->id;
}


void CCustomer::GotoJuiceMaker(spIJuiceMaker& juice_maker) {
    assert(juice_maker);
    assert(m_member);

    m_member->orders_unserved.clear();
    m_member->orders_served.clear();

    m_member->juice_vendor = juice_maker;
    juice_maker->AddCustomer(this);
}

void CCustomer::OrderJuice(std::vector<JuiceType> &v_juice_type) {
    assert(m_member);

    for(auto &iter : v_juice_type)
        m_member->orders_unserved.emplace_back(iter);

    assert(m_member->juice_vendor);
    m_member->juice_vendor->GetOrder(this);

    m_member->orders_unserved.clear();
}


auto CCustomer::GetOrders() -> std::vector<JuiceType> {
    assert(m_member);
    return m_member->orders_unserved;
}


void CCustomer::ServeOrders(std::vector<Fruit>& servered_juice) {
    assert(m_member);

    m_member->orders_served.emplace_back(servered_juice);
}

void CCustomer::ConsumeJuice() {
    assert(m_member);

    for (auto &v_iter : m_member->orders_served)
    {
        std::cout<<"Customer "<< m_member->id<<" is Served Juice: ";
        for(auto &iter : v_iter) std::cout<<GetJuiceText(iter)<<", ";
        std::cout<<"\n";
    }
}

void CCustomerWithPreference::FruitPreference(std::vector<Fruit>&) {
    assert(m_member);
    assert(m_member->juice_vendor);

    // spIJuiceMakerFruitChoice juice_choice = m_member->juice_vendor;

}
