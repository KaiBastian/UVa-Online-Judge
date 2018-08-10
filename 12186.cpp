#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <vector>
# 12186

struct EmployeeRecord
{
    EmployeeRecord()
        : directReports(), costToActivate(1), properlyEvaluated(false)
    {
    }

    std::vector<unsigned> directReports;
    unsigned costToActivate;
    bool properlyEvaluated;
    // TODO something like 'wont be cheaper than...'
};

std::vector<unsigned> getCheapEmployees(
    std::vector<EmployeeRecord>& employees,
    EmployeeRecord& managerRecord)
{
    const auto& directReports = managerRecord.directReports;
    std::vector<unsigned> directReportsActivationCost;
    directReportsActivationCost.reserve(directReports.size());
    for (auto directReport : directReports)
    {
        auto currentReportsCost = employees[directReport].costToActivate;
        directReportsActivationCost.push_back(currentReportsCost);
    }

    std::sort(
        directReportsActivationCost.begin(), directReportsActivationCost.end());

    return directReportsActivationCost;
}

unsigned calculateCost(
    const std::vector<unsigned>& costs,
    unsigned percentPoints)
{
    unsigned cost = 0;
    unsigned numberOfNeededEmp = static_cast<unsigned>(
        std::ceil((costs.size() * percentPoints) / 100.0));
    for (unsigned i = 0; i < numberOfNeededEmp; ++i)
    {
        cost += costs[i];
    }
    return cost;
}

void evaluateManager(
    std::vector<EmployeeRecord>& employees,
    EmployeeRecord& managerRecord,
    unsigned percentPoints)
{
    const auto listOfCheapEmps = getCheapEmployees(employees, managerRecord);

    managerRecord.costToActivate =
        calculateCost(listOfCheapEmps, percentPoints);

    managerRecord.properlyEvaluated = true;
}

void calculateActivationCost(
    std::vector<EmployeeRecord>& employees,
    unsigned percentPoints)
{
    std::stack<unsigned> employeesToExplore;
    employeesToExplore.push(0);

    while (!employeesToExplore.empty())
    {
        auto currentEmpId = employeesToExplore.top();
        EmployeeRecord& currentEmpRec = employees[currentEmpId];
        if (currentEmpRec.directReports.empty()) // Found a worker.
        {
            currentEmpRec.properlyEvaluated = true;
            employeesToExplore.pop(); // Done with this guy.
            continue;
        }

        const bool areDirectReportsEvaluated =
            employees[currentEmpRec.directReports[0]].properlyEvaluated;

        if (areDirectReportsEvaluated)
        {
            // We have a manager.
            // If all his direct reports were processed already, we can evaluate
            // him.
            evaluateManager(employees, currentEmpRec, percentPoints);
            employeesToExplore.pop(); // Done with this guy.
        }
        else
        {
            // A manager who's employees need processing.
            for (auto directReport : currentEmpRec.directReports)
                employeesToExplore.push(directReport);
            // We don't clear the manager from the stack, cause he is still
            // unevaluated.
        }
    }
}

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    while (true)
    {
        unsigned numberOfEmployees, percentPoints;
        std::cin >> numberOfEmployees >> percentPoints;
        if (numberOfEmployees == 0 && percentPoints == 0)
            return 0;

        std::vector<EmployeeRecord> employees(numberOfEmployees + 1);
        for (unsigned empNumber = 1; empNumber <= numberOfEmployees;
             ++empNumber)
        {
            unsigned hisManager;
            std::cin >> hisManager;
            employees[hisManager].directReports.push_back(empNumber);
        }

        calculateActivationCost(employees, percentPoints);
        std::cout << employees[0].costToActivate << '\n';
    }
}
