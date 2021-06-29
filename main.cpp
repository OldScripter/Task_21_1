#include <iostream>
#include <fstream>
#include <string>

const char* FILE_PATH = "..\\payments.txt";
const int MIN_YEAR = 1987;
const int MAX_YEAR = 2022;

struct Payment
{
    std::string name;
    std::string surname;
    int value = 0;
    std::string date;

    void print() const
    {
        std::cout << name << " " << surname << " " << value << " " << date << "\n";
    }
};

/*
 * Returns true if format is OK.
 * Corrects the dateInput string in order to make it standard.
*/
bool processTheDateInput(std::string& dateInput)
{
    if (dateInput.length() < 10)
    {
        std::cerr << "Date length error\n";
        return false;
    }

    std::string dayStr = dateInput.substr(0, 2);
    std::string monthStr = dateInput.substr(3, 2);
    std::string yearStr = dateInput.substr(6, 4);

    try
    {
        int day = std::stoi(dayStr);
        int month = std::stoi(monthStr);
        int year = std::stoi(yearStr);

        if (day > 0 && day < 32 &&
            month > 0 && month < 13 &&
            year > MIN_YEAR && year < MAX_YEAR)
        {
            dayStr = (day < 10 ? "0" + std::to_string(day) : std::to_string(day)) + ".";
            monthStr = (month < 10 ? "0" + std::to_string(month) : std::to_string(month)) + ".";
            yearStr = std::to_string(year);
            dateInput = dayStr + monthStr + yearStr;
            return true;
        }
        else
        {
            std::cerr << "Date values error\n";
            return false;
        }
    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Date invalid arguments error\n";
        return false;
    }
}

/*
 * Writes new payment to the end of file.
 */
void addPayment()
{
    std::cout << "Please enter the payment data.\n";
    std::cout << "Format [name] [surname] [payment] [DD.MM.YYYY].\n";
    auto payment = new Payment();
    std::cin >> payment->name >> payment->surname >> payment->value >> payment->date;
    bool dateFormatIsOk = processTheDateInput(payment->date);

    if (dateFormatIsOk)
    {
        std::ofstream outStream (FILE_PATH, std::ios::app);
        if (outStream.is_open())
        {
            outStream
            << payment->name << " "
            << payment->surname << " "
            << payment->value << " "
            << payment->date << '\n';
            outStream.close();

            std::cout << "File is saved.\n";
        }
        else
            std::cout << "Error while opening the file.\n";
    }
    payment = nullptr;
    delete(payment);
}

/*
 * Reads and print payments from file.
 */
void readPayments()
{
    std::ifstream inputStream(FILE_PATH);
    if (inputStream.is_open())
    {
        while (!inputStream.eof())
        {
            auto p = new Payment();
            inputStream >> p->name >> p->surname >> p->value >> p->date;
            //Check if name and value are set to avoid blank strings reading:
            if (!p->name.empty() && p->value != 0) p->print();
            p = nullptr;
            delete(p);
        }
        inputStream.close();
    }
}

int main() {
    do
    {
        std::cin.clear();
        std::string command;
        std::cout << "\nPlease enter the command.\n";
        std::cout << "\tread \t- to read payments;\n";
        std::cout << "\tadd \t- to add payments;\n";
        std::cout << "\texit \t- to exit the program;\n";

        std::cin >> command;

        if (command == "read")
        {
            std::cout << "\t---Reading payments---\n";
            readPayments();
            std::cout << "\t---End of payments list---\n";
        }
        else if (command == "add")
        {
            std::cout << "\t---Adding the payment---\n";
            addPayment();
            std::cout << "\t---Payment is added---\n";
        }
        else if (command == "exit")
        {
            std::cout << "\t---Exiting the program---\n";
            break;
        }
        else
        {
            std::cerr << "Wrong command. Try again.\n";
        }
    } while (true);

    std::cout << "\t---Program is finished---\n";

    return 0;
}
