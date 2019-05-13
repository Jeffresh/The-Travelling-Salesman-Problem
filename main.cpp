#include <iostream>
#include <regex>
#include "Graph.hpp"

using namespace std;

int main()
{
    std::ifstream myfile("TSPLIB/a280.tsp/a280.tsp");

    regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
    regex word("[[:alpha:]]+(_)*[[:space:]]*(:)*(\\([[:space:]]*[[:alpha:]]*[[:space:]]*\\))*");
    regex more_space("(([[:space:]][[:space:]])[[:space:]]*)\t*");
    string clean_numbers,clean_words,line;
    //Replace with an empty string
    const string format="";
    const string format2=" ";

    if(myfile.is_open())
    {

        while(getline (myfile,line) )
        {
            clean_words=regex_replace(line,word,format,regex_constants::format_default);
            clean_words=regex_replace(clean_words,more_space,format2,regex_constants::format_default);

            cout<<clean_words<<endl;
        }



    }
    else
    {
            std::cout<<"Error opening the file";

    }

}