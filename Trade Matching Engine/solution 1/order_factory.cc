#include "common.h"
#include "order_factory.h"

OrderFactory::OrderFactory(){}

spITradeOrder OrderFactory::CreateOrder(UmAtrMeta &order_atr) {
    spITradeOrder ret = nullptr;
    ret = std::make_shared<CTradeOrder>(order_atr);
    return ret;
}

OrderTransactionFactory::OrderTransactionFactory(){}

spITradeTransaction OrderTransactionFactory::CreateTransactionObj(tuple_transaction &transaction_tuple) {
    spITradeTransaction ret = nullptr; 
    ret = std::make_shared<CTradeTransaction>(transaction_tuple);
    return ret;
}
