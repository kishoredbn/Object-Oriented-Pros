#pragma once

#include "common.h"

class ICustomer {
public:
    virtual auto GetCustomerId() -> uint64_t = 0;
    virtual void GotoJuiceMaker(spIJuiceMaker&) = 0;
    virtual void OrderJuice(std::vector<JuiceType>&) = 0;
    virtual auto GetOrders() -> std::vector<JuiceType> = 0;
    virtual void ServeOrders(std::vector<Fruit>&) = 0;
    virtual void ConsumeJuice() = 0;
    virtual ~ICustomer(){}
};

using spICustomer = std::shared_ptr<ICustomer>;
using vspICustomer = std::vector<spICustomer>;
using vpICustomer = std::vector<ICustomer*>;

class ICustomerAction {
public:
    virtual void FruitPreference(std::vector<Fruit>&) = 0;
    virtual ~ICustomerAction(){}
};

class CCustomer : public ICustomer {
protected: 
    struct PimplMember;
    std::shared_ptr<PimplMember> m_member;
public:
    CCustomer();
    virtual auto GetCustomerId() -> uint64_t override;
    virtual void GotoJuiceMaker(spIJuiceMaker&) override;
    virtual void OrderJuice(std::vector<JuiceType>&) override;
    virtual auto GetOrders() -> std::vector<JuiceType> override;
    virtual void ServeOrders(std::vector<Fruit>&) override;
    virtual void ConsumeJuice() override;
};

class CCustomerWithPreference : public CCustomer, public ICustomerAction {
public:
    virtual void FruitPreference(std::vector<Fruit>&) override;
};
