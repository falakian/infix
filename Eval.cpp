
#include "Scanner.h"
#include "Stack.h"  // GENERIC STACK

#include <iostream>
using namespace std;



int main () {
    Scanner S(cin);
    Token t;

    Stack<Token> numstack, opstack;  // 2x Stacks of type Token
    

    t = S.getnext(); // Read the first character

    while (t.tt != eof || !opstack.isEmpty()) // The loop continues until the end or until the operator stack is empty
        // After reaching the end of the line, it pops all the operators in the stack so that the loop is no longer executed
    {
        if (t.tt == integer) //If the character was a number
        { 
            numstack.push(t);  // Add to stack of numbers
            t = S.getnext();   // Read the next character
        }
        else 
        { 
            if (t.tt == lptok) // If the parentheses were open, add them to the operator stack
            { 
                opstack.push(t);
                t = S.getnext(); // Read the next character
            }
            else 
            {
                if (t.tt == rptok) // If we reach the closed parenthesis
                                   // we pop from the stack until we reach the open parenthesis
                {
                    if (opstack.peek().tt == lptok) 
                    {
                        opstack.pop();
                        t = S.getnext(); // Read the next character
                    }
                    else 
                    {
                        int a2 = numstack.pop().val;
                        int a1 = numstack.pop().val;
                        int result=0;
                        Token ope = opstack.pop();
                        if (ope.tt == pltok) { result = a1 + a2; }
                        else if (ope.tt == mitok) { result = a1 - a2; }
                        else if (ope.tt == asttok) { result = a1 * a2; }
                        else if (ope.tt == slashtok) { result = a1 / a2; }
                        else { cout << "err" << endl; }
                        ope.tt = integer;
                        ope.val = result;
                        ope.text = to_string(result);
                        numstack.push(ope);
                    }
                }
                else 
                {
                    if (t.tt == pltok || t.tt == mitok || t.tt == eof)  //If subtraction or addition or we reach the end of the line
                    {
                        if (!opstack.isEmpty() && (opstack.peek().tt == pltok || opstack.peek().tt == mitok || opstack.peek().tt == asttok || opstack.peek().tt == slashtok)) 
                        {
                            /*Because the priority of addition and subtraction is lower than multiplication
                            and division and equal to themselves, if the operator stack is not empty,
                            we will pop it until it is empty or reach the open parenthesis.*/
                            int a2 = numstack.pop().val;
                            int a1 = numstack.pop().val;
                            int result = 0;
                            Token ope = opstack.pop();
                            if (ope.tt == pltok) { result = a1 + a2; }
                            else if (ope.tt == mitok) { result = a1 - a2; }
                            else if (ope.tt == asttok) { result = a1 * a2; }
                            else if (ope.tt == slashtok) { result = a1 / a2; }
                            else { cout << "err" << endl; }
                            ope.tt = integer;
                            ope.val = result;
                            ope.text = to_string(result);
                            numstack.push(ope);
                        }
                        else 
                        {
                            opstack.push(t);
                            t = S.getnext(); // Read the next character
                        }
                    }
                    else 
                    {
                        if (t.tt == asttok || t.tt == slashtok)  // If the operator was multiplication or division
                        {
                            if (!opstack.isEmpty() && (opstack.peek().tt == asttok || opstack.peek().tt == slashtok)) 
                            {
                                /*If the multiplication or division operator is in the stack, 
                                we will pop it until we reach the operator 
                                whose priority is higher than that of multiplication and division.*/
                                int a2 = numstack.pop().val;
                                int a1 = numstack.pop().val;
                                int result = 0;
                                Token ope = opstack.pop();
                                if (ope.tt == pltok) { result = a1 + a2; }
                                else if (ope.tt == mitok) { result = a1 - a2; }
                                else if (ope.tt == asttok) { result = a1 * a2; }
                                else if (ope.tt == slashtok) { result = a1 / a2; }
                                else { cout << "err" << endl; }
                                ope.tt = integer;
                                ope.val = result;
                                ope.text = to_string(result);
                                numstack.push(ope);
                            }
                            else 
                            {
                                opstack.push(t);
                                t = S.getnext(); // Read the next character
                            }
                        }
                    }
                }
            }
        }
    }
    // After the loop is finished, we pop from the stack of numbers 
    //to get the final answer and then print it
    cout << numstack.pop().val << endl;
    // End pretty printer coding demo.

    return 0;
}

