#ifndef AIRGEAD_BANKING_AIRGEAD_BANKING_H_
#define AIRGEAD_BANKING_AIRGEAD_BANKING_H_

#include <string>

// Handles user input and investment calculations.
class AirgeadBanking {
public:
    AirgeadBanking();
    void run();

private:
    // Stores the values entered by the user.
    double m_initialInvestment;
    double m_monthlyDeposit;
    double m_annualInterest;
    int m_numberOfYears;

    // Helper functions for input and reports.
    void displayInputScreen() const;
    void collectUserInput();
    void displayReport(bool t_includeMonthlyDeposits) const;
    double getPositiveDouble(const std::string& t_prompt) const;
    int getPositiveInt(const std::string& t_prompt) const;
    bool askToRunAgain() const;
};

#endif
