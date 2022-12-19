
#include "Scanner.h"
#include "Stack.h"  // GENERIC STACK

#include <iostream>
using namespace std;



int main () {
    Scanner S(cin);
    Token t;

    Stack<Token> numstack, opstack;  // 2x Stacks of type Token
    

    t = S.getnext();

    while (t.tt != eof || !opstack.isEmpty())
    {
        if (t.tt == integer) 
        { 
            numstack.push(t);
            t = S.getnext();
        }
        else 
        { 
            if (t.tt == lptok) 
            { 
                opstack.push(t);
                t = S.getnext();
            }
            else 
            {
                if (t.tt == rptok) 
                {
                    if (opstack.peek().tt == lptok) 
                    {
                        opstack.pop();
                        t = S.getnext();
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
                    if (t.tt == pltok || t.tt == mitok || t.tt == eof) 
                    {
                        if (!opstack.isEmpty() && (opstack.peek().tt == pltok || opstack.peek().tt == mitok || opstack.peek().tt == asttok || opstack.peek().tt == slashtok)) 
                        {
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
                            t = S.getnext();
                        }
                    }
                    else 
                    {
                        if (t.tt == asttok || t.tt == slashtok) 
                        {
                            if (!opstack.isEmpty() && (opstack.peek().tt == asttok || opstack.peek().tt == slashtok)) 
                            {
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
                                t = S.getnext();
                            }
                        }
                    }
                }
            }
        }
    }
    // Pretty printer coding demo.  Please remove before coding
    /*while (t.tt != eof) {
        if (t.tt == integer || t.tt == lptok || t.tt == rptok) {
            cout << t;
        } else if (t.tt == pltok || t.tt == mitok || 
                   t.tt == asttok || t.tt == slashtok) {
            cout << ' ' << t << ' ';
        }

        t = S.getnext();
    }*/

    cout << numstack.pop().val << endl;
    // End pretty printer coding demo.

    return 0;
}

