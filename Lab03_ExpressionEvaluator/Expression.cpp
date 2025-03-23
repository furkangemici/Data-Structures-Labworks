#include <string>
#include <iostream>
#include <stack>
#include <sstream>
#include <unordered_map>
using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
int getPrecedence(char op) {
    unordered_map<char, int> precedence;
    precedence['+'] = precedence['-'] = 1;  // D���k �ncelik
    precedence['*'] = precedence['/'] = 2;  // Y�ksek �ncelik

    return precedence[op];
}

string Infix2Postfix(string& s) {
    // Fill this in
    stack<char> operatorStack;  // Operat�rler i�in y���n
    string result;              // Postfix sonucu

    for (char c : s) {
        if (isspace(c)) continue;  // Bo�luklar� atla
        else if (isdigit(c)) result += c;  // Say�lar� sonuca ekle
        else if (c == '(') operatorStack.push(c);  // '(' y���na ekle
        else if (c == ')') {  // '(' g�r�nene kadar i�le
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                result += ' ';
                result += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();  // '(' ��kart
        }
        else {  // Operat�rleri i�le
            result += ' ';
            while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(c)) {
                result += operatorStack.top();
                operatorStack.pop();
                result += ' ';
            }
            operatorStack.push(c);
        }
    }

    // Kalan operat�rleri ��kart
    while (!operatorStack.empty()) {
        result += ' ';
        result += operatorStack.top();
        operatorStack.pop();
    }

    return result;  // Postfix ifadeyi d�nd�r
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
/// 
bool IsOperator(char C) {
    return C == '+' || C == '-' || C == '*' || C == '/';
}

int EvaluatePostfixExpression(string& s) {
    stack<int> operandStack;  // Operat�rler i�in y���n

    stringstream ss(s);  // Ayr��t�rma i�in stringstream kullan
    string token;

    while (ss >> token) {
        // Say�lar� y���na ekle
        if (isdigit(token[0]) || (token.length() > 1 && isdigit(token[1]))) {
            operandStack.push(stoi(token));
        }
        // Operat�rleri i�le
        else if (IsOperator(token[0])) {
            int operand2 = operandStack.top(); operandStack.pop();
            int operand1 = operandStack.top(); operandStack.pop();

            switch (token[0]) {
            case '+': operandStack.push(operand1 + operand2); break;
            case '-': operandStack.push(operand1 - operand2); break;
            case '*': operandStack.push(operand1 * operand2); break;
            case '/': operandStack.push(operand1 / operand2); break;
            }
        }
    }

    return operandStack.top();  // Son sonucu d�nd�r
} // end-EvaluatePostfixExpression
