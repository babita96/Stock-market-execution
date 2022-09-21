#include "Stockmarket.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <array>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>

using namespace std;

string StockMarket::getorderIndex(){
    return orderIndex;
}

string StockMarket::getOrderID() {
    return orderId;
}

string StockMarket::getbuyerOrSeller() {
    return buyerOrSeller;
}

string StockMarket::getlimitOrMarket() const{
    return limitOrMarket;
}

string StockMarket::getindOrDiv() {
    return indOrDiv;
}

float StockMarket::getlimitPrice() const {
    return stof(limitPrice);
}

int StockMarket::getquantity() {
    return stoi(quantity);
}

void StockMarket::setquantity(string quantityVal) {
    quantity = quantityVal;
}

void StockMarket::setDetails(string orderVal, int index) {
    istringstream ss(orderVal);
    string word;
    vector<string> orderDetails;

    while (ss >> word) {
        orderDetails.push_back(word);
    }

    orderIndex = index;
    orderId = orderDetails[0];
    buyerOrSeller = orderDetails[1];
    limitOrMarket = orderDetails[2];
    indOrDiv = orderDetails[3];
    if(limitOrMarket == "L") {
        limitPrice = orderDetails[4];
        quantity = orderDetails[5];
    } else {
        quantity = orderDetails[4];
    }
    
}

string StockMarket::precision(float price, const int val) {
    ostringstream out;
    out.precision(val);
    out << std::fixed << price;
    return out.str();
}

string StockMarket :: getPurchaseExecutionResult(StockMarket s1, int quantityshare, float finalPrice) {
    return "order " + s1.getOrderID() + " " + to_string(quantityshare) + " shares purchased at price " + precision(finalPrice,2) + "\n";
}

string StockMarket :: getSellExecutionResult(StockMarket s1, int quantityshare, float finalPrice) {
    return "order " + s1.getOrderID() + " " + to_string(quantityshare) + " shares sold at price " + precision(finalPrice,2) + "\n";
}

string StockMarket :: getUnexecutionResult(StockMarket s1) {
    return "order " + s1.getOrderID() + " " + to_string(s1.getquantity()) + " shares unexecuted" + "\n";
}