#include <iostream>
#include <iomanip>  // For formatting output

void printBillReport() {
    // Set precision for displaying currency
    std::cout << std::fixed << std::setprecision(2);

    // Header
    std::cout << "----------------------------------------\n";
    std::cout << "          Supermarket Bill Report\n";
    std::cout << "----------------------------------------\n";

    // Item details
    std::cout << std::setw(20) << "Item" << std::setw(10) << "Quantity" << std::setw(10) << "Price\n";
    std::cout << "----------------------------------------\n";
    std::cout << std::setw(20) << "Milk" << std::setw(10) << "2" << std::setw(10) << "$2.50\n";
    std::cout << std::setw(20) << "Bread" << std::setw(10) << "1" << std::setw(10) << "$1.50\n";
    std::cout << std::setw(20) << "Eggs" << std::setw(10) << "1 dozen" << std::setw(10) << "$3.75\n";
    std::cout << std::setw(20) << "Cereal" << std::setw(10) << "1 box" << std::setw(10) << "$4.99\n";
    std::cout << std::setw(20) << "Vegetables" << std::setw(10) << "0.5 kg" << std::setw(10) << "$2.00\n";
    std::cout << "----------------------------------------\n";

    // Total calculations
    double subtotal = 14.74;
    double taxRate = 0.08;
    double tax = subtotal * taxRate;
    double totalAmount = subtotal + tax;

    // Totals section
    std::cout << std::setw(10) << "Subtotal:"      << "$" << subtotal << '\n';
    std::cout << std::setw(10) << "Tax (8%):"      << "$" << tax << '\n';
    std::cout << std::setw(90) << "Total Amount:"  << "$" << totalAmount << '\n';

    // Payment method
    std::cout << "\nPayment Method:" << std::setw(23) << "Credit Card\n";

    // Footer
    std::cout << "----------------------------------------\n";
}

int main() {
    printBillReport();
    return 0;
}
