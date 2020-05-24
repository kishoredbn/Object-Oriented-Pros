#include "common.h"
#include "order_trade.h"

struct CTradeTransaction::PimpTransaction {
    tuple_transaction transaction;
    PimpTransaction(tuple_transaction transaction)
    : transaction(transaction) {}
};

CTradeTransaction::CTradeTransaction(tuple_transaction transaction) 
: m_attributes(std::make_shared<PimpTransaction>(transaction)) {
};

auto CTradeTransaction::ShowResult() const -> void {
    auto order = m_attributes->transaction;
    std::cout<<"TRADE "<<std::get<0>(order)<<" "<<std::get<1>(order)<<" "<<std::get<2>(order)<<" "<<std::get<3>(order)<<" "<<std::get<4>(order)<<" "<<std::get<5>(order)<<"\n";
}

struct CTradeOrder::PimpOrderAttributes {
    OrderAttributes order;
    PimpOrderAttributes(VcAtrVal v_order_tuple) {
        UmAtrMeta order_attr_map;
        for (auto &iter : v_order_tuple)
        {
            auto attribute_type = std::get<0>(iter);
            auto attribute_value = std::get<1>(iter);
            auto attribute_tag = GetTagType(attribute_type);
            order_attr_map[attribute_type] = MetaOrderValues(attribute_value, attribute_tag);
        }
        order = OrderAttributes(order_attr_map);
    }
    PimpOrderAttributes(UmAtrMeta um_order_tuple)
    {
        UmAtrMeta order_attr_map = um_order_tuple;
        order = OrderAttributes(order_attr_map);
    }
};

CTradeOrder::CTradeOrder(const VcAtrVal& v_order_tuple)
: m_attributes(std::make_shared<PimpOrderAttributes>(v_order_tuple))
{
}

CTradeOrder::CTradeOrder(const UmAtrMeta& um_order_tuple)
: m_attributes(std::make_shared<PimpOrderAttributes>(um_order_tuple))
{
}

auto CTradeOrder::SetOrderAttributes(std::unordered_map<Attributes, MetaOrderValues> attributes) -> void {
    for(auto &iter : attributes) m_attributes->order.metadata[iter.first] = iter.second;
}

auto CTradeOrder::GetOrderAttributes() -> std::unordered_map<Attributes, MetaOrderValues> {
    return m_attributes->order.metadata;
}

auto CTradeOrder::PivotAttribute() const -> uint64_t {
    auto metadata_price_find = m_attributes->order.metadata.find(Attributes::Price);
    if(metadata_price_find != m_attributes->order.metadata.end()) return std::get<uint64_t>(metadata_price_find->second.value);
    return 0;
}

