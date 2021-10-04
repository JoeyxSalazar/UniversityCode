#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct person
{ int ssn, bday, zipcode;
  string fname, lname;
};

struct node
{ person p;
  node * left, * right;

  node(person newp)
  { p = newp;
    left = NULL;
    right = NULL; }
};

class tree
{ protected:
    node * root;

  public:
    tree()
    { root = NULL; }

    void _add(node * & r, person & newp)
    { if(r != NULL)
      { 
        if(newp.lname < r->p.lname)
          _add(r->left, newp);
        else if(newp.lname > r->p.lname)
          _add(r->right, newp);
        else if(newp.lname == r->p.lname)
        { 
          if(newp.fname < r->p.fname)
            _add(r->left, newp);
          else
            _add(r->right, newp); 
        }             
      }
      else
        r = new node(newp);
        return;
        
      }

    void add(person & newp)
    {_add(root, newp); }

    void _age_add(node * & r, person & newp)
    { if(r != NULL)
      {
        if(newp.bday < r->p.bday)
          _age_add(r->left, newp);
        else
          _age_add(r->right, newp);
      }
      else
        r = new node(newp);
        return;
    }

    void age_add(person & newp)
    { _age_add(root, newp); }

    void oldest()
    { node * curr = root;
      while(curr->left != NULL)
        curr = curr->left;
      cout << endl << endl << "The oldest person is :" << curr->p.fname << " " << curr->p.lname << endl;
        
    }

    void find(node* n,string fnam, string lnam)
    { 
        if(n != NULL)
        {	
          int lcom = lnam.compare(n->p.lname);
          if(lcom < 0)
          {
            find(n->left, fnam, lnam);
          }
          else if(lcom > 0)
          {
            find(n->right, fnam, lnam);
          }
          else if(lcom == 0)
          {
            int fcom = fnam.compare(n->p.fname);
            if(fcom < 0)
            {
              find(n->left, fnam, lnam);
            }
            else if(fcom > 0)
            {
              find(n->right, fnam, lnam);
            }
            else if(fcom == 0)
            {
              cout << "Search Successfully Completed!" << endl;
              cout << n->p.ssn << " " << n->p.bday << " " << n->p.fname << " " << n->p.lname << " " << n->p.zipcode << endl;
              return;
            }
            else
              n = NULL;
          }
          else
            cout << "Person not found" << endl; return;
        }
    cout << "Person not found" << endl;
    return;
    }

    void zipcode(node * & r, int zip)
    { if(r == NULL)
        return;
      zipcode(r->left, zip);
      if(zip == r->p.zipcode)
        cout << r->p.fname << " " << r->p.lname << " " << endl; 
      zipcode(r->right, zip);
    }

    void zipcode(int zip)
    { zipcode(root, zip); }


 ostream &_print(node* r, ostream &out) {
	if (r!=NULL) {
		_print(r->left,out);
		out << r->p.ssn << " " << r->p.bday << " " << r->p.fname << " " << r->p.lname << " " << r->p.zipcode <<endl;
		_print(r->right,out);
	}
	return out;
}


ostream &print(ostream &out) {
	return _print(root,out);
}

    person maxvalleft ()
    {
      root = root->left;
        while(root != NULL && root->right != NULL)
        {
            root = root->right;
        }
        person out;
        out = root->p;
        return out;
    }

    void remove(node* root, string lnam,string fnam)
    {
      int lcom = lnam.compare(root->p.lname);
      int fcom = fnam.compare(root->p.fname);

        if (root == NULL)
            return;
    
        else if (lcom < 0)
            remove(root->left, lnam, fnam);
    
        else if (lcom > 0)
            remove(root->right, lnam, fnam);
    
        else 
        {
            if(fnam == root->p.fname)
                if (root->left==NULL && root->right==NULL)
                    return;
                else if (root->left == NULL) {
                    node* temp = root->right;
                    //free(root);
                    delete root;
                    return;
                }
                else if (root->right == NULL) {
                    node* temp = root->left;
                    delete root;
                    return;
                }
            else if(fcom < 0)
                remove(root->left,lnam, fnam);
            else
                remove(root->right,lnam, fnam);

            person replace = maxvalleft();
            root->p = replace;
            remove(root->right, replace.lname, replace.fname);
        }
        return;
    }


    node* getroot(){return root;}
};


int main() { 

fstream filename; filename.open("smalltxt.txt");
int sn, bd, zip; string fnam, lnam;
tree Tree;
tree oldtree;
if(filename.is_open()) 
{
    while(filename >> sn >> bd >> fnam >> lnam >> zip)
    {
        person newp;
        newp.fname = fnam;  newp.lname = lnam; newp.ssn = sn; newp.bday= bd; newp.zipcode = zip;
        Tree.add(newp);
        oldtree.age_add(newp);
    }
}
else cout << "error reading file" << endl;
filename.close();

  while(true)
	{
		string inp;
		cout << endl << endl;
		cout << "Please make a selction: " <<endl;
		cout << "'FIND' to search the directory" << endl;
		cout << "'PRINT' to return all members of the database" << endl;
		cout << "'ZIP' to return all members belonging to a zipcode" << endl;
		cout << "'OLDEST' to retuen the oldest member of the database" << endl;
		cout << "'DELETE' to delete a member of the database" << endl; 
		cout << "'EXIT' to exit the program" << endl; cout << "Enter Selection:";
		cin >> inp;
		if(inp == "FIND") //Works
		{
			string fname, lname;
			cout << "Enter first name: "; cin >> fname; 
			cout << "Enter last name: "; cin >> lname;
      node* root = Tree.getroot();
			Tree.find(root,fname,lname);
		}
		else if(inp == "PRINT") //Works
		{
			Tree.print(cout);
			cout << endl << endl << endl;
		}
		else if(inp == "ZIP") //Works
		{
			int zipin;
			cout << "Enter zipcode:"; cin >> zipin;
			Tree.zipcode(zipin);
		}
		else if(inp == "OLDEST") //Works
		{
			oldtree.oldest();
		}
		else if(inp == "DELETE") //Doesnt work
		{
			string fn, ln;
			cout << "Enter first name:"; cin >> fn; 
			cout << "Enter last name:"; cin >> ln; cout << endl;
      node* temp = Tree.getroot();
      Tree.remove(temp,fn,ln);
		}
		else if(inp == "EXIT")
		{
			break;
		}
    else
      cout <<"Invalid input";
	}

    return 0;
} 


