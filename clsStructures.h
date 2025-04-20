#pragma once
#include <iostream> 
using namespace std;
#include <vector>

class clsStructures
{
	public : 
	
	enum  _enConditionType {
		Sum,Odd,Even,Value 
	};
	enum _enOperator  {
		Equal,         // ==
		NotEqual,      // !=
		Greater,       // >
		GreaterEqual,  // >=
		Less,          // <
		LessEqual      // <=
	};
	enum _enOutputMode {
		Zeros = 0,
		Ones = 1
	};

	struct stRuls {
		string equationText;
		vector<char> vars;
		_enConditionType condType;
		_enOperator op;
		int targetValue;
		_enOutputMode outputMode = Ones; // defult value 1s the f  output  
	};

};

