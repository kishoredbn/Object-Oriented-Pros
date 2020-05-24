#pragma once

class ITradeOrder;
using spITradeOrder = std::shared_ptr<ITradeOrder>;
class ITradeOrder {
public:
    virtual auto SetOrderAttributes(UmAtrMeta attributes) -> void = 0;
    virtual auto GetOrderAttributes() -> UmAtrMeta = 0;
    virtual auto PivotAttribute() const -> uint64_t = 0;
    virtual ~ITradeOrder(){}
};

auto cmp = [](const spITradeOrder &left, const spITradeOrder &right) { return left->PivotAttribute() < right->PivotAttribute(); };
using PqspIA = std::priority_queue<spITradeOrder, std::vector<spITradeOrder>, decltype(cmp)>;

class ITradeTransaction {
public:
    virtual auto ShowResult() const -> void = 0;
    virtual ~ITradeTransaction(){}
};
using spITradeTransaction = std::shared_ptr<ITradeTransaction>;

class CTradeOrder : public ITradeOrder {
private:
    struct PimpOrderAttributes;
    std::shared_ptr<PimpOrderAttributes> m_attributes;
public:
    CTradeOrder(){}
    CTradeOrder(const VcAtrVal&);
    CTradeOrder(const UmAtrMeta&);
    virtual auto SetOrderAttributes(UmAtrMeta attributes) -> void override;
    virtual auto GetOrderAttributes() -> UmAtrMeta override;
    virtual auto PivotAttribute() const -> uint64_t override;
};

using tuple_transaction = std::tuple<std::string, uint64_t, uint64_t, std::string, uint64_t, uint64_t>;
class CTradeTransaction : public ITradeTransaction {
private:
    struct PimpTransaction;
    std::shared_ptr<PimpTransaction> m_attributes;
public:
    CTradeTransaction(tuple_transaction);
    virtual auto ShowResult() const -> void override;
};
