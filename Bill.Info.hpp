# ifndef BILL_INFO_H
# define BILL_INFO_H

# include <iostream>
# include <fstream>
# include <sstream>
# include <iomanip>

using namespace std;

class BillInfo
{
    private:
        string  ItemName;
        string  ItemManufacturingDate;
        double  ItemPrice;
        double  ItemTaxPercent;
        long long    ItemQuantity;
        long long     ItemNumber;
        string  ItemCategory;
        double  ItemDiscount;

    public:
        string const & getItemName()const ;
        string const & getItemManufacturingDate()const ;
        double const & getItemPrice()const ;
        double const & getItemTaxPercent()const ;
        long long const & getItemQuantity()const ;
        long long const & getItemNumber()const ;
        string const & getItemCategory()const ;
        double const & getItemDiscount()const ;

        void    setItemName                 (string Name);
        void    setItemManufacturingDate    (string Data);
        void    setItemPrice                (string Price);
        void    setItemTaxPercent           (string TaxPercent);
        void    setItemQuantity             (string Quantity);
        void    setItemNumber               (string Number);
        void    setItemCategory             (string Category);
        void    setItemDiscount             (string Discount);
};

# endif