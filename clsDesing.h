#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <windows.h> 
#include "clsStructures.h"
#include "clsStirngHandling.h"
using namespace std;

class clsDesign {
public:

    static void PrintTruthTable(clsStructures::stRuls rule) {
        int numVars = rule.vars.size();
        int totalRows = 1 << numVars;

        for (char var : rule.vars) {
            cout << var << " ";
        }
        cout << "| F" << endl;

        for (int row = 0; row < totalRows; ++row) {
            vector<int> rowBits(numVars);
            int sum = 0;
           string binary = bitset<8>(row).to_string();
            string relevantBits = binary.substr(8 - numVars); 

            for (int i = 0; i < numVars; ++i) {
                int bit = relevantBits[i] - '0';
                rowBits[i] = bit;
                cout << bit << " ";
                sum += bit;
            }

            bool conditionResult = Evaluate(rule, rowBits, sum);

            int output = (rule.outputMode == clsStructures::_enOutputMode::Ones) ? conditionResult : !conditionResult;

            cout << "| " << output << endl;
        }
    }

    static void RUN_APP() {
        string input = GetInput();
        clsStructures::stRuls rule = clsStirngHandling::Parse(input);
        PrintTruthTable(rule);
    }

private:
    static bool Evaluate(clsStructures::stRuls rule, vector<int>& rowBits, int sum) {
        int valueToCheck = 0;

        switch (rule.condType) {
        case clsStructures::_enConditionType::Sum:
            valueToCheck = sum;
            break;
        case clsStructures::_enConditionType::Odd:
            valueToCheck = sum % 2;
            break;
        case clsStructures::_enConditionType::Even:
            valueToCheck = (sum % 2 == 0) ? 1 : 0;
            break;
        case clsStructures::_enConditionType::Value:
            for (int bit : rowBits) {
                valueToCheck = (valueToCheck << 1) | bit;
            }
            break;
        }

        switch (rule.op) {
        case clsStructures::_enOperator::Equal:
            return valueToCheck == rule.targetValue;
        case clsStructures::_enOperator::NotEqual:
            return valueToCheck != rule.targetValue;
        case clsStructures::_enOperator::Greater:
            return valueToCheck > rule.targetValue;
        case clsStructures::_enOperator::GreaterEqual:
            return valueToCheck >= rule.targetValue;
        case clsStructures::_enOperator::Less:
            return valueToCheck < rule.targetValue;
        case clsStructures::_enOperator::LessEqual:
            return valueToCheck <= rule.targetValue;
        }

        return false;
    }

    static void SetColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    static string GetInput() {
        SetColor(9);
        cout << "\n======================= INPUT FORMAT HELP =======================\n";
        SetColor(15);
        cout << "Use the format: (N) WHEN [1S|0S] [SUM|VALUE|EVEN|ODD] [OP] Number\n\n";

        SetColor(10);
        cout << "Examples:\n";
        SetColor(15);
        cout << " (3) WHEN 1S SUM == 2\n";
        cout << " (A,B,C) WHEN 0S VALUE >= 1\n";
        cout << " (2) WHEN 1S EVEN != 1\n\n";

        SetColor(12);
        cout << "Some WRONG Examples:\n";
        SetColor(15);
        cout << " 3 when 1s value == 3     // Missing ()\n";
        cout << " (3) when value == 3      // Missing 1S or 0S\n";
        cout << " (ABC) when 1s value == 3 // Missing commas\n\n";

        SetColor(10);
        cout << "Enter your logic rule: ";
        SetColor(6);
        string input;
        getline(cin, input);
        return input;
    }
};
