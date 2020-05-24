#pragma once

#include "common.h"

enum class OrderAction : uint8_t {BUY=0, SELL, CANCEL, MODIFY, PRINT, UNKNOWN};
enum class OrderType : uint8_t {GFD=0, IOC};
enum class Tag : uint8_t {STRING, INT, ORDER_TYPE, ORDER_ACTION}; // types of order attribute 

constexpr OrderAction Exchange(OrderAction input) {
    if(input == OrderAction::SELL) return OrderAction::BUY;
    if(input == OrderAction::BUY) return OrderAction::SELL;
    return OrderAction::UNKNOWN;
}

#define ATTRIBUTE CODE(Action,    Tag::ORDER_ACTION) \
                  CODE(ActionNew, Tag::ORDER_ACTION) \
                  CODE(OrderType, Tag::ORDER_TYPE) \
                  CODE(Quantity,  Tag::INT)    \
                  CODE(Price,     Tag::INT)    \
                  CODE(OrderId,   Tag::STRING) 

#undef CODE
#define CODE(__name, __type) __name,
enum class Attributes : uint64_t { ATTRIBUTE // Expands here as enum
                                   Default };

using Atr = Attributes;

#undef CODE
#define CODE(__name, __type) case Attributes::__name: return __type;
constexpr Tag GetTagType(const Attributes attri) {
    switch(attri) {
        ATTRIBUTE // expands here as switch-case
        default: return Tag::INT;
    }
}

using OrderVariant = std::variant<std::string, uint64_t, OrderAction, OrderType>;

struct OrderMetaType {
    OrderVariant value;
    OrderMetaType() {}
    OrderMetaType(OrderVariant value): value(value) {}
};

struct MetaOrderValues : public OrderMetaType {
    Tag tag;
    void operator=(const MetaOrderValues &that) {
        value = that.value;
        tag = that.tag;
    }
    bool operator==(const MetaOrderValues &that) {
        switch (that.tag)
        {
        case Tag::INT: if(std::get<uint64_t>(value) == std::get<uint64_t>(that.value)) return true; break;
        case Tag::STRING: if(std::get<std::string>(value) == std::get<std::string>(that.value)) return true; break;
        case Tag::ORDER_TYPE: if(std::get<OrderType>(value) == std::get<OrderType>(that.value)) return true; break;
        case Tag::ORDER_ACTION: if(std::get<OrderAction>(value) == std::get<OrderAction>(that.value)) return true; break;
        }
        return false;
    }
    MetaOrderValues() {}
    MetaOrderValues(OrderMetaType orderMetaType, Tag tag) 
        : OrderMetaType(orderMetaType), tag(tag) {}
};

using UmAtrMeta = std::unordered_map<Attributes, MetaOrderValues>;
using VcAtrMeta = std::vector<std::tuple<Attributes, MetaOrderValues>>;
using VcAtrVal = std::vector<std::tuple<Attributes, OrderMetaType>>;

struct OrderAttributes {
    UmAtrMeta metadata; // order attributes
    OrderAttributes() {}
    OrderAttributes(UmAtrMeta metadata) : metadata(metadata) {}
    virtual ~OrderAttributes() {}
};

