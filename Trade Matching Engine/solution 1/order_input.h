#pragma once

class ITradeInputControl {
public:
    virtual auto InsertInput(const std::vector<VcAtrVal>&) -> void = 0;
    virtual ~ITradeInputControl() {}
};

using spITradeInputControl = std::shared_ptr<ITradeInputControl>;

class CTradeInputControl : public  ITradeInputControl {
private:
    spITradeEngine m_engine;
public:
    CTradeInputControl();
    virtual auto InsertInput(const std::vector<VcAtrVal>&) -> void override;
};