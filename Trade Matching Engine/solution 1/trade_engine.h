#pragma once

class ITradeEngine {
public:
    virtual auto PerformTrade(spITradeOrder) -> void = 0;
    virtual ~ITradeEngine() {}
};

using spITradeEngine = std::shared_ptr<ITradeEngine>;

class CTradeEngine : public  ITradeEngine {
private:
    struct PimpAttribute;
    std::shared_ptr<PimpAttribute> m_attribute;

    virtual auto PerformTransaction(UmAtrMeta) -> void;
    virtual auto PerformCancel(UmAtrMeta) -> void;
    virtual auto PerformModify(UmAtrMeta) -> void;
    virtual auto GetTransactionOutput() -> void;
    virtual auto GetAllOrderLists() -> void;
public:
    CTradeEngine();
    virtual auto PerformTrade(spITradeOrder orderAtr) -> void override;
    virtual ~CTradeEngine() {}
};
