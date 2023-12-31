#include "ManagmentSystem.hpp"

enum Process 
{
    Add = 1, 
    Edit = 2, 
    Remove = 3
};

ManagmentSystem::ManagmentSystem(string dbPath)
{
    this->db_sperator = "_______________________________";
    this->databasePath = dbPath;
}

void ManagmentSystem::ProgrameHeader()
{
    std::cout << "\x1B[2J\x1B[H";
    std::cout << std::setw(5) << std::right << '\0' << "_________________________________________" << endl;
    std::cout << std::setw(5) << std::right << '\0' << "[         Super Market Billing          ]" << std::endl;
    std::cout << std::setw(5) << std::right << '\0' << "_________________________________________" << endl
              << endl;
}

void ManagmentSystem::OpenStream(int Permissions)
{
    this->databaseFile.close();
    this->databaseFile.open(this->databasePath, Permissions);
    if (!this->databaseFile.good())
        throw std::runtime_error("The program crashed due can't open database file");
}

BillInfo ManagmentSystem::parseInfo(std::string info)
{
    BillInfo currentBill;
    std::istringstream iss(info);
    std::string line;

    while (std::getline(iss, line))
    {
        std::istringstream lineStream(line);
        std::string key, value;

        if (std::getline(lineStream, key, ':'))
        {
            key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
            if (std::getline(lineStream, value))
            {
                size_t start = value.find_first_not_of(" ");
                if (start != std::string::npos)
                    value = value.substr(start);
                if (key == "ItemName")
                    currentBill.setItemName(value);
                if (key == "ItemManufacturingDate")
                    currentBill.setItemManufacturingDate(value);
                if (key == "ItemPrice")
                    currentBill.setItemPrice(value);
                if (key == "ItemTaxPercent")
                    currentBill.setItemTaxPercent(value);
                if (key == "ItemQuantity")
                    currentBill.setItemQuantity(value);
                if (key == "ItemNumber")
                    currentBill.setItemNumber(value);
                if (key == "ItemCategory")
                    currentBill.setItemCategory(value);
                if (key == "ItemDiscount")
                    currentBill.setItemDiscount(value);
            }
        }
    }
    return (currentBill);
}

void ManagmentSystem::ReadDataAndParsIt()
{
    string LineRead, BillBody;

    this->OpenStream(ios::in | ios::out | ios::app);
    databaseFile.seekg(0, std::ios::beg);
    while (getline(this->databaseFile, LineRead))
    {
        if (LineRead.find(this->db_sperator) != string::npos)
        {
            this->BillInfos.push_back(parseInfo(BillBody));
            BillBody.clear();
        }
        BillBody += LineRead + "\n";
    }
    databaseFile.seekg(0, std::ios::beg);
}

void ManagmentSystem::displayBillReport()
{
    double grandTotal = 0.0;
    cout << setw(5) << ' ' << "Bill Report : " << endl
         << endl
         << endl;
    for (size_t i = 0; i < this->BillInfos.size(); i++)
    {
        double total = this->BillInfos[i].getItemPrice() * this->BillInfos[i].getItemQuantity();
        cout << setw(8) << ' ' << "Name          : " << fixed << setprecision(2) << this->BillInfos[i].getItemName() << endl;
        cout << setw(8) << ' ' << "Manufacturing : " << fixed << setprecision(2) << this->BillInfos[i].getItemManufacturingDate() << endl;
        cout << setw(8) << ' ' << "Price         : $" << fixed << setprecision(2) << this->BillInfos[i].getItemPrice() << endl;
        cout << setw(8) << ' ' << "Tax Percent   : %" << fixed << setprecision(2) << this->BillInfos[i].getItemTaxPercent() << endl;
        cout << setw(8) << ' ' << "Quantity      : " << fixed << setprecision(2) << this->BillInfos[i].getItemQuantity() << endl;
        cout << setw(8) << ' ' << "Number        : " << fixed << setprecision(2) << this->BillInfos[i].getItemNumber() << endl;
        cout << setw(8) << ' ' << "Category      : " << fixed << setprecision(2) << this->BillInfos[i].getItemCategory() << endl;
        cout << setw(8) << ' ' << "Discount      : %" << fixed << setprecision(2) << this->BillInfos[i].getItemDiscount() << endl;
        cout << setw(8) << ' ' << "_________________________________" << endl
             << endl;
        grandTotal += total;
    }
    cout << setw(5) << ' ' << "Total" << setw(5) << "$" << fixed << setprecision(2) << grandTotal << endl
         << endl;
}

void ManagmentSystem::ShowBillReport()
{
    this->ProgrameHeader();
    this->BillInfos.clear();
    this->ReadDataAndParsIt();
    if (this->BillInfos.size())
        this->displayBillReport();
    else
        cout << endl
             << "Your database is empty" << endl;
    cout << "Press any key to return to the main menu." << endl;
    cin.ignore();
}

void ManagmentSystem::StoreData(string ItemName, string ItemManufacturingDate, string ItemPrice, string ItemTaxPercent, string ItemQuantity, string ItemNumber, string ItemCategory, string ItemDiscount)
{
    string res = "ItemName : " + ItemName + "\n" +
                 "ItemManufacturingDate  : " + ItemManufacturingDate + "\n" +
                 "ItemPrice  : " + ItemPrice + "\n" +
                 "ItemTaxPercent  : " + ItemTaxPercent + "\n" +
                 "ItemQuantity  : " + ItemQuantity + "\n" +
                 "ItemNumber  : " + ItemNumber + "\n" +
                 "ItemCategory  : " + ItemCategory + "\n" +
                 "ItemDiscount  : " + ItemDiscount + "\n" +
                 this->db_sperator + "\n";
    this->databaseFile << res;
    this->databaseFile.flush();
}

void ManagmentSystem::ReadData(string &readline, string fieldName, int type)
{
    string Error;
    while (readline.empty())
    {
        cout << Error << "Please Enter " << fieldName << " : ";
        cout.flush();
        getline(cin, readline);
        if (cin.eof())
            throw "The program crashed due to the end of the file (^D) input";
        readline.erase(std::remove(readline.begin(), readline.end(), '\t'), readline.end());
        Error = "(Value can't be Empty) ";
        if (type > 0 && readline.find_first_not_of(".1234567890") != string::npos)
        {
            Error = "(Value should a valid number) ";
            readline.clear();
        }
    }
}

void ManagmentSystem::AddMethod()
{
    this->ProgrameHeader();
    OpenStream(ios::in | ios::out | ios::app);
    string ItemName, ItemManufacturingDate, ItemPrice, ItemTaxPercent, ItemQuantity, ItemNumber, ItemCategory, ItemDiscount;
    this->ReadData(ItemName, "Item Name", 0);
    this->ReadData(ItemManufacturingDate, "Item Manufacturing Date", 0);
    this->ReadData(ItemPrice, "Item Price", 1);
    this->ReadData(ItemTaxPercent, "Item Tax Percent", 1);
    this->ReadData(ItemQuantity, "Item Quantity", 1);
    this->ReadData(ItemNumber, "Item Number", 1);
    this->ReadData(ItemCategory, "Item Category", 0);
    this->ReadData(ItemDiscount, "ItemDiscount ", 1);
    this->StoreData(ItemName, ItemManufacturingDate, ItemPrice, ItemTaxPercent, ItemQuantity, ItemNumber, ItemCategory, ItemDiscount);
}

int ManagmentSystem::ShowBanner(string title)
{
    this->ProgrameHeader();
    this->ReadDataAndParsIt();
    string ReadLine, ItemName, ItemManufacturingDate, ItemPrice, ItemTaxPercent, ItemQuantity, ItemNumber, ItemCategory, ItemDiscount;
    for (size_t i = 0; i < this->BillInfos.size(); i++)
    {
        cout << setw(8) << ' ' << "Id            : " << fixed << setprecision(2) << i << endl;
        cout << setw(8) << ' ' << "Name          : " << fixed << setprecision(2) << this->BillInfos[i].getItemName() << endl;
        cout << setw(8) << ' ' << "_________________________________" << endl
             << endl
             << endl;
        cout << setw(8) << ' ' << title << endl
             << endl
             << endl;
    }

    cout << "Enter Item Id : ";
    cout.flush();
    getline(cin, ReadLine);
    if (ReadLine.empty() || ReadLine.find_first_not_of("0123456789") != string::npos || stoi(ReadLine) < 0 || stoi(ReadLine) >= (int)this->BillInfos.size())
        return (-1);

    return (stoi(ReadLine));
}

void ManagmentSystem::EditMethod()
{
    string ReadLine, ItemName, ItemManufacturingDate, ItemPrice, ItemTaxPercent, ItemQuantity, ItemNumber, ItemCategory, ItemDiscount;
    int key = this->ShowBanner("Edit Item Information's");
    if (key == -1)
    {
        cout << "Error Detected in your input" << endl;
        cout << "Press any key to return to the main menu." << endl;
        cin.ignore();
        return;
    }
    this->ReadData(ItemName, "Item Name", 0);
    this->ReadData(ItemManufacturingDate, "Item Manufacturing Date", 0);
    this->ReadData(ItemPrice, "Item Price", 1);
    this->ReadData(ItemTaxPercent, "Item Tax Percent", 1);
    this->ReadData(ItemQuantity, "Item Quantity", 1);
    this->ReadData(ItemNumber, "Item Number", 1);
    this->ReadData(ItemCategory, "Item Category", 0);
    this->ReadData(ItemDiscount, "ItemDiscount ", 1);

    this->BillInfos[key].setItemName(ItemName);
    this->BillInfos[key].setItemManufacturingDate(ItemManufacturingDate);
    this->BillInfos[key].setItemPrice(ItemPrice);
    this->BillInfos[key].setItemTaxPercent(ItemTaxPercent);
    this->BillInfos[key].setItemQuantity(ItemQuantity);
    this->BillInfos[key].setItemNumber(ItemNumber);
    this->BillInfos[key].setItemCategory(ItemCategory);
    this->BillInfos[key].setItemDiscount(ItemDiscount);
    this->OpenStream(std::ios::out | std::ios::trunc);
    this->OpenStream(ios::in | ios::out | ios::app);

    for (size_t i = 0; i < this->BillInfos.size(); i++)
    {
        this->StoreData(
            this->BillInfos[i].getItemName(), this->BillInfos[i].getItemManufacturingDate(),
            to_string(this->BillInfos[i].getItemPrice()), to_string(this->BillInfos[i].getItemTaxPercent()),
            to_string(this->BillInfos[i].getItemQuantity()), to_string(this->BillInfos[i].getItemNumber()),
            this->BillInfos[i].getItemCategory(), to_string(this->BillInfos[i].getItemDiscount()));
    }
}

void ManagmentSystem::DeleteMethod()
{
    int key = this->ShowBanner("Delete Item Information's");
    if (key == -1)
    {
        cout << "Error Detected in your input" << endl;
        cout << "Press any key to return to the main menu." << endl;
        cin.ignore();
        return;
    }

    this->BillInfos.erase(this->BillInfos.begin() + key);
    this->OpenStream(std::ios::out | std::ios::trunc);
    this->OpenStream(ios::in | ios::out | ios::app);

    for (size_t i = 0; i < this->BillInfos.size(); i++)
    {
        this->StoreData(
            this->BillInfos[i].getItemName(), this->BillInfos[i].getItemManufacturingDate(),
            to_string(this->BillInfos[i].getItemPrice()), to_string(this->BillInfos[i].getItemTaxPercent()),
            to_string(this->BillInfos[i].getItemQuantity()), to_string(this->BillInfos[i].getItemNumber()),
            this->BillInfos[i].getItemCategory(), to_string(this->BillInfos[i].getItemDiscount()));
    }
}

void ManagmentSystem::ShowItemDetails()
{
    int key = this->ShowBanner("Show Item Details Information's");
    if (key == -1)
    {
        cout << "Error Detected in your input" << endl;
        cout << "Press any key to return to the main menu." << endl;
        cin.ignore();
        return;
    }
    this->ProgrameHeader();
    cout << setw(8) << ' ' << "_________________________________" << endl
         << endl;
    cout << setw(8) << ' ' << "Name          : " << fixed << setprecision(2) << this->BillInfos[key].getItemName() << endl;
    cout << setw(8) << ' ' << "Manufacturing : " << fixed << setprecision(2) << this->BillInfos[key].getItemManufacturingDate() << endl;
    cout << setw(8) << ' ' << "Price         : $" << fixed << setprecision(2) << this->BillInfos[key].getItemPrice() << endl;
    cout << setw(8) << ' ' << "Tax Percent   : %" << fixed << setprecision(2) << this->BillInfos[key].getItemTaxPercent() << endl;
    cout << setw(8) << ' ' << "Quantity      : " << fixed << setprecision(2) << this->BillInfos[key].getItemQuantity() << endl;
    cout << setw(8) << ' ' << "Number        : " << fixed << setprecision(2) << this->BillInfos[key].getItemNumber() << endl;
    cout << setw(8) << ' ' << "Category      : " << fixed << setprecision(2) << this->BillInfos[key].getItemCategory() << endl;
    cout << setw(8) << ' ' << "Discount      : %" << fixed << setprecision(2) << this->BillInfos[key].getItemDiscount() << endl;
    cout << setw(8) << ' ' << "_________________________________" << endl
         << endl;
    cout << "Press any key to return to the main menu." << endl;
    cin.ignore();
}

void ManagmentSystem::Process()
{
    string ReadLine;
    this->ProgrameHeader();
    this->BillInfos.clear();
    std::cout << std::setw(15) << std::right << '\0' << 1 << ". Add " << endl;
    std::cout << std::setw(15) << std::right << '\0' << 2 << ". Edit" << endl;
    std::cout << std::setw(15) << std::right << '\0' << 3 << ". Remove" << endl;
    std::cout << std::setw(15) << std::right << '\0' << 4 << ". Back to Main" << endl
              << endl;
    std::cout << std::setw(5) << std::right << '\0' << "_________________________________________" << endl
              << endl;
    std::cout << std::setw(5) << std::right << '\0' << "Enter Command ID : ";
    cout.flush();
    while (ReadLine.empty())
    {
        getline(cin, ReadLine);
        if (ReadLine.find_first_not_of("0123456789") != string::npos || stoi(ReadLine) < 1 || stoi(ReadLine) > 4)
            ReadLine.clear();
    }

    switch (stoi(ReadLine))
    {
    case Process::Add:
        this->AddMethod();
        break;
    case Process::Edit:
        this->EditMethod();
        break;
    case Process::Remove:
        this->DeleteMethod();
        break;
    default:
        break;
    }
}