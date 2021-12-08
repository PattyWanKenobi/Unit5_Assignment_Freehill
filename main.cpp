//Date created: 12/06/2021
//Tarrant County College/Dr. Tyson McMillan
//A restaraunt menu with accumulating quantities, prices, and total costs

#include <iostream>
#include<string>
#include<vector>
#include<iomanip>
#include <fstream>
using namespace std; 

class MenuItem
{
  private:
    string name;
    double itemCost; 
    string desc; 
    char addLetter; 
    char removeLetter;
    int count; 

  public:
  //set up default constructor
  //this will be how the default menu is set
  MenuItem()
  {
    name = "item";
    itemCost = 0.00;
    desc = "delicious";
    addLetter = 0;
    removeLetter = 0;
    count = 0;
  }

  //setters and getters
  void setName(string n) {name = n;}
  void setItemCost(double cost) {itemCost = cost;}
  void setDesc(string description) {desc = description;}
  void setAddLetter(char addLet) {addLetter = addLet;}
  void setRemoveLetter(char remLet) {removeLetter = remLet;}
  void setCount(int quant) {count = quant;}
  string getName() const {return name;}
  double getItemCost() const {return itemCost;}
  string getDesc() const {return desc;}
  char getAddLetter() const {return addLetter;}
  char getRemoveLetter() const {return removeLetter;}
  int getCount() const {return count;}
};


//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Item 3", "Item 4", "Item 5", "Item 6", "Item 7"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    entireMenu[i].setName(defaultMenuNames[i]); //= defaultMenuNames[i]; 
    entireMenu[i].setAddLetter(defaultAddLetters[i]);// = defaultAddLetters[i]; 
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); //= defaultRemoveLetters[i]; 
    entireMenu[i].setItemCost(3.00 + i); // = (3.00 + i); //set a random starter cost for each item
    entireMenu[i].setCount(0); // = 0; //initialze all counts to 0
    entireMenu[i].setDesc("delicious"); // = "delicious"; //set all default desc to "delicous"
  }


}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << "DrT's Effcient Menu" << endl; 
  cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].getAddLetter() << ")" << setw(10) << m[i].getName() 
    << setw(5) << "$" << m[i].getItemCost() << setw(5) << "(" << m[i].getRemoveLetter()
    << ")" << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc() 
    <<endl; 
  }

}



void acceptOrder(vector<MenuItem> &m)
{
  
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0; 
  double tip;
  string payMethod;
  double tender;
  double amountDue;

  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option; 

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].getAddLetter())
      {
        cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
        m[i].setCount(m[i].getCount() +1); //increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].getName() << endl;
        subtotal += m[i].getItemCost(); //increment the subtotal by the cost of the item 
        showMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
      }
      else if(option == m[i].getRemoveLetter())
      {
        cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
        if(m[i].getCount() > 0) //subtract if and only if the count is > 0
        {
          m[i].setCount(m[i].getCount() - 1); //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].getName() << endl;
          subtotal -= m[i].getItemCost(); //decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;  
        }
        else //the the user why you blocked item removal 
        {
            
            cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getAddLetter() && 
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X' 
            ) //test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  }while(option != 'x' && option != 'X'); 
  cout << "\nThank you for placing your order." << endl; 
  //handle the tip process here
  cout << "Please enter amount for tip ($" << (subtotal * 0.2) << " recomended): ";
  cin >> tip;
  double tax = (subtotal * 0.0825);
  double total = (subtotal + tip + tax);
  cout << "Total due = $" << total << endl;
  cout << "Cash or Credit?: ";

  cin >> payMethod;

  while (payMethod != "cash" && payMethod != "Cash" && payMethod != "Credit" &&payMethod != "credit") 
    {
       
      cout << "Invalid Payment Method - Please Choose Cash or Credit";
      cin >> payMethod;

    } 

    //accept tender amount from customer
    cout << "Please enter amount tendered: ";
    cin >> tender;

    if (tender >= total)
    {
      if (payMethod == "cash" || payMethod == "Cash")
      {
        cout << "Total = $" << total <<endl;
        cout << "Amount tendered = $" << tender << endl;
        cout << "Change due = $" << (total - tender);
      }
      else if (payMethod == "credit" || payMethod == "Credit")
      {
        cout << "Payment processed!";
      }
    }
 void printReceipt(vector<MenuItem> &m, double subtotal);
  {
    cout << "\n\n\n\nReceipt" << endl;
    cout << "Subtotal: " << subtotal << endl;
    cout << "Tax: " << tax << endl;
    cout << "Tip: " <<tip << endl;
    cout << "Total Due: " << total;
  }

  void writeReceipt(vector<MenuItem> &m, double subtotal);
  {
    ofstream ReceiptFile("receiptFile.txt");
    ReceiptFile << "Receipt" << endl;
    ReceiptFile  << "Subtotal: " << setprecision(2) << subtotal << endl;
    ReceiptFile << "Tax: " << tax << endl;
    ReceiptFile << "Tip: " <<tip << endl;
    ReceiptFile << "Total Due: " << total;
    ReceiptFile.close();

  }
  
  
}


int main() 
{
  vector<MenuItem> wholeMenu; 
  populateMenu(wholeMenu); //put some default values in the menu
  showMenu(wholeMenu); //print the current data of the menu on screen 
  acceptOrder(wholeMenu); 
  
  return 0; 
}

