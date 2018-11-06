using namespace std;

/**
 * Header files 
 */
#include <iostream> //For basic input/output operations

/**
 * Displays home screen only if the administrator has entered the correct credentials
 * Note: Administrator is anyone using our school management system app
*/
void displayHomeScreen()
{
  cout << "1. Update School Data Records\t\t\t\t\t\t\t2. View School Data Records";
  cout << "\na. Add or remove student\t\t\t\t\t\t\td. View student database";
  cout << "\nb. Add or remove class\t\t\t\t\t\t\t\te. View staff database";
  cout << "\nc. Add or remove school staff\t\t\t\t\t\t\tf. View class database";

  cout << "\n\n3. Accounting and Finance";
  cout << "\ng. Receive student fee";
  cout << "\nh. Pay salaray to school staff";
  cout << "\ni. View last five transactions";
}

/**
 * main() starts here
*/
int main()
{
  displayHomeScreen();
}
