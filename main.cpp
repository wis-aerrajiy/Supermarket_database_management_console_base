#include "ManagmentSystem.hpp"
#include "Bill.Info.hpp"

enum options 
{
    Report = 1, 
    Add_Remove_Edit = 2, 
    Show = 3,
    Exit = 4
};

void ShowHeader(ManagmentSystem *Run)
{
    Run->ProgrameHeader();
    std::cout << std::setw(15) << std::right << '\0' << 1 << ". Bill Report " << endl;
    std::cout << std::setw(15) << std::right << '\0' << 2 << ". Add / Remove /Edit Item" << endl;
    std::cout << std::setw(15) << std::right << '\0' << 3 << ". Show Item Details" << endl;
    std::cout << std::setw(15) << std::right << '\0' << 4 << ". Exit Program" << endl
              << endl;

    std::cout << std::setw(5) << std::right << '\0' << "_________________________________________" << endl
              << endl;
    std::cout << std::setw(5) << std::right << '\0' << "Enter Command ID : ";
    cout.flush();
}

int main()
{
    ManagmentSystem *Run = new ManagmentSystem("database.db");
    string ReadedLine;
    bool SystemRuning = true;
    try
    {
        for (; SystemRuning;)
        {
            ShowHeader(Run);
            getline(cin, ReadedLine);
            if (cin.eof())
                throw runtime_error("The program crashed due to the end of the file (^D) input");
            if (ReadedLine.empty() || ReadedLine.find_first_not_of("0123456789") != string::npos)
                continue;
            switch (stoi(ReadedLine))
            {
                case options::Report :
                    Run->ShowBillReport();
                    break;
                case options::Add_Remove_Edit :
                    Run->Process();
                    break;
                case options::Show :
                    Run->ShowItemDetails();
                    break;
                case options::Exit :
                    SystemRuning = false;
                    break;
            }
            
        }
    }
    catch(const std::exception& e) {
        cout << endl << e.what() << endl;
    }
    delete Run;
    return (0);
}