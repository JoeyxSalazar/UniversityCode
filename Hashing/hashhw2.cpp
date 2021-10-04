//Hashhw.cpp (main cpp file)


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "hash.h"
//Each line is 114 characters in length
//-------index 113 is last pos
// population ends at 66, which is actualy index 65 (use 66 for blank space)
using namespace std;

string getdist(string s) //index 101 is after long
{
    string str;
    int n;
    for(int i= 106; i < 114; i ++) //index 66 is blank space after population
    {
        if(s[i] != ' ') //Finds a number
        {
            n = i; //position of first found number
            break;
        }
    }
    for(n; n<114; n++)
    {
        if(s[n] != ' ')
        {
            str = str + s[n];
        }
        else
            break;
    }
    return str;
}

string getroad(string s) //index 101 is after long
{
    string str;
    int n;
    for(int i= 101; i < 106; i ++) //index 101 
    {
        if(s[i] != ' ') //Finds a number
        {
            n = i; //position of first found number
            break;
        }
    }
    for(n; n<106; n++)
    {
        if(s[n] != ' ')
        {
            str = str + s[n];
        }
        else
            break;
    }
    return str;
}

string getlon(string s) //index 90 is blank
{
    string str;
    int n;
    for(int i= 90; i < 114; i ++) 
    {
        if(s[i] != ' ') //Finds a number
        {
            n = i; //position of first found number
            break;
        }
    }
    for(n; n<114; n++)
    {
        if(s[n] != ' ')
        {
            str = str + s[n];
        }
        else
            break;
    }

    if(str.length() > 10)
    {
        string mod;
        for(int i=0; i<10; i++)
        {
            mod = mod + str[i];
        }
        str = mod;
    }
    return str;
}

string getlat(string s) //index 80 is blank
{
    string str;
    int n;
    for(int i= 80; i < 114; i ++) 
    {
        if(s[i] != ' ') //Finds a number
        {
            n = i; //position of first found number
            break;
        }
    }
    for(n; n<114; n++)
    {
        if(s[n] == '-')
        {
            break;
        }
        else if(s[n] != ' ')
        {
            str = str + s[n];
        }
        else
            break;
    }
    
    return str;
}

string getarea(string s)
{
    string str;
    int n;
    for(int i= 66; i < 114; i ++) //index 66 is blank space after population
    {
        if(s[i] != ' ') //Finds a number
        {
            n = i; //position of first found number
            break;
        }
    }
    for(n; n<114; n++)
    {
        if(s[n] != ' ')
        {
            str = str + s[n];
        }
        else
            break;
    }
    
    return str;
}


string getpop(string s)
{
    string str;
    int n;
    for(int i= 48; i < 114; i ++)
    {
        if(s[i] != ' ') //Finds a number
        {
            n = i; //position of first found number
            break;
        }
    }
    for(n; n<114; n++)
    {
        if(s[n] != ' ')
        {
            str = str + s[n];
        }
        else
            break;
    }

        return str;
}

string gettown(string s)
{
    string town;
    char space = ' ';
    for(int i = 10; i< 40; i++)
    {
        if(s[i] == space && s[i+1] == space)
        {
            break;
        }
        else{
            town = town + s[i];
        }
    }

    return town;
}

string getstate(string s)
{
    string state;
    for(int i=8; i< 10; i++)
    {
        state = state + s[i];
    }
    return state;   
}


string getcode(string s)
{
    string code;
    for(int i=0; i< 8; i++)
    {
        code = code + s[i];
    }
    return code;
}

void options(Hashtable H)
{ 
    while(1)
    {
        cout << "Welcome, input 'S' to enter a place name and state" << endl;
        cout <<"Input 'N' for a specific place name" << endl;
        cout <<"Or 'Q' to quit this program:";
        string choice;
        cin>>choice;
        if(choice == "S")
        {
            cout << "Please enter a place name: ";
            string p; getline(cin >> ws,p);
            cout << "Please enter a state: ";
            string s; cin >> s;
            H.printtownst(p,s,cout);
            cout << endl << "If no output, place name does not belong to given state";
            cout << endl << endl;
        }
        else if(choice == "N")
        {
            cout << "Please enter a place name: ";
            string p; getline(cin >> ws,p);
            H.printtowns(p,cout);
            cout << endl << endl;
        }
        else if(choice == "Q")
        {
            cout << "Goodbye!"<<endl;
            break;
        }
        else{
            cout << "Unrecognized command" << endl << endl;
        }
    }
}

void readfile()
{
    ifstream file;
    file.open("named-places.txt");
    string line;
    Hashtable H;
    
    
    string code, town, state, pop, area, lat, lon, road, dist;
    if(file.is_open())
    {
        while(getline(file,line))
        {
            code = getcode(line); town = gettown(line); state = getstate(line); pop = getpop(line); area = getarea(line); lat = getlat(line); lon = getlon(line); road = getroad(line); dist = getdist(line);
            H.insert(code, state, town, pop, area, lat, lon, road, dist);
        }
    } 
    else
    {
        cout << "Error reading file!" << endl;
    }
    file.close();

    options(H);
    
}


int main()
{ 
    readfile();
    return 0;
    
}
