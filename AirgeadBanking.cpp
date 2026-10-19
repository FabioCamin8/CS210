#include "AirgeadBanking.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace {
constexpr int MONTHS_PER_YEAR = 12;
constexpr double PERCENT_CONVERSION = 100.0;
}

AirgeadBanking::AirgeadBanking()
    : m_initialInvestment(0.0),
      m_monthlyDeposit(0.0),
      m_annualInterest(0.0),
      m_numberOfYears(0) {
}

void AirgeadBanking::run() {
    // Keep running until the user chooses to stop.
    bool runAgain = true;

    while (runAgain) {
        displayInputScreen();
        collectUserInput();

        std::cout << "\nPress Enter to continue...";
        std::string pauseInput;
        std::getline(std::cin, pauseInput);

        displayReport(false);
        displayReport(true);

        runAgain = askToRunAgain();
    }

    std::cout << "\nThank you for using the Airgead Banking Investment Calculator.\n";
}

void AirgeadBanking::displayInputScreen() const {
    std::cout << "\n**************************************\n";
    std::cout << "************** Data Input ************\n";
}

void AirgeadBanking::collectUserInput() {
    // Read the investment values from the user.
    m_initialInvestment = getPositiveDouble("Initial Investment Amount: $");
    m_monthlyDeposit = getPositiveDouble("Monthly Deposit: $");
    m_annualInterest = getPositiveDouble("Annual Interest: %");
    m_numberOfYears = getPositiveInt("Number of Years: ");
}

void AirgeadBanking::displayReport(bool t_includeMonthlyDeposits) const {
    double balance = m_initialInvestment;
    const double monthlyInterestRate =
        (m_annualInterest / PERCENT_CONVERSION) / MONTHS_PER_YEAR;

    std::cout << "\n";
    if (t_includeMonthlyDeposits) {
        std::cout << " Balance and Interest With Additional Monthly Deposits\n";
    }
    else {
        std::cout << " Balance and Interest Without Additional Monthly Deposits\n";
    }

    std::cout << "==================================================================\n";
    std::cout << std::left << std::setw(10) << "Year"
              << std::right << std::setw(24) << "Year End Balance"
              << std::setw(30) << "Year End Earned Interest" << '\n';
    std::cout << "------------------------------------------------------------------\n";

    // Without deposits, add annual interest once at the end of each year.
    // With deposits, calculate interest monthly on the balance plus the deposit.
    for (int year = 1; year <= m_numberOfYears; ++year) {
        double yearlyInterest = 0.0;

        if (t_includeMonthlyDeposits) {
            for (int month = 1; month <= MONTHS_PER_YEAR; ++month) {
                const double interest =
                    (balance + m_monthlyDeposit) * monthlyInterestRate;

                balance += m_monthlyDeposit + interest;
                yearlyInterest += interest;
            }
        }
        else {
            yearlyInterest = balance * (m_annualInterest / PERCENT_CONVERSION);
            balance += yearlyInterest;
        }

        std::ostringstream balanceText;
        balanceText << '$' << std::fixed << std::setprecision(2) << balance;

        std::ostringstream interestText;
        interestText << '$' << std::fixed << std::setprecision(2) << yearlyInterest;

        std::cout << std::left << std::setw(10) << year
                  << std::right << std::setw(24) << balanceText.str()
                  << std::setw(30) << interestText.str() << '\n';
    }
}

double AirgeadBanking::getPositiveDouble(const std::string& t_prompt) const {
    // Repeat until a valid positive number is entered.
    while (true) {
        std::cout << t_prompt;

        std::string input;
        std::getline(std::cin, input);
        std::stringstream inputStream(input);

        double value = 0.0;
        char extraCharacter = '\0';

        if ((inputStream >> value) && value > 0.0 && !(inputStream >> extraCharacter)) {
            return value;
        }

        std::cout << "Invalid input. Please enter a positive number.\n";
    }
}

int AirgeadBanking::getPositiveInt(const std::string& t_prompt) const {
    while (true) {
        std::cout << t_prompt;

        std::string input;
        std::getline(std::cin, input);
        std::stringstream inputStream(input);

        int value = 0;
        char extraCharacter = '\0';

        if ((inputStream >> value) && value > 0 && !(inputStream >> extraCharacter)) {
            return value;
        }

        std::cout << "Invalid input. Please enter a positive whole number.\n";
    }
}

bool AirgeadBanking::askToRunAgain() const {
    while (true) {
        std::cout << "\nWould you like to test another investment scenario? (Y/N): ";

        std::string input;
        std::getline(std::cin, input);

        if (input == "Y" || input == "y") {
            return true;
        }
        if (input == "N" || input == "n") {
            return false;
        }

        std::cout << "Invalid input. Please enter Y or N.\n";
    }
}
