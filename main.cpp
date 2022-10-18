/*
 * main.cpp created on Wed Oct 12 2022 by King Red Sanchez
 * Copyright (c) 2022
 */

#include <iostream>
#include <string>
#include <stack>
using namespace std;

string infixToPostfix(string infix)
{
    stack<char> stack;
    char elem, prev, top;
    string postfix = "";
    int i = 0;
    int implicit = 0;
    while (i < infix.length())
    {
        elem = infix[i];
        if (elem == '(')
        {
            stack.push(elem);
            if (i != 0)
            {
                prev = infix[i - 1];
                if (prev != '+' && prev != '-' && prev != '*' && prev != '/' && prev != '%')
                {
                    implicit++;
                }
            }
        }
        else if (elem == ')')
        {
            top = stack.top();
            while ((top != '(') && !stack.empty())
            {
                postfix += stack.top();
                stack.pop();
                if (!stack.empty())
                {
                    top = stack.top();
                }
            }
            stack.pop();
            if (implicit != 0)
            {
                stack.push('*');
                implicit--;
            }
        }
        else if (elem == 'v' || elem == '|')
        {
            if (!stack.empty())
            {
                top = stack.top();
                while ((top == 'v' || top == '|') && !stack.empty())
                {
                    postfix += stack.top();
                    stack.pop();
                    if (!stack.empty())
                    {
                        top = stack.top();
                    }
                }
            }

            stack.push(elem);
        }
        else if (elem == '^' || elem == '!')
        {
            if (!stack.empty())
            {
                top = stack.top();
                while ((top == 'v' || top == '|' || top == '^' || top == '!') && !stack.empty())
                {
                    postfix += stack.top();
                    stack.pop();
                    if (!stack.empty())
                    {
                        top = stack.top();
                    }
                }
            }

            stack.push(elem);
        }
        else if (elem == '*' || elem == '/' || elem == '%')
        {
            if (!stack.empty())
            {
                top = stack.top();
                while ((top == 'v' || top == '|' || top == '^' || top == '!' || top == '*' || top == '/' || top == '%') && !stack.empty())
                {
                    postfix += stack.top();
                    stack.pop();
                    if (!stack.empty())
                    {
                        top = stack.top();
                    }
                }
            }

            stack.push(elem);
        }
        else if (elem == '+' || elem == '-')
        {
            if (!stack.empty())
            {
                top = stack.top();
                while ((top == 'v' || top == '|' || top == '^' || top == '!' || top == '*' || top == '/' || top == '%' || top == '+' || top == '-') && !stack.empty())
                {
                    postfix += stack.top();
                    stack.pop();
                    if (!stack.empty())
                    {
                        top = stack.top();
                    }
                }
            }

            stack.push(elem);
        }
        else
        {
            postfix += elem;
        }
        i++;
    }
    while (!stack.empty())
    {
        postfix += stack.top();
        stack.pop();
    }
    return postfix;
}

int main()
{
    string infix, postfix;
    cout << "Welocome Infix to Postfix Evaluator";
    cout << "\nSupported operations: +, -, *, /, %, ^, !, |, v\n";
    cout << "Enter the infix expression: ";
    getline(cin, infix);
    postfix = infixToPostfix(infix);
    cout << "The postfix is: " + postfix;
}