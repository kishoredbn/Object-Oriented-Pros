#pragma once

class ITradeEngine {
public:
    virtual auto PerformTrade(spITradeOrder) -> void = 0; // simple interface method to taken in input and simultaneously process output
    virtual ~ITradeEngine() {}
};

using spITradeEngine = std::shared_ptr<ITradeEngine>;

class CTradeEngine : public  ITradeEngine {
private:
    using OrderIter = std::vector<spITradeOrder>::iterator;
    using VOrderIter = std::vector<OrderIter>;
    using UmExchange = std::unordered_map<OrderAction, std::tuple<uint64_t*, uint64_t*, std::string*>>;

    struct PimpAttribute;
    std::shared_ptr<PimpAttribute> m_attribute;

    virtual auto PerformTransaction(UmAtrMeta) -> void;
    virtual auto PerformExchangeOrders(UmExchange&, OrderAction) -> void;
    virtual auto PerformCancel(UmAtrMeta) -> void;
    virtual auto PerformModify(UmAtrMeta) -> void;
    virtual auto GetOrderLedgerItrator(UmAtrMeta&) -> OrderIter;
    virtual auto GetTransactionOutput() -> void;
    virtual auto GetAllOrderLists() -> void;
public:
    CTradeEngine();
    virtual auto PerformTrade(spITradeOrder orderAtr) -> void override;
    virtual ~CTradeEngine() {}
};
