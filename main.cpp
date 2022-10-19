/*
 * main.cpp created on Wed Oct 12 2022 by King Red Sanchez
 * Copyright (c) 2022
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

ofstream file("process.txt");

// from GeeksforGeeks.com
void printStack(stack<char> s)
{
    // If stack is empty then return
    if (s.empty())
        return;
    char x = s.top();
    // Pop the top element of the stack
    s.pop();
    // Recursively call the function PrintStack
    printStack(s);
    // Print the stack element starting from the bottom
    file << x << " ";
    // Push the same element onto the stack to preserve the order
    s.push(x);
}

void printSolveStack(stack<float> s)
{
    // If stack is empty then return
    if (s.empty())
        return;
    float x = s.top();
    // Pop the top element of the stack
    s.pop();
    // Recursively call the function PrintStack
    printSolveStack(s);
    // Print the stack element starting from the bottom
    file << x << " ";
    // Push the same element onto the stack to preserve the order
    s.push(x);
}

// NOTE: will automatically print translation progress and stack contents
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
        // SEE: If else statements are the easiest way to compare same level tokens
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
            // SEE: all checking of empty stack is redundant, need refactoring so the check is only one
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
        file << "~Curent elem: " << elem << " ~Current postfix: " << postfix << " ~Current Stack: ";
        printStack(stack);
        file << "\n";
        i++;
    }
    while (!stack.empty())
    {
        postfix += stack.top();
        stack.pop();
        file << "~Current postfix: " + postfix + " ~Current stack: ";
        printStack(stack);
        file << "\n";
    }
    return postfix;
}

float evaluate(string postfix)
{
    stack<float> solveStack;
    char elem;
    float a,b, ans;
    for (int i = 0; i < postfix.length(); i++)
    {
        elem = postfix[i];
        switch (elem)
        {
        case '+':
            a = solveStack.top();
            solveStack.pop();
            b = solveStack.top();
            solveStack.pop();
            ans = b+a;
            solveStack.push(ans);
            break;
        case '-':
            a = solveStack.top();
            solveStack.pop();
            b = solveStack.top();
            solveStack.pop();
            ans = b-a;
            solveStack.push(ans);
            break;
        case '*':
            a = solveStack.top();
            solveStack.pop();
            b = solveStack.top();
            solveStack.pop();
            ans = b*a;
            solveStack.push(ans);
            break;
        case '/':
            a = solveStack.top();
            solveStack.pop();
            b = solveStack.top();
            solveStack.pop();
            ans = b/a;
            solveStack.push(ans);
            break;
        default:
            solveStack.push(elem - '0');
            break;
        }
        file << "~Current elem: " << elem << "  ~Current stack: ";
        printSolveStack(solveStack);
        file << "\n";
    }
    ans = solveStack.top();
    return ans;
}

int main()
{
    string infix, postfix;
    float ans;
    cout << "Welocome Infix to Postfix Evaluator";
    cout << "\nSupported operations: +, -, *, /, ()\n";
    cout << "Enter the infix expression: ";
    getline(cin, infix);
    postfix = infixToPostfix(infix);
    cout << "The postfix is: " << postfix << "\n";
    ans = evaluate(postfix);
    cout << "Answer: " << ans;
    file.close();
}