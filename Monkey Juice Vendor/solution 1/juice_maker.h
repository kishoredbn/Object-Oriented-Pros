#pragma once

#include "juice_attribute.h"

class ICustomer;

// Interface Juice Maker
class IJuiceMaker {
public:
    virtual void AddCustomer(ICustomer*) = 0;
    virtual void AddRawMaterials(std::vector<std::tuple<Fruit, uint64_t>>&) = 0;
    virtual void GetOrder(ICustomer*) = 0;
    virtual ~IJuiceMaker(){}
};

using spIJuiceMaker = std::shared_ptr<IJuiceMaker>;

// Interface Choice Juice Fruit
class IJuiceMakerFruitChoice {
public:
    virtual void SayFruitPreference(vFruit&) = 0;
    virtual ~IJuiceMakerFruitChoice(){}
};

using spIJuiceMakerFruitChoice = std::shared_ptr<IJuiceMakerFruitChoice>;

// Abstract: Common Juice Maker
class CommonJuiceMaker : public IJuiceMaker {
protected:
    struct PimplMember;
    std::shared_ptr<PimplMember> m_member;
    virtual auto StdPrepareJuice() -> std::vector<Fruit> = 0;
    virtual auto PrmPrepareJuice() -> std::vector<Fruit> = 0;
    virtual auto SplPrepareJuice() -> std::vector<Fruit> = 0;
    virtual auto PrepareJuice(JuiceType) -> std::vector<Fruit>;
public:
    CommonJuiceMaker();
    virtual void AddCustomer(ICustomer*) override;
    virtual void AddRawMaterials(std::vector<std::tuple<Fruit, uint64_t>>&) override;
    virtual void GetOrder(ICustomer*) override;
};

// Concrete: Magic Juice Maker : makes juice with whatever fruit is available in the busket
class MagicJuiceMaker : public CommonJuiceMaker {
protected:
    // struct PimplMember;
    // std::shared_ptr<PimplMember> m_member;
    virtual auto StdPrepareJuice() -> std::vector<Fruit> override;
    virtual auto PrmPrepareJuice() -> std::vector<Fruit> override;
    virtual auto SplPrepareJuice() -> std::vector<Fruit> override;
};

// Concrete: Supreme Juice Maker : makes juice with preferential fruit order from the busket
class SupremeJuiceMaker : public CommonJuiceMaker/*, public IJuiceMakerFruitChoice*/ {
protected:
    // struct PimplMember;
    // std::shared_ptr<PimplMember> m_member;
    const vFruit fruit_preference = {Fruit::Banana, Fruit::Apple, Fruit::Mango, Fruit::Pineapple };
    virtual auto StdPrepareJuice() -> std::vector<Fruit> override;
    virtual auto PrmPrepareJuice() -> std::vector<Fruit> override;
    virtual auto SplPrepareJuice() -> std::vector<Fruit> override;
    // virtual void SayFruitPreference(vFruit&) override;
};

// Concrete: Awesome Juice Maker : makes juice with randomly taken fruit from the busket
class AwesomeJuiceMaker : public CommonJuiceMaker/*, public IJuiceMakerFruitChoice*/ {
protected:
    // struct PimplMember;
    // std::shared_ptr<PimplMember> m_member;
    auto GetRandomFruit() -> Fruit;
    virtual auto StdPrepareJuice() -> std::vector<Fruit> override;
    virtual auto PrmPrepareJuice() -> std::vector<Fruit> override;
    virtual auto SplPrepareJuice() -> std::vector<Fruit> override;
    // virtual void SayFruitPreference(vFruit&) override;
};