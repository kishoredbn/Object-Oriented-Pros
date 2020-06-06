#pragma once

class OrderFactory {
private:
public:
    OrderFactory();
    spITradeOrder CreateOrder(UmAtrMeta&);
};

class OrderTransactionFactory {
private:
public:
    OrderTransactionFactory();
    spITradeTransaction CreateTransactionObj(tuple_transaction&);
};