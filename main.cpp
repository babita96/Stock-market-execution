#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <functional>
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
        (buy.getlimitOrMarket() == "M" && sell.getlimitOrMarket() == "L") ||
        (buy.getlimitOrMarket() == "L" && sell.getlimitOrMarket() == "M") ){
            retVal = true;
        }
    return retVal;
}

int main(int argc, char *argv[]){
    fstream file;
    vector<string> orderVal;
    vector <StockMarket> buyer, seller, allOrder;
    string statement, printVal;
    bool append = false;

    file.open(argv[1], ios::in);
    if (file.is_open()) {
        string line;
        while (getline(file, line, '\n')) {
            orderVal.push_back(line);
        }
        file.close();
    }

    //Put all stock orders in a vector type
    string lastMarketPrice = orderVal[0];
    for (int i = 1; i < orderVal.size(); i++) {
        StockMarket s;
        s.setDetails(orderVal[i], i);
        allOrder.push_back(s);
        if(s.getbuyerOrSeller() == "B") buyer.push_back(s);
        else if(s.getbuyerOrSeller() == "S") seller.push_back(s);
    }

    // vector<StockMarket> newvec;
    // for (vector<StockMarket>::iterator it=buyer.begin(); it!=buyer.end();) {
    //     if (it->getlimitOrMarket() == "M") {
    //         newvec.push_back(*it);
    //         it = buyer.erase(it);
    //     } else ++it;
    // }

    // sort(buyer.begin( ), buyer.end( ), [ ]( const StockMarket& lhs, const StockMarket& rhs ) {
    //         return (lhs.getlimitPrice() > rhs.getlimitPrice());
    // });

    // buyer.insert(buyer.begin(), newvec.begin(), newvec.end());

//Testing
for(int i = 0; i < allOrder.size(); i++) {
    if(allOrder[i].getlimitOrMarket() == "M") {
        if(allOrder[i].getbuyerOrSeller () == "B") {
            printVal += allOrder[i].getOrderID() +  " "  + "M" + "    " + to_string(allOrder[i].getquantity());
        } else {
            printVal += "\t\t\t\t" + allOrder[i].getOrderID() +  " "  + "M" + "    " + to_string(allOrder[i].getquantity());
        }

    } else {
        if(allOrder[i].getbuyerOrSeller () == "B") {
            printVal += allOrder[i].getOrderID() +  " "  + allOrder[i].precision(allOrder[i].getlimitPrice()) + " " + to_string(allOrder[i].getquantity());
        } else {
            printVal += "\t\t\t\t" + allOrder[i].getOrderID() +  " "  + allOrder[i].precision(allOrder[i].getlimitPrice()) + " " + to_string(allOrder[i].getquantity());
        }
    }
    printVal += "\n";
    
}
    // std::for_each(buyer.begin(), buyer.end(), [&](StockMarket& buy) {
    //     if(buy.getlimitOrMarket() == "M") {
    //         printVal += buy.getOrderID() + " "  + "M" + " " + to_string(buy.getquantity())  + "\t\t\t";
    //     } else {
    //         printVal += buy.getOrderID() + " "  + buy.precision(buy.getlimitPrice(),2) + " " + to_string(buy.getquantity())  + "\t\t\t";
    //     }
    // });

    // std::for_each(seller.begin(), seller.end(), [&](StockMarket& sell) {
    //     if(sell.getlimitOrMarket() == "M") {
    //         printVal += sell.getOrderID() + " "  + "M" + " "  +  to_string(sell.getquantity()) + "\n";
    //     } else {
    //         printVal += sell.getOrderID() + " "  + sell.precision(sell.getlimitPrice(),2) + " "  +  to_string(sell.getquantity()) + "\n";
    //     }
    // });
    //  printVal += buy.getOrderID() + " "  + buy.precision(printLimitPrice,2) + " " + to_string(minQuantityshare)  + "\t\t\t";
    //  printVal += sell.getOrderID() + " "  + sell.precision(printLimitPrice,2) + " "  +  to_string(minQuantityshare) + "\n";


    // std::for_each(seller.begin(), seller.end(), [&](StockMarket& sell) {

    //     if(sell.getquantity()>0) {

    //         std::for_each(buyer.begin(), buyer.end(), [&](StockMarket& buy) {

    std::for_each(buyer.begin(), buyer.end(), [&](StockMarket& buy) {   
        // printVal += buy.getOrderID() + " "  + buy.precision(buy.getlimitPrice(),2) + " " + to_string(buy.getquantity())  + "\t\t\t";      

        if(buy.getquantity()>0) {

            std::for_each(seller.begin(), seller.end(), [&](StockMarket& sell) {
                // printVal += sell.getOrderID() + " "  + sell.precision(sell.getlimitPrice(),2) + " "  +  to_string(sell.getquantity()) + "\n";

                 
                if(checkIfLimitOrMarket(buy, sell, stof(lastMarketPrice))) {

                    if(checkIfIndivisibleExecutingFull(buy, sell)) {

                        int minQuantityshare = std::min(buy.getquantity(),sell.getquantity());
                        float printLimitPrice = getExecutionPrice(buy, sell, lastMarketPrice);
                        lastMarketPrice = to_string(printLimitPrice);

                        if(minQuantityshare > 0) {

                            statement += buy.getPurchaseExecutionResult(buy, minQuantityshare, printLimitPrice);
                            statement += sell.getSellExecutionResult(sell, minQuantityshare, printLimitPrice);  

                            buy.setquantity(to_string(buy.getquantity() - minQuantityshare));
                            sell.setquantity(to_string(sell.getquantity() - minQuantityshare));

                        }
                     }
                 }
             });
         }
     });
    cout << "\nLast trading price: " << orderVal[0] <<endl;
    cout << "Buy" <<"\t\t\t\t" << "Sell" <<endl;
    cout << "-------------------------------------------------" <<endl;
    cout << printVal;

    for (int i = 0; i < buyer.size(); i++) {
        if(buyer[i].getquantity() > 0) statement += buyer[i].getUnexecutionResult(buyer[i]); //If unexecuted set statement
    }
    for (int i = 0; i < seller.size(); i++) {
        if(seller[i].getquantity() > 0) statement += seller[i].getUnexecutionResult(seller[i]);
    }

    fstream executionFile;
    executionFile.open("executions.txt", ios::out);
    if (executionFile.is_open()) {
        executionFile << statement << endl;
        executionFile.close();
    }
    return 0;
}