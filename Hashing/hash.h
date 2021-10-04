//hash.h supplement

#include <iostream>
#include <string>
#include <iomanip> 
using namespace std;

#ifndef hash_h
#define hash_h


class Hashtable{
    protected:
        static const int hashsize = 26003; //prime and close to file sie
        struct node {
            string code, state, town, pop, area, lat, lon, road, distance;
            node *next;
            node(string cod, string stat, string tow,string po,string are,string la,string lo,string roa,string dis)
            {
                code = cod; state = stat; town = tow; pop = po; area = are; lat = la; lon = lo; road = roa; distance = dis;
                next = NULL;
            }
        }; 
        node* table[hashsize];

    public:
        Hashtable();
        unsigned int hashval(string p);  //creates a value
        void insert(string code, string state, string town, string pop, string area, string lat, string lon, string road, string dist); //inserts a struct into the table
        ostream& printtownst(string town, string state, ostream& out); //prints info on specific place
        ostream& printtowns(string town, ostream& out); //prints info for various towns
};


Hashtable:: Hashtable() //construct table
{
    int i=0;
    while(i < hashsize) {
        table[i] = new node("NULL","NULL","NULL","NULL","NULL","NULL","NULL","NULL","NULL");
        table[i]->next = NULL;
        i++;
    }
}


unsigned int Hashtable:: hashval(string s){ 
    unsigned int h = 987123654;
    for (int i = 0; i < s.length(); i += 1)
        h = h * 691 + s[i];
    if (h < 0)
        h = -h;
    return h%hashsize;
 
}

void Hashtable:: insert(string code, string state, string town, string pop, string area, string lat, string lon, string road, string dist)
{
    unsigned int i = hashval(town);
    node* temp = new node(code, state, town, pop, area, lat, lon, road, dist);
    if(table[i]->town == "NULL") 
    {
        table[i] = temp;
    }
    
    else
    {
        node* trav = table[i];
        while(trav->next != NULL)
        {
            trav = trav->next;
        }
        trav->next = temp;
    }   
}

ostream& Hashtable:: printtownst(string town, string state, ostream& out)
{
    unsigned int i = hashval(town);
    node* nav = table[i];
    if(table[i]->town != town)
    {
        out << "This place does not exist or could not be found" << endl;
        return out;
    }
    else{
        while(nav != NULL)
        {
            if(nav->state == state && nav->town == town)
            {
                cout << "____________________________________________________________________________________________________"<< endl;
                out << nav->code << "   " << nav->state << "    " << nav->town << "     " << nav->pop << "     " << nav->area << "     " << nav->lat << "     " << nav->lon << "     " << nav->road << "     " << nav->distance << endl;           
            }
            nav = nav->next;
        }
    }
    
    return out;
}


ostream& Hashtable:: printtowns(string town,ostream& out)
{
    unsigned int i = hashval(town);
    node* nav = table[i];
    if(table[i]->town != town)
    {
        out << "These places do not exist or could not be found" << endl;
    }
    else{
        while(nav != NULL)
        {
            if(nav->town == town)
            {
                cout << "____________________________________________________________________________________________________"<< endl;
                out << nav->code << "   " << nav->state << "    " << nav->town << "     " << nav->pop << "          " << nav->area << "     " << nav->lat << "     " << nav->lon << "     " << nav->road << "     " << nav->distance << endl;
            }
            nav = nav->next;
        }
    }
        return out;
}
#endif
