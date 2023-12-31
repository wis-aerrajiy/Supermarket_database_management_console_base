#ifndef MANAGMENT_SYSTEM_HPP
#define MANAGMENT_SYSTEM_HPP

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include "Bill.Info.hpp"

using namespace std;

class ManagmentSystem {
    private:
        string  db_sperator;
        string  databasePath;
        fstream databaseFile;
        vector <BillInfo> BillInfos;

    public:
        ManagmentSystem(string dbaPath);
        void        ProgrameHeader();
        void        OpenStream(int Permissions);
        void        StoreData(string ItemName, string ItemManufacturingDate, string ItemPrice, string ItemTaxPercent, string ItemQuantity, string ItemNumber, string ItemCategory, string ItemDiscount);
        void        ReadData(string &readline, string fieldName, int type);

        void        ReadDataAndParsIt();
        BillInfo    parseInfo(std::string info);
        void        ShowBillReport();
        void        displayBillReport();
        int         ShowBanner(string title);
        void        AddMethod();
        void        EditMethod();
        void        DeleteMethod();
        void        Process();
        void        ShowItemDetails();
};

#endif