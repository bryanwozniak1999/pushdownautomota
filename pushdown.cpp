#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

//declare function checking acceptable string
bool acceptableString (string Istring);

//declare the function that will apply transition rules to the function  
void states(char &state, string &rule, string &rUse, stack <char> &UIstacks, stack <char> &cStack, int &step);

//function for formatting the information
void printingRows(string state, string rule, string rUse, stack <char> &UIstacks, stack <char> cStacks, int step);

//declaring stacks for check stacks and unread input stack
stack <char> cStacks;
stack <char> UIstacks;

//pushing unread input/input to stack
void UIToStack(string str, stack <char> &inputStack);

//function to print the unread input stack
void printUIstack(stack <char> & inputStack);

//function to print the check stack
void printCstack(stack <char> & cStack);

//function to print the header for the 
void headerFormat();

int main(){
    string input; //user input 
    cout << "Enter an input that follows the language L(G) = {a^n b^n | n >= 0} (with '$' at end): " << endl;
    cin >> input;
    
    //checking if the user inputted string is acceptable in terms of format
    if(acceptableString(input) == true)
    {
        //push the input into the unread input stack
        UIToStack(input, UIstacks);
        
        int step = 0; //step
        char state = 'p'; //state
        string rUse = " "; //R used
        string rule = "-"; // transition rule 
        
        //call function to set up the header/ columns
        headerFormat();
        //call function to apply transition rules
        states(state, rule, rUse,UIstacks,cStacks,step);
        
        cout  << "The string is accepted by the language" <<endl;
    
    }
    else
    {
        //invalid formatted string
        cout << "The langauge does not recognize the string" << endl;
    }
    
    return 0;
    
}


//function to push input into the unread input stack
void UIToStack(string str, stack <char> &inputStack)
{
    //starting from the back of the string so that the first element of the string ends up on top
    int leng = str.length();
    for(int i = leng-1; i >= 0; i--)
    {
    inputStack.push(str.at(i));
    }
}

//function to print the user input stack is not empty
void printUIstack(stack <char> & inputStack)
{
    stack<char> temp;
    temp = inputStack;
    while (!(temp.empty()))
    {
    char top = temp.top();
    temp.pop();
    cout << top;
    }
}

//function to print the check stack while stack is not empty
void printCstack(stack <char> & cStack)
{
    stack<char> temp;
    temp = cStack;
    while (!(temp.empty()))
    {
    char top = temp.top();
    temp.pop();
    cout << top;
    }
}

//function that applies the transition rules and DPDA to the stacks
void states(char &state, string &rule, string &rUse, stack <char> &UIstacks, stack <char> &cStacks, int &step)
{
    //string realState is just the string version of state and how it actually should be outputted while char state is just made that way to enable switch cases and easier access
    string realState;
    step = 0;
    while(!(UIstacks.empty()))
    {
       //string unread = UIstacks;
        switch (state)
        {
            case 'p': //if state is equal to p
                //if else checks if it is step zero or if it is step 1 and will apply rule 1
                if(step == 0)
                {
                    //prints first row (row 0) which is basically the same for all accepted languages with the exception of the unread input stack
                    cout << left << setw(16);
                    cout << step;
    
                    cout << left << setw(15);
                    cout << state;
    
                    cout << left << setw(0);
                    cout << " ";
                    printUIstack(UIstacks);
    
                    cout << left << setw(53);
                    cout << " ";
                    cout << "--";
    
                    cout << left << setw(10);
                    cout <<" ";    
                    cout << endl <<endl;
                    rule = "1";
                    rUse = "";
                    
                    step++;
                }
                   else
                   {
                state = 'q';
                realState = "q";
                cStacks.push('S');
                printingRows(realState, rule, rUse, UIstacks, cStacks, step);
                step++;
                   }
                
 
                break;
            
            
            case 'q':  //checks if that state is q and then uses if else statements to decide what is on top of the unread input and thus what rule should be used. thus applying the rule and formatting/printing
            
                //Rule 2
                if (UIstacks.top() == 'a')
                 {
                     state = 'a';
                     realState ="qa";
                     
                     rule = "2";
                     rUse = "";
                     UIstacks.pop();
                     printingRows(realState, rule, rUse, UIstacks, cStacks, step);
                     step++;

                 }
        
                //Rule 4
                else if (UIstacks.top() == 'b')
                 {
                     state = 'b';
                     realState = "qb";
                     rule = "4";
                     rUse = "";
                     UIstacks.pop();
                     printingRows(realState, rule, rUse, UIstacks, cStacks, step);
                     step++;
                
                 }
        
            
                //Rule 6
                else if (UIstacks.top() == '$')
                 { 
                     state = '$';
                     realState = "q$";
                    rule = "6";
                     rUse = "";
                     if (!(UIstacks.empty()))
                     {
                     UIstacks.pop();
                     }
                     printingRows(realState, rule, rUse, UIstacks, cStacks, step);
                     step++;
                 }
                 break;
            
                 
            case 'a': //qa but labeled as a for switch statement
            
                 //Rule 7
                 if(cStacks.top() == 'S')
                 {
                     state = 'a';
                     realState = "qa";
                     rule = "7";
                     rUse = "S -> aSb";
                     cStacks.pop();
                     cStacks.push('b');
                     cStacks.push('S');
                     cStacks.push('a');
                     printingRows(realState, rule, rUse, UIstacks, cStacks, step);
                     step++;
                 }
                  
                  //rule 3
                 else
                 {
                     state = 'q';
                     realState = "q";
                     rule = "3";
                     rUse = "";
                     cStacks.pop();
                     printingRows(realState, rule, rUse, UIstacks, cStacks, step);
                     step++;
                 }
                 
                 break;
            
        
            case 'b': //qb labeled as b for the switch string realstate shows actual value that will be printed
            
             //Rule 8
                 if(cStacks.top() == 'S')
                 {
                     state = 'b';
                     realState = "qb";
                     rule = "8";
                     rUse = "S -> e";
                     cStacks.pop();
                     printingRows(realState, rule, rUse, UIstacks, cStacks, step);
                     step++;
            
                 }
                  
                  //rule 5
                 else
                 {
                    state = 'q';
                     realState = "q";
                     rule = "5";
                     rUse = "";
                     cStacks.pop();
                     printingRows(realState, rule, rUse, UIstacks, cStacks, step);
                     step++;
                 }
                 
                break;

           }
    }
}
    
//function for printing the titles of each column using setw
void headerFormat()
{
    cout << left << setw(15);
    cout << "Step" << " ";
    
    cout << left << setw(15);
    cout << "State" << " ";
    
    cout << left << setw(25);
    cout << "Unread Input" << " ";
    
    cout << left << setw(29);
    cout << "Stack" << " ";
    
    cout << left << setw(19);
    cout << "Rule" << " ";
    
    cout << left << setw(15);
    cout << "R Used" << " ";
    cout << endl;
    
    
}

//function for printing each row (state, rule used, r used, unread input stack, check stack, and step and formatting it)
void printingRows(string state, string rule, string rUse, stack <char> &UIstacks, stack <char> cStacks, int step)
{
    cout << left << setw(16);
    cout << step;
    
    cout << left << setw(15);
    cout << state;
    
    cout << left <<setfill(' ')<< setw(0);
    cout << " ";
    printUIstack(UIstacks);
    
    cout << left << setfill(' ')<< setw(23);
    cout << "\t";
    printCstack(cStacks);
    
    cout << left << setfill(' ') <<setw(25);
    cout << " ";
    cout << "\t";
    cout << rule;
    
    cout << left << setfill(' ') <<setw(17);
    cout << "\t";
    cout << rUse;
    
    cout << endl << endl;
}



//function that checks if the string is accepted by the language
bool acceptableString (string Istring)
{
    // bools for if there is a $ at the end, if a starts the input, and if number of a and b is equal
    bool dollarTrue;
    bool aFTrue;
    bool numAB;
    bool anbn = true;

    int lengthOS = Istring.length();
    int aNumber = count (Istring.begin(), Istring.end(),'a');
    int bNumber = count(Istring.begin(), Istring.end(), 'b');

    //check for $ at end of string
     if (Istring.at(lengthOS-1) =='$')
    {
        dollarTrue = true;
    }
    else
    {
        dollarTrue = false;
    }

    //make sure number of a's and b's are the same
    if(aNumber != bNumber)
    {
     anbn = false;
    }

    //cut $ off of end of string for easier processing
    string st = Istring.substr(0, Istring.size() - 1);

    //make sure second half of string is all b's
    for (int j = aNumber; j < st.length(); j++)
    {
     if (st[j] != 'b')
     {
      anbn = false;
     }
     }

    //final check
    if(dollarTrue == true && anbn == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
