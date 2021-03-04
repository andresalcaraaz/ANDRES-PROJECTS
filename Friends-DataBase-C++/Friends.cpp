// Name: Mario Alcaraz
// Assignment: Programming  Assignment 1
// Date Due: February 28th
//Course: CSC 372 Data Structures
//Professor: Dr. Jonathan M. Graham


/* Purpose of program: A program to maintain a database of your friends. The data to be maintained on the friends consist of first name, last name, year of birth, month of birth and day of birth and sex. The data is to be stored in a linked list of struct and an object-oriented interface be provided to access the data and provide functionality. A menu driven interface is to be provided to maintain the database*/

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>

using namespace std;

// MARK: Friend Struct
struct Friend {
    string last;
    string first;
    int  yob;
    int mob;
    int dob;
    int age;
    string sex;
    string season;
    string dayBorn;
    struct Friend* next;
};

void populate(Friend* &head, int& size);
void getCurrrentDate(int &year, int& month, int& day);
void insert(Friend** head);
void getData(Friend** head);
void menu(int &choice);
void deleteFriend(Friend** head);
void printNames(Friend** head);
void printInfo(Friend** head);
void oldest(Friend** head);
void youngest(Friend** head);
void sortedList(Friend** head);
void averageAge(Friend** head);
void maleFriends(Friend** head);
void empty();
string calcSeason (int month, int day);
string dayBorn(int year, int month, int day);
int getAge(int y,int m,int d, int currYear, int currMonth, int currDay);
string getSeason ();
int currYear, currMonth , currDay;

// MARK: Main Method
int main(int argc, const char * argv[]) {
    int choice;
    
    getCurrrentDate(currYear, currMonth, currDay);
    Friend* head;
    
    do{
        menu(choice);
        
        if(choice == 1){
            insert(&head);
        }
        if(choice == 2){
            deleteFriend(&head);
        }
        if(choice == 3){
            printNames(&head);
        }
        if(choice == 4){
            printInfo(&head);
        }
        if(choice == 5){
            oldest(&head);
        }
        if(choice == 6){
            youngest(&head);
        }
        if(choice == 7){
            sortedList(&head);
        }
        if(choice == 8){
            averageAge(&head);
        }
        if(choice == 9){
            maleFriends(&head);
        }
        
        if(choice == 0){
            cout << "Goodbye :) " << endl;
            choice = 0;
        }
    }
    while (choice != 0);
    return 0;
}


// MARK: Menu Method to navigate along the program
void menu(int &choice){
    bool valid = false;
    do {
        cout << "Please Select one of the following options:" << endl;
        cout << "1) Add friend " << endl;
        cout << "2) Delete a friend by last name " << endl;
        cout << "3) Print the names ages of all friends " << endl;
        cout << "4) Print information on a friend: name, age, day born (Monday, Tuesday,….,), season born " << endl;
        cout << "5) Print the oldest friend " << endl;
        cout << "6) Print the youngest friend " << endl;
        cout << "7) Print sorted list of friends " << endl;
        cout << "8) Print the average age of friends " << endl;
        cout << "9) Print the list of male friends " << endl;
        cout << "0) End Program " << endl;
        cin >> choice;
        
        if(cin.good()){
            //everything went well, we'll get out of the loop and return the value
                       valid = true;
        }
        else
                {
                    //something went wrong, we reset the buffer's state to good
                    cin.clear();
                    //and empty it
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid input; please re-enter." << endl;
                }
    }
       
    while(!valid);
        
    
}


// MARK: Get Data Method
void getData(string& f, string& l, string& s,int& y, int& m, int& d){
    cout << "Please type friend's first name: " << endl;
    cin >> f;
    cout << "Please type friend's last name: " << endl;
    cin >> l;
    cout << "Please type friend's year of birth (yyyy): " << endl;
    cin >> y;
    cout << "Please type friend's month of birth (mm): " << endl;
    cin >> m;
    cout << "Please type friend's day of birth (dd): " << endl;
    cin >> d;
    cout << "Please type friend's sex (f/m): " << endl;
    cin >> s;
}


// MARK: Insert new Friend Method
void insert(struct Friend** head) {
    string f, l, s;
    int y = 0,m = 0,d = 0;
    getData(f,l,s,y,m,d); // gets data of the new friend to insert
    
    Friend *tmp = new Friend;
    tmp->first = f;
    tmp->last = l;
    tmp->yob = y;
    tmp->mob = m;
    tmp->dob = d;
    tmp->sex = s;
    tmp->next = NULL;
    
    tmp->age = getAge(tmp->yob, tmp->mob, tmp->dob, currYear, currMonth, currDay);
    tmp->dayBorn = dayBorn(tmp->yob, tmp->mob, tmp->dob);
    tmp->season = calcSeason(tmp->mob, tmp->dob);
    
    if(*head == NULL){
        *head = tmp;
    }
    
    else
    {
        struct Friend *lastNode = *head;
        //last node's next address will be NULL.
        while(lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        //add the newNode at the end of the linked list
        lastNode->next = tmp;
    }
    
};


// MARK: Delete friend from linked list by last name
void deleteFriend(struct Friend** head){
    string lastName;
    struct Friend *ptr = *head;
    struct Friend *tmp = *head;
   
    // Check if the Database is not empty first
    if(ptr == NULL){
        empty();
        return;
    }
    cout << "Please provide the last name of the friend that you are willing to remove:" << endl;
    cin >> lastName;
    
    // If linked list is empty
    if (*head == NULL)
        return;
    
    // If head needs to be removed
    if (ptr->last == lastName)
    {
        *head = ptr->next;   // Change head
        free(ptr);               // free old head
        return;
    }
    ptr = ptr->next;
    while (ptr->last != lastName) {
        tmp = ptr;
        ptr = ptr->next;
    }
    tmp->next = ptr->next;
    free(ptr);
};


// MARK: Prints Name and age of all nodes in the linked list of Friends
void printNames(struct Friend** head){
    struct Friend *ptr = *head;
    
    // Check if the Database is not empty first
    if(ptr == NULL){
        empty();
        return;
    }
    while(ptr != NULL){
        cout << ptr->first << " " << ptr->last << " " << ptr->age << endl;
        cout << endl;
        ptr = ptr->next;
        
    }
};

//MARK: Method to print info of a specific friend
void printInfo(struct Friend** head){
    struct Friend *ptr = *head;
   
    // Check if the Database is not empty first
    if(ptr == NULL){
        empty();
        return;
    }
    string last;
    cout << "Please enter the last name of the friend that you would like to request the info: " << endl;
    cin >> last;
    cout << endl;
    
    while(ptr->last != last){
        ptr = ptr->next;
    }
    cout << "-----------------------------------------" << endl;
    cout << ptr->first << " " << ptr->last << endl;
    cout << "Age " << ptr->age << " years old" << endl;
    cout << "Season born: " << ptr->season <<endl;
    cout << "Day born: " << ptr->dayBorn << endl;
    cout << "-----------------------------------------" << endl;
    
};


// MARK: Print oldest friend with name and age
void oldest(struct Friend** head){
    int max = 0;
    struct Friend *ptr = *head;
    
    // Check if the Database is not empty first
    if(ptr == NULL){
        empty();
        return;
    }
    while (ptr != NULL) {
        int age = ptr->age;
        if(age > max){
            max = age;
            ptr = ptr->next;
        }
        else{
            ptr = ptr->next;
        }
    }
    struct Friend *tmp = *head;
    while(tmp != NULL){
        int age = tmp->age;
        if(age == max){
            cout << "The oldest friend is " << tmp->first << " " << tmp->last << " and is  " << age << " years old" << endl;
            cout << "Birth date: " << tmp->mob << "/" << tmp->dob << "/" << tmp->yob << endl;
            cout << "Season born: " << tmp->season << endl;
            if(tmp->sex == "m"){
                cout << "Gender: Male" << endl;
            }
            if(tmp->sex == "f"){
                cout << "Gender: Female" << endl;
            }
            cout << endl;
            tmp = NULL;
        }
        else {
            tmp = tmp->next;
        }
    }
};


// MARK: Method to print the youngest friend
void youngest(struct Friend** head){
    int min = 1000000000;
    
    struct Friend *ptr = *head;
    
    // Check if the Database is not empty first
    if(ptr == NULL){
        empty();
        return;
    }
    while (ptr != NULL) {
        int age = ptr->age;
        if(age < min){
            min = age;
            ptr = ptr->next;
        }
        else{
            ptr = ptr->next;
        }
    }
    
    struct Friend *tmp = *head;
    while(tmp != NULL){
        int age = tmp->age;
        if(age == min){
            cout << "The youngest friend is " << tmp->first << " " << tmp->last << " and is  " << age << " years old" << endl;
            cout << "Birth date: " << tmp->mob << "/" << tmp->dob << "/" << tmp->yob << endl;
            cout << "Season born: " << tmp->season << endl;
            if(tmp->sex == "m"){
                cout << "Gender: Male" << endl;
            }
            if(tmp->sex == "f"){
                cout << "Gender: Female" << endl;
            }
            cout << endl;
            tmp = NULL;
        }
        else {
            tmp = tmp->next;
        }
    }
    
};



// MARK: Method to sort list of friend
void sortedList(struct Friend** head){
    list <string> names;
    struct Friend *tmp = *head;
    
    // Check if the Database is not empty first
    if(tmp == NULL){
        empty();
        return;
    }
    while(tmp != NULL){
        names.push_back(tmp->last);
        tmp = tmp->next;
    }
    names.sort();
    cout << " Friends sorted on alphabetical order based on last name: " << endl;
    for (std::list<std::string>::iterator it=names.begin(); it!=names.end(); ++it){
    std::cout << ' ' << *it;
    std::cout << '\n';
    }
    cout << endl;
};


//MARK: Method to calculate the average age of all the friends
void averageAge(struct Friend** head){
    struct Friend *tmp = *head;
    
    // Check if the Database is not empty first
    if(tmp == NULL){
        empty();
        return;
    }
    vector<int> ages;
    int sum = 0;
    float average;
    
    while(tmp != NULL){
        ages.push_back(tmp->age);
        tmp = tmp->next;
    }
    
    for(int i = 0; i < ages.size(); i ++){
        sum = sum + ages[i];
    }
    
    average = (sum/ages.size());
    cout << " The average age of the friends is " << average << endl;
    cout << endl;
    
};

// MARK: Method to print all male friends on the list
void maleFriends(struct Friend** head){
    struct Friend *tmp = *head;
    
    // Check if the Database is not empty first
    if(tmp == NULL){
        empty();
        return;
    }
    cout << "Here is a list of the male friends in the database:" << endl;
    cout<< "-----------------------------------------------------" << endl;
    while(tmp != NULL){
        if(tmp->sex == "m"){
            cout << tmp->first << " " << tmp->last << endl;
            tmp = tmp->next;
        }
        else if (tmp->sex == "f"){
            tmp = tmp->next;
        }
    }
    cout << endl;
};

// MARK: Method to calculate the age and return value  as an int
int getAge(int y, int m,int d, int currYear, int currMonth, int currDay){
    
    
    int age = currYear - y;
    if (currMonth < m)
        age--;
    if (currMonth == m && currDay < d)
        age--;
    
    
    return age;
}

//MARK: Method to get the season on which the friend was born & return it as a string
string calcSeason(int month, int day)
{
    string season = "";
    if (month == 1 || month == 2)
        season = "Winter";
    if (month == 4 || month == 5)
        season = "Spring";
    if (month == 7 || month == 8)
        season = "Summer";
    if (month == 10 || month == 11)
        season = "Fall";
    if (month == 3 && day >= 21)
        season = "Spring";
    if (month == 3 && day < 21)
        season = "Winter";
    if (month == 6 && day >= 21)
        season = "Summer";
    if (month == 6 && day < 21)
        season = "Spring";
    if (month == 9 && day >= 21)
        season = "Fall";
    if (month == 9 && day < 21)
        season = "Summer";
    
    return season;
}


//MARK: Method to calculate the day that the friend was born and return as string value
string dayBorn(int year, int month, int day)
{
    int d = day;
    int m = month;
    
    int y = year % 100;
    int c = year / 100;
    if (m == 1 || m == 2)
    {
        m += 12;
        y--;
    }
    
    int D = (d + (m + 1) * 26 / 10 + y + y / 4 + c / 4 + 5 * c) % 7;
    if (D == 0)    return "Saturday";
    else if (D == 1)return "Sunday";
    else if (D == 2)return "Monday";
    else if (D == 3)return "Tuesday";
    else if (D == 4)return "Wednesday";
    else if (D == 5)return "Thursday";
    else if (D == 6)return "Friday";
    return "impossible";
    
}

//MARK: Method to get the current date and store it for future use
void getCurrrentDate(int &year, int& month, int& day){
    bool valid = false;
    bool val = false;
    bool v = false;
    
    // Validate the input
    do {
        cout << "Please enter the current year (yyyy) " << endl;
        cin >> year;
        if(cin.good()){
            //everything went well, we'll get out of the loop and return the value
                       valid = true;
        }
        else
                {
                    //something went wrong, we reset the buffer's state to good
                    cin.clear();
                    //and empty it
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid input; please re-enter." << endl;
                }
    }
    while (!valid);
    
    // Validate the input
    do {
        cout << "Please enter the current month (mm) " << endl;
        cin >> month;
        if(cin.good()){
            //everything went well, we'll get out of the loop and return the value
                       val = true;
        }
        else
                {
                    //something went wrong, we reset the buffer's state to good
                    cin.clear();
                    //and empty it
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid input; please re-enter." << endl;
                }
    }
    while (!val);
    
    // Validate the input
    do{
        cout << "Please enter the current day (dd)" << endl;
        cin >> day;
        if(cin.good()){
            //everything went well, we'll get out of the loop and return the value
                       v = true;
        }
        else
                {
                    //something went wrong, we reset the buffer's state to good
                    cin.clear();
                    //and empty it
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid input; please re-enter." << endl;
                }
    }
    while (!v);
    }
   
    
//MARK: Method to display that the Database is still empty
void empty(){
    cout << "The Database is still empty. Please add some friends first... " << endl;
    cout << endl;
}
