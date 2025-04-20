#pragma once
#include <vector> 
#include <iostream> 
#include <string>
#include <algorithm>
#include "clsStructures.h"

using namespace std;

class clsStirngHandling
{
private:
     
   //convetr string to enum values  
    static clsStructures::_enOperator clsStringToOp(string op) {
        if (op == "==") return clsStructures::_enOperator::Equal;
        if (op == "!=") return clsStructures::_enOperator::NotEqual;
        if (op == ">")  return clsStructures::_enOperator::Greater;
        if (op == ">=") return clsStructures::_enOperator::GreaterEqual;
        if (op == "<")  return clsStructures::_enOperator::Less;
        if (op == "<=") return clsStructures::_enOperator::LessEqual;
          // the defult value 
        return clsStructures::_enOperator::Equal;
    }
public:
   
    static clsStructures::stRuls Parse(string input) {
        clsStructures::stRuls rule;

     
        input.erase(remove(input.begin(), input.end(), ' '), input.end());

        transform(input.begin(), input.end(), input.begin(), ::toupper);

        rule.equationText = input;

        int start = input.find('(');
        int end = input.find(')');
        string varText = input.substr(start + 1, end - start - 1);
        /////////////////////
      //   input = input.substr(input.find('=') + 1);
        ////////////
        if (isdigit(varText[0])) {
            int count = stoi(varText);
            count = (count < 1) ? 1 : (count > 10) ? 10 : count;
            string letters = "ABCDEFGHIJ";
            for (int i = 0; i < count; i++) {
                rule.vars.push_back(letters[i]);
            }
        }
        else {
            for (char c : varText) {
                rule.vars.push_back(c);
            }
        }
    ///////////////////////////////////////////////////////////////****************************
   string conditionPart = input.substr( input.find("WHEN")+ 4);
        if (conditionPart.find("0S") == 0) {
            rule.outputMode = clsStructures::_enOutputMode::Zeros;
            conditionPart = conditionPart.substr(2);
        }
        else{
            rule.outputMode = clsStructures::_enOutputMode::Ones;
            conditionPart = conditionPart.substr(2);
        }
        ////-----------------------------

        if (conditionPart.find("SUM") == 0) {
            rule.condType = clsStructures::_enConditionType::Sum;
            conditionPart = conditionPart.substr(3);
        }
        else if (conditionPart.find("ODD") == 0) {
            rule.condType = clsStructures::_enConditionType::Odd;
            conditionPart = conditionPart.substr(3);
        }
        else if (conditionPart.find("EVEN") == 0) {
            rule.condType = clsStructures::_enConditionType::Even;
            conditionPart = conditionPart.substr(4);
        }
        else if (conditionPart.find("VALUE") == 0) {
            rule.condType = clsStructures::_enConditionType::Value;
            conditionPart = conditionPart.substr(5);
        }

        // --------------------------------- Find operator
        vector<string> ops = { "==", "!=", ">=", "<=", ">", "<" };
        for (string op : ops) {
            if (conditionPart.find(op) == 0) {
                rule.op = clsStringToOp(op);
                conditionPart = conditionPart.substr(op.length());
                break;
            }
        }

            rule.targetValue = stoi(conditionPart);

        return rule;
    }


};
