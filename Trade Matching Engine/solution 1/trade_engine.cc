#include "common.h"
#include "trade_engine.h"

struct CTradeEngine::PimpAttribute {
    std::vector<spITradeOrder> orders;
    std::vector<spITradeTransaction> trade_orders;
};

CTradeEngine::CTradeEngine()
    : m_attribute(std::make_shared<PimpAttribute>()) {}

// Calls specific trade actions based on user input
auto CTradeEngine::PerformTrade(spITradeOrder order) -> void {

    if(!order) return;

    auto order_atr = order->GetOrderAttributes();
    auto order_atr_find = order_atr.find(Attributes::Action); // check used input for action

    if(order_atr_find == order_atr.end()) return; // if not a valid input exit function

    auto order_atr_val_var = order_atr_find->second.value;
    auto order_atr_val = std::get<OrderAction>(order_atr_val_var); // get the action value

    switch (order_atr_val) // call specific function based on user input
    {
        case OrderAction::BUY: PerformTransaction(order_atr); break;
        case OrderAction::SELL: PerformTransaction(order_atr); break;
        case OrderAction::PRINT: GetAllOrderLists(); break;
        case OrderAction::CANCEL: PerformCancel(order_atr); break;
        case OrderAction::MODIFY: PerformModify(order_atr); break;
        default: break;
    }
}

// For every BUY/SELL actions, check if a trade is possible or not
// If trade is NOT possible, then make an entry to the ledger for future use
// If trade is possible, perform the trade and remove orders from the ledger
// If trade is partially-possible, then update ledger accordingly
auto CTradeEngine::PerformTransaction(UmAtrMeta order_atr) -> void {

    m_attribute->trade_orders.clear(); // remove any previous transaction history

    auto order_atr_action = order_atr[Attributes::Action];
    auto order_atr_action_val = std::get<OrderAction>(order_atr_action.value); // check the new order action type
    auto exchange_type = Exchange(order_atr_action_val); // get the exchange action type, ie. if BUY -> SELL, SELL -> BUY

    // get all attributes/parameters of the new orders
    auto &order_price = std::get<uint64_t>(order_atr[Attributes::Price].value);
    auto &order_type = std::get<OrderType>(order_atr[Attributes::OrderType].value);
    auto &order_quantity = std::get<uint64_t>(order_atr[Attributes::Quantity].value);
    auto &order_orderid = std::get<std::string>(order_atr[Attributes::OrderId].value);

    VOrderIter remove_orders; // upon success completion of orders, make an entry of iters here to remove them from ledge later
    UmExchange price_point_map; // helper reference map to exchange BUY & SELL orders, using references to orders
    price_point_map[order_atr_action_val] = {&order_price, &order_quantity, &order_orderid}; // enter new order details to reference map
    for(auto iter = m_attribute->orders.begin(); iter != m_attribute->orders.end(); iter++) { // for all orders in the ledger
        auto order_list_atr = (*iter)->GetOrderAttributes(); // get the order attributes

        auto order_list_find = order_list_atr.find(Attributes::Action); // check for specific action types
        if(order_list_find != order_list_atr.end()) {

            auto list_order_type = std::get<OrderAction>(order_list_find->second.value);
            if(list_order_type == exchange_type) { // check if exchange possible

                // get all attributes/parameters of each ledge orders
                auto &list_price = std::get<uint64_t>(order_list_atr[Attributes::Price].value);
                auto &list_quantity = std::get<uint64_t>(order_list_atr[Attributes::Quantity].value);
                auto &list_orderid = std::get<std::string>(order_list_atr[Attributes::OrderId].value);

                // enter ledger order details to reference map
                price_point_map[list_order_type] = {&list_price, &list_quantity, &list_orderid};

                // Perform order exchange
                PerformExchangeOrders(price_point_map, list_order_type);

                if(list_quantity == 0) remove_orders.emplace_back(iter); // if ledger order is done, then mark for deletion
                if(order_quantity == 0) break; // if new order is complete then break

                price_point_map.erase(price_point_map.find(list_order_type));
            }
        }
    }

    // if new order is NNOT complete and is not of type IOC, then make an entry to the ledger
    if(order_quantity && order_type != OrderType::IOC) m_attribute->orders.emplace_back(std::make_shared<CTradeOrder>(order_atr));
    for(auto &iter : remove_orders) m_attribute->orders.erase(iter); // remove the existing completed orders from the ledger

    GetTransactionOutput(); // output transaction details, if any occured
}

// To CANCEL an order from the ledger
auto CTradeEngine::PerformCancel(UmAtrMeta order_atr) -> void {
    auto find_clear_match = GetOrderLedgerItrator(order_atr); // get ledger index iterator

    if(find_clear_match == m_attribute->orders.end()) return; // if not valid exit
    m_attribute->orders.erase(find_clear_match); // or, remove an order from the ledger
}

// To MODIFY an order in the ledger
auto CTradeEngine::PerformModify(UmAtrMeta order_atr) -> void {
    auto find_clear_match = GetOrderLedgerItrator(order_atr); // get ledger index iterator

    if(find_clear_match == m_attribute->orders.end()) return; // if not valid exit

    UmAtrMeta new_order; // create a new order attribute map to store new order details
    auto order_atr_change_map = (*find_clear_match)->GetOrderAttributes();

    // set all new order attribute details to attribute map
    new_order[Attributes::OrderType] = order_atr_change_map[Attributes::OrderType];
    new_order[Attributes::Action] = order_atr[Attributes::ActionNew];
    new_order[Attributes::Price] = order_atr[Attributes::Price];
    new_order[Attributes::Quantity] = order_atr[Attributes::Quantity];
    new_order[Attributes::OrderId] = order_atr[Attributes::OrderId];

    m_attribute->orders.erase(find_clear_match); // remove old order entry
    
    // Remember: we work with only abstract type, NOT concrete types
    spITradeOrder new_order_obj = std::make_shared<CTradeOrder>(new_order); // create new order abstract objects
    m_attribute->orders.emplace_back(new_order_obj); // insert abstract type to the ledger
}

// Perform order exchange on order "references"
// any changes on the order attributes directly changes orders in the ledger
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

// iterate over the ledge to find a specific order, searched based on order id and then return the iterator if found
auto CTradeEngine::GetOrderLedgerItrator(UmAtrMeta& order_atr) -> OrderIter {
    auto find_clear_match = std::end(m_attribute->orders);

    auto give_order_iter = order_atr.find(Attributes::OrderId);
    if(give_order_iter == order_atr.end()) return find_clear_match;

    auto give_order_id = std::get<std::string>(give_order_iter->second.value); // get order id of the requested order

    // iterate over the ledger and check for the order
    find_clear_match = std::find_if(std::begin(m_attribute->orders), std::end(m_attribute->orders), [&](auto &iter){
        assert(iter);

        auto iter_attr_map = iter->GetOrderAttributes();
        auto iter_attr_find = iter_attr_map.find(Attributes::OrderId);

        if(iter_attr_find == iter_attr_map.end()) return false;

        auto iter_attr_order_id = std::get<std::string>(iter_attr_find->second.value);
        if(iter_attr_order_id == give_order_id) return true;
        return false;
    });

    return find_clear_match;
}

// Get list of all the orders currently in the ledge
auto CTradeEngine::GetAllOrderLists() -> void {
    PqspIA sell_price_max_heap(cmp); // sort SELL order by price
    PqspIA buy_price_max_heap(cmp); // sort BUY order by price

    for(auto &iter : m_attribute->orders) {
        auto list_order_arg = iter->GetOrderAttributes();
        switch (std::get<OrderAction>(list_order_arg[Attributes::Action].value))
        {
            case OrderAction::BUY: buy_price_max_heap.emplace(iter); break; // BUY orders goes to buy max heap
            case OrderAction::SELL: sell_price_max_heap.emplace(iter); break; // SELL orders goes to sell max heap
            default: break;
        }
    }

    // display SELL orders 
    std::cout<<"SELL:\n";
    while(sell_price_max_heap.size()) {
        auto order_obj = sell_price_max_heap.top();
        auto order_arg = order_obj->GetOrderAttributes();
        sell_price_max_heap.pop();

        std::cout<< std::get<uint64_t>(order_arg[Attributes::Price].value) 
            <<" "<< std::get<uint64_t>(order_arg[Attributes::Quantity].value)<<"\n";
    }

    // display BUY orders
    std::cout<<"BUY:\n";
    while(buy_price_max_heap.size()) {
        auto order_obj = buy_price_max_heap.top();
        auto order_arg = order_obj->GetOrderAttributes();
        buy_price_max_heap.pop();

        std::cout<< std::get<uint64_t>(order_arg[Attributes::Price].value) 
            <<" "<< std::get<uint64_t>(order_arg[Attributes::Quantity].value)<<"\n";
    }
}

// display call the transaction details.
auto CTradeEngine::GetTransactionOutput() -> void {
    for (auto &iter : m_attribute->trade_orders)
    {
        iter->ShowResult(); // transaction objects is responsible for displaying output
    }
}

