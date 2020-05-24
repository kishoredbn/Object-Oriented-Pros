#include "common.h"
#include "trade_engine.h"

struct CTradeEngine::PimpAttribute {
    std::vector<spITradeOrder> orders;
    std::vector<spITradeTransaction> trade_orders;
};

CTradeEngine::CTradeEngine()
    : m_attribute(std::make_shared<PimpAttribute>()) {}

auto CTradeEngine::PerformTrade(spITradeOrder order) -> void {

    if(!order) return;

    auto order_obj = std::dynamic_pointer_cast<CTradeOrder>(order);
    auto order_atr = order_obj->GetOrderAttributes();
    auto order_atr_find = order_atr.find(Attributes::Action);

    if(order_atr_find == order_atr.end()) return;

    auto order_atr_val_var = order_atr_find->second.value;
    auto order_atr_val = std::get<OrderAction>(order_atr_val_var);

    switch (order_atr_val)
    {
        case OrderAction::BUY: PerformTransaction(order_atr); break;
        case OrderAction::SELL: PerformTransaction(order_atr); break;
        case OrderAction::PRINT: GetAllOrderLists(); break;
        case OrderAction::CANCEL: PerformCancel(order_atr); break;
        case OrderAction::MODIFY: PerformModify(order_atr); break;
        default: break;
    }
}

auto CTradeEngine::PerformExchangeOrders(UmExchange &exchange_map, OrderAction ledger_curr_order_type) -> void {

    auto &buying_order = exchange_map[OrderAction::BUY]; // reference to BUY order from exchange map
    uint64_t *buying_order_price = std::get<0>(buying_order); // reference to map order price buying
    uint64_t *buying_order_quantity = std::get<1>(buying_order); // reference to map order quantity buying

    auto &selling_order = exchange_map[OrderAction::SELL]; // reference to SELL order from exchange map
    uint64_t *selling_order_price = std::get<0>(selling_order); // reference to map order price selling
    uint64_t *selling_order_quantity = std::get<1>(selling_order); // reference to map order quantity selling

    // move from reference type to value type for calculations
    uint64_t buy_quantity  = (*buying_order_quantity);
    uint64_t sell_quantity = (*selling_order_quantity);

    // buying price more than cost price
    if(*buying_order_price  >= *selling_order_price) {
        uint64_t min_quantity = ( buy_quantity > sell_quantity ) ? sell_quantity : buy_quantity ;
        buy_quantity -= min_quantity;
        sell_quantity -= min_quantity;

        *buying_order_quantity = buy_quantity;
        *selling_order_quantity = sell_quantity;

        // make an enry to the transaction table
        // ledger order details first, followed by new order details
        tuple_transaction transaction_tuple = std::make_tuple(*std::get<2>(exchange_map[ledger_curr_order_type]), // order id
                                                              *std::get<0>(exchange_map[ledger_curr_order_type]), // price of orders
                                                              min_quantity,                                       // quantity exchanged
                                                              *std::get<2>(exchange_map[Exchange(ledger_curr_order_type)]), // order id
                                                              *std::get<0>(exchange_map[Exchange(ledger_curr_order_type)]), // price of orders
                                                              min_quantity);                                                // quantity exchanged
        m_attribute->trade_orders.emplace_back(std::make_shared<CTradeTransaction>(transaction_tuple));
    }
}

auto CTradeEngine::PerformTransaction(UmAtrMeta order_atr) -> void {

    m_attribute->trade_orders.clear();

    auto order_atr_action = order_atr[Attributes::Action];
    auto order_atr_action_val = std::get<OrderAction>(order_atr_action.value);
    auto exchange_type = Exchange(order_atr_action_val);

    auto &order_price = std::get<uint64_t>(order_atr[Attributes::Price].value);
    auto &order_type = std::get<OrderType>(order_atr[Attributes::OrderType].value);
    auto &order_quantity = std::get<uint64_t>(order_atr[Attributes::Quantity].value);
    auto &order_orderid = std::get<std::string>(order_atr[Attributes::OrderId].value);

    VOrderIter remove_orders;
    UmExchange price_point_map;
    price_point_map[order_atr_action_val] = {&order_price, &order_quantity, &order_orderid};
    for(auto iter = m_attribute->orders.begin(); iter != m_attribute->orders.end(); iter++) {
        auto order_list_each = std::dynamic_pointer_cast<CTradeOrder>(*iter);
        auto order_list_atr = order_list_each->GetOrderAttributes();

        auto order_list_find = order_list_atr.find(Attributes::Action);
        if(order_list_find != order_list_atr.end()) {

            auto list_order_type = std::get<OrderAction>(order_list_find->second.value);
            if(list_order_type == exchange_type) { // check if exchange possible

                auto &list_price = std::get<uint64_t>(order_list_atr[Attributes::Price].value);
                auto &list_quantity = std::get<uint64_t>(order_list_atr[Attributes::Quantity].value);
                auto &list_orderid = std::get<std::string>(order_list_atr[Attributes::OrderId].value);

                price_point_map[list_order_type] = {&list_price, &list_quantity, &list_orderid};

                PerformExchangeOrders(price_point_map, list_order_type);

                if(list_quantity == 0) remove_orders.emplace_back(iter);
                if(order_quantity == 0) break;

                price_point_map.erase(price_point_map.find(list_order_type));
            }
        }
    }

    if(order_quantity && order_type != OrderType::IOC) m_attribute->orders.emplace_back(std::make_shared<CTradeOrder>(order_atr));
    for(auto &iter : remove_orders) m_attribute->orders.erase(iter);

    GetTransactionOutput();
}

auto CTradeEngine::PerformCancel(UmAtrMeta order_atr) -> void {
    auto give_order_iter = order_atr.find(Attributes::OrderId);
    if(give_order_iter == order_atr.end()) return;

    auto give_order_id = std::get<std::string>(give_order_iter->second.value);
    auto find_clear_match = std::find_if(std::begin(m_attribute->orders), std::end(m_attribute->orders), [&](auto &iter){
        auto iter_order = std::dynamic_pointer_cast<CTradeOrder>(iter);
        auto iter_attr_map = iter_order->GetOrderAttributes();
        auto iter_attr_find = iter_attr_map.find(Attributes::OrderId);
        if(iter_attr_find == iter_attr_map.end()) return false;
        auto iter_attr_order_id = std::get<std::string>(iter_attr_find->second.value);
        if(iter_attr_order_id == give_order_id) return true;
        return false;
    });

    if(find_clear_match == m_attribute->orders.end()) return;

    m_attribute->orders.erase(find_clear_match);
}

auto CTradeEngine::PerformModify(UmAtrMeta order_atr) -> void {
    auto given_order_iter = order_atr.find(Attributes::OrderId);
    if(given_order_iter == order_atr.end()) return;

    auto given_order_id = std::get<std::string>(given_order_iter->second.value);
    auto find_clear_match = std::find_if(std::begin(m_attribute->orders), std::end(m_attribute->orders), [&](auto &iter) {
        auto iter_order = std::dynamic_pointer_cast<CTradeOrder>(iter);
        assert(iter_order);

        auto iter_attr_map = iter_order->GetOrderAttributes();
        auto iter_attr_find = iter_attr_map.find(Attributes::OrderId);

        if(iter_attr_find == iter_attr_map.end()) return false;

        auto iter_attr_order_id = std::get<std::string>(iter_attr_find->second.value);
        if(iter_attr_order_id == given_order_id) return true;
        return false;
    });

    if(find_clear_match == m_attribute->orders.end()) return;

    UmAtrMeta new_order;
    auto order_atr_change = std::dynamic_pointer_cast<CTradeOrder>(*find_clear_match);
    auto order_atr_change_map = order_atr_change->GetOrderAttributes();

    new_order[Attributes::OrderType] = order_atr_change_map[Attributes::OrderType];
    new_order[Attributes::Action] = order_atr[Attributes::ActionNew];
    new_order[Attributes::Price] = order_atr[Attributes::Price];
    new_order[Attributes::Quantity] = order_atr[Attributes::Quantity];
    new_order[Attributes::OrderId] = order_atr[Attributes::OrderId];

    m_attribute->orders.erase(find_clear_match);
    
    spITradeOrder new_order_obj = std::make_shared<CTradeOrder>(new_order);
    m_attribute->orders.emplace_back(new_order_obj);
}

auto CTradeEngine::GetAllOrderLists() -> void {
    PqspIA sell_price_max_heap(cmp);
    PqspIA buy_price_max_heap(cmp);

    for(auto &iter : m_attribute->orders) {
        auto list_order = std::dynamic_pointer_cast<CTradeOrder>(iter);
        auto list_order_arg = list_order->GetOrderAttributes();
        switch (std::get<OrderAction>(list_order_arg[Attributes::Action].value))
        {
            case OrderAction::BUY: buy_price_max_heap.emplace(iter); break;
            case OrderAction::SELL: sell_price_max_heap.emplace(iter); break;
            default: break;
        }
    }

    std::cout<<"SELL:\n";
    while(sell_price_max_heap.size()) {
        auto order_obj = std::dynamic_pointer_cast<CTradeOrder>(sell_price_max_heap.top());
        auto order_arg = order_obj->GetOrderAttributes();
        sell_price_max_heap.pop();

        std::cout<< std::get<uint64_t>(order_arg[Attributes::Price].value) <<" "<< std::get<uint64_t>(order_arg[Attributes::Quantity].value)<<"\n";
    }

    std::cout<<"BUY:\n";
    while(buy_price_max_heap.size()) {
        auto order_obj = std::dynamic_pointer_cast<CTradeOrder>(buy_price_max_heap.top());
        auto order_arg = order_obj->GetOrderAttributes();
        buy_price_max_heap.pop();

        std::cout<< std::get<uint64_t>(order_arg[Attributes::Price].value) <<" "<< std::get<uint64_t>(order_arg[Attributes::Quantity].value)<<"\n";
    }
}

auto CTradeEngine::GetTransactionOutput() -> void {
    for (auto &iter : m_attribute->trade_orders)
    {
        auto iter_obj = std::dynamic_pointer_cast<CTradeTransaction>(iter);
        iter_obj->ShowResult();
    }
}

