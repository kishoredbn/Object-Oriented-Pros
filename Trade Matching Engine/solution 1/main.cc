#include "common.h"

int main()
{
    spITradeInputControl control = std::make_shared<CTradeInputControl>();
    control->InsertInput({ // taking hardcoded input (can also be taken from standard input stream)
            {{Atr::Action, {OrderAction::BUY}}, {Atr::OrderType, {OrderType::GFD}}, {Atr::Price, {1000}}, {Atr::Quantity, {10}}, {Atr::OrderId, {"order1"}}},
            {{Atr::Action, {OrderAction::SELL}}, {Atr::OrderType, {OrderType::GFD}}, {Atr::Price, {900}}, {Atr::Quantity, {10}}, {Atr::OrderId, {"order2"}}},
            {{Atr::Action, {OrderAction::BUY}}, {Atr::OrderType, {OrderType::GFD}}, {Atr::Price, {1000}}, {Atr::Quantity, {10}}, {Atr::OrderId, {"order3"}}},
            {{Atr::Action, {OrderAction::BUY}}, {Atr::OrderType, {OrderType::GFD}}, {Atr::Price, {1100}}, {Atr::Quantity, {10}}, {Atr::OrderId, {"order4"}}},
            {{Atr::Action, {OrderAction::BUY}}, {Atr::OrderType, {OrderType::GFD}}, {Atr::Price, {1050}}, {Atr::Quantity, {10}}, {Atr::OrderId, {"order5"}}},
            {{Atr::Action, {OrderAction::MODIFY}}, {Atr::OrderId, {"order4"}}, {Atr::ActionNew, {OrderAction::BUY}}, {Atr::Price, {1110}}, {Atr::Quantity, {20}}},
            {{Atr::Action, {OrderAction::SELL}}, {Atr::OrderType, {OrderType::GFD}}, {Atr::Price, {1200}}, {Atr::Quantity, {20}}, {Atr::OrderId, {"order6"}}},
            {{Atr::Action, {OrderAction::SELL}}, {Atr::OrderType, {OrderType::GFD}}, {Atr::Price, {1250}}, {Atr::Quantity, {20}}, {Atr::OrderId, {"order7"}}},
            {{Atr::Action, {OrderAction::PRINT}}}
        });

    return 0;
}
