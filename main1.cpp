#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include "Stockmarket.h"
using namespace std;

float getExecutionPrice(StockMarket& buy, StockMarket& sell, string lastMarketPrice){
    float printLimitPrice;
    if (buy.getlimitOrMarket() == "M" && sell.getlimitOrMarket() == "M") {
        printLimitPrice = stof(lastMarketPrice);
    } else if(buy.getlimitOrMarket() == "M" && sell.getlimitOrMarket() == "L") {
        printLimitPrice = sell.getlimitPrice();
    } else {
        if(buy.getorderIndex() < sell.getorderIndex()) printLimitPrice = buy.getlimitPrice();
        else printLimitPrice = sell.getlimitPrice();
    }    
    return printLimitPrice;
}

bool checkIfIndivisibleExecutingFull(StockMarket& buy, StockMarket& sell) {
    bool retVal = false;
    if( (buy.getindOrDiv() == "I" && sell.getindOrDiv() == "D" && (buy.getquantity() <= sell.getquantity())) || 
        (buy.getindOrDiv() == "D" && sell.getindOrDiv() == "I" && (sell.getquantity() <= buy.getquantity())) || 
        (buy.getindOrDiv() == "I" && sell.getindOrDiv() == "I" && (buy.getquantity() == sell.getquantity())) ||
        (buy.getindOrDiv() == "D" && sell.getindOrDiv() == "D") ) {
        retVal = true;
    }
    return retVal;
}

bool checkIfLimitOrMarket(StockMarket& buy, StockMarket& sell, float lastMarketPrice) {
    bool retVal = false;
    if ((buy.getlimitOrMarket() == "L" && sell.getlimitOrMarket()== "L" && buy.getlimitPrice() >= sell.getlimitPrice()) || 
                (buy.getlimitOrMarket() == "M" && sell.getlimitOrMarket() == "M") ||
                (buy.getlimitOrMarket() == "M" && sell.getlimitOrMarket() == "L" ) ||
                (buy.getlimitOrMarket() == "L" && sell.getlimitOrMarket() == "M"  ) ){
                            retVal = true;
                        }
    return retVal;
}


int main(int argc, char *argv[]){
    fstream file;
    vector<string> orderVal;
    string statement;
    bool append = false;

    // file.open("orders.txt", ios::in);
    file.open(argv[1], ios::in);
    if (file.is_open()) {
        string line;
        while (getline(file, line, '\n')) {
            orderVal.push_back(line);
        }
        file.close();
    }

    vector<StockMarket> stockOrders;
    // vector<StockMarket> pairOrder;
    vector <pair<StockMarket, StockMarket>> pairOrder;

    //Put all stock orders in a vector type
    string lastMarketPrice = orderVal[0];
    cout << "lastmarket : " << lastMarketPrice <<endl;
    for (int i = 1; i < orderVal.size(); i++) {
        StockMarket s;
        s.setDetails(orderVal[i], i);
        stockOrders.push_back(s);
    }
    StockMarket buy; StockMarket sell;
    for(int i = 1; i < stockOrders.size(); i++) {
        for(int j = 0; j < i; j++) {
            // cout << i << ", " << j << endl; // Very Important
            
            //First check if buyer and seller match      
            if(stockOrders[i].getbuyerOrSeller() == "B" && stockOrders[j].getbuyerOrSeller() == "S") {
                buy = stockOrders[i]; sell = stockOrders[j];
            } else if(stockOrders[i].getbuyerOrSeller() == "S" && stockOrders[j].getbuyerOrSeller() == "B") {
                buy = stockOrders[j]; sell = stockOrders[i];
            }
            // Check if Limitprice or market price

            //If both market order high priority

            if(checkIfLimitOrMarket(buy, sell, stof(lastMarketPrice))) {
            
           
                    cout << buy.getOrderID() << " " << buy.getbuyerOrSeller() << " : " << sell.getOrderID() << " " << sell.getbuyerOrSeller() <<endl;
                   

                if(checkIfIndivisibleExecutingFull(buy, sell)) {
                    int minQuantityshare = std::min(buy.getquantity(),sell.getquantity());
                    float printLimitPrice = getExecutionPrice(buy, sell, lastMarketPrice);
                    lastMarketPrice = to_string(printLimitPrice);

                    if(minQuantityshare > 0) {
                        statement += buy.getPurchaseExecutionResult(buy, minQuantityshare, printLimitPrice);
                        statement += sell.getSellExecutionResult(sell, minQuantityshare, printLimitPrice);

                        buy.setquantity(to_string(buy.getquantity() - minQuantityshare));
                        sell.setquantity(to_string(sell.getquantity() - minQuantityshare));
                        pairOrder.push_back(make_pair(buy,sell));
                    }
                }


            }           

        }append = true;
    }

    cout << "Final" << pairOrder.size() << endl;
    for(int i = 0 ; i < pairOrder.size(); i++) {
        cout << pairOrder[i].first.getOrderID() << " " << pairOrder[i].second.getOrderID() << endl;
        cout << pairOrder[i].first.getquantity() << " " << pairOrder[i].second.getquantity() << endl;

    }

    //Add unexecuted orders
    // for (int i = 0; i < buyer.size(); i++) {
    //     if(buyer[i].getquantity() > 0) statement += buyer[i].getUnexecutionResult(buyer[i]); //If unexecuted set statement
    // }
    // for (int i = 0; i < seller.size(); i++) {
    //     if(seller[i].getquantity() > 0) statement += seller[i].getUnexecutionResult(seller[i]);
    // }


    //Print all Execution
    fstream executionFile;
    executionFile.open("execution.txt", ios::out);
    if (executionFile.is_open()) {
        executionFile << statement << endl;
        executionFile.close();
    }
    return 0;
}