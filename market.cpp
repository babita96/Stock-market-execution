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

class StockExecution {
  string orderId;
  string buyerOrSeller;
  string limitOrMarket;
  string indOrDiv;
  string limitPrice;
  string quantity;
};

void ifBuyer(string id, string limOrMarket, string indOrDiv, string limitPrice, string quantity) {
    // order ord001 100 shares purchased at price 4.25
    fstream executionFile;
    executionFile.open("execution.txt", ios::out);
    if(executionFile.is_open()) {
        executionFile << "Order " << id << " " << quantity << " shares purchased at price " << limitPrice <<endl; 
        executionFile.close();
    }
}

void voidPrintstatement(string statement, bool append) {
    // order ord001 100 shares purchased at price 4.25
    fstream executionFile;
    
    if(append){
        executionFile.open("execution.txt", ios::app);
    } else {
        executionFile.open("execution.txt", ios::out);
    }
    if(executionFile.is_open()) {
        executionFile << statement <<endl; 
        executionFile.close();
    }
}

void getDetails(std::vector<string>& order) {
    int totalOrders= order.size();
    bool append = false;
    istringstream ss0(order[0]);
    istringstream ss(order[1]);
    string word , lastTransaction;
    vector<string> orderDetails;

    while (ss >> word) {
        orderDetails.push_back(word);
    }

    while (ss0 >> lastTransaction) {
        lastTransaction = lastTransaction;
    }

    for(int i = 0 ; i < orderDetails.size(); i++) {
        cout << i << " : " << orderDetails[i] <<endl;
    }
    string id = orderDetails[0];
    string BuyOrSell = orderDetails[1];
    string limOrMar = orderDetails[2];
    string indOrDiv = orderDetails[3];
    string limitPrice, quantity;
    if(limOrMar == "L") {
        limitPrice = orderDetails[4];
        quantity = orderDetails[5];
    } else {
        quantity = orderDetails[4];
    }

    // cout << "lastTargetVal" << lastTransaction << endl;

    if(BuyOrSell == "B" && limOrMar == "L" && indOrDiv == "I") {
        string str = "Order " + id + " " + quantity + " shares purchased at price " + limitPrice;
        voidPrintstatement(str , append);
        append = true;
    }
    if(BuyOrSell == "S" && limOrMar == "L" && indOrDiv == "I") {
        string str = "Order " + id + " " + quantity + " shares sold at price " + limitPrice;
        voidPrintstatement(str , append);
        append = true;
    }
    
    
}



void ifSeller() {

}

int main() {
    fstream file;
    vector< string > orderVal;
    string orderID, OrderType, limitOrMarket, divisibleOrder, limitPrice, targetQuantity;

    file.open("stockinput.txt", ios::in);
    if(file.is_open()) {
        string line;
        while(getline(file, line, '\n')) {
            orderVal.push_back(line);
        }
        file.close();
    }

    cout << "check" << endl;

    getDetails(orderVal);

    // system("pause>0");
    return 0;
}
