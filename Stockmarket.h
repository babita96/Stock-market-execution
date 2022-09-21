#ifndef STOCKMARKET_H_
#define STOCKMARKET_H_
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdio.h>

using namespace std;
using std::vector;

class StockMarket {

public:
	// StockMarket();
	// ~StockMarket();
    string getorderIndex();
    string getOrderID();
    string getbuyerOrSeller();
    string getlimitOrMarket() const;
    string getindOrDiv();
    float getlimitPrice() const;
    int getquantity();
    void setquantity(string quantityVal);
    void setDetails(string order, int index);
    string precision(float f, const int n = 2);
    string getPurchaseExecutionResult(StockMarket s1, int quantityShare, float finalPrice);
    string getSellExecutionResult(StockMarket s1, int quantityShare, float finalPrice);
    string getUnexecutionResult(StockMarket s1);

    bool operator()(const StockMarket& x, const StockMarket& y) const  
    {
        return x.getlimitPrice() < y.getlimitPrice();
    }


protected:
private:
    string orderIndex;
    string orderId;
    string buyerOrSeller;
    string limitOrMarket;
    string indOrDiv;
    string limitPrice;
    string quantity;
    string marketPrice;
};

#endif /* STOCKMARKET_H_ */