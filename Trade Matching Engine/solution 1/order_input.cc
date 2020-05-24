#include "common.h"
#include "order_input.h"

CTradeInputControl::CTradeInputControl() 
: m_engine(std::make_shared<CTradeEngine>()) {
}

auto CTradeInputControl::InsertInput(const std::vector<VcAtrVal>& vvav) -> void {
    for (auto &v_iter : vvav) {
        VcAtrVal vac;
        for (auto &&iter : v_iter)
        {
            auto &attribute = std::get<Attributes>(iter);
            auto &meta_data = std::get<OrderMetaType>(iter);
            vac.emplace_back(std::make_tuple(attribute, meta_data));
        }
        spITradeOrder order = std::make_shared<CTradeOrder>(vac);
        m_engine->PerformTrade(order);
    }
}