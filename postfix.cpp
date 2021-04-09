#include<bits/stdc++.h>
using namespace std;

int InfixToPostfix(string infix, int len){



///Find postfix
    stack st;
    char postfix[len];
    int counter=0;
    for(int i=0;i<=len;i++)
    {
        if(infix[i]=='(')
           {
               st.push(infix[i]);
           }
         if(infix[i]==')')
         {
               while(st.top()!='(')
                  {
                    postfix[counter++]=infix[i];
                    //counter++;
                    st.pop();
                  }
            st.pop();
         }

          if(infix[i]=='+' || infix[i]=='-' || infix[i]=='/' || infix[i]=='*')
            {
                while(getPrecedence(st.top())>=getPrecedence(infix[i]) && st.size()!=0 && st.top()!='(')
                        postfix[counter++]=infix[i];
                        //counter++;
                        st.pop();
            }
        st.push(infix[i]);

        if(infix[i]!='(' || infix[i]!=')' || infix[i]!='+' || infix[i]!='-' || infix[i]!='/' || infix[i]!='*')
            {
                postfix[counter++]=infix[i];
            }
            //counter++;

        while(st.size()>0)
        {
            postfix[counter++]=st.top();
            st.pop();
        }
}
cout<<postfix[counter];
}


int main()
{
    stack st;
    int len=19;
    string infix="(2-4*3-9)+(4-9-2*6)";
    InfixToPostfix(infix,19);

  //  cout<<"Enter Infix expression : "; //enter the expression
    //cin>>infix;
    //postfix = InfixToPostfix(infix);
    return 0;
}
