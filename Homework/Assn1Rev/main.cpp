/* 
 * File:   main.cpp
 * Author: mikemorales
 *
 * Created on March 11, 2015, 3:33 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void menu();
void problem1();
void problem2();
//leapYr goes with problem 3
bool leapYr(int year);
void problem3();
void problem4();
//frnToCel goes with problem 5
float frnToCel(float);
void problem5();
void problem6();
//prntArry, sort, and binarySearch go with problem 7
void prntArray(string [], int, int);
void sort(string [], int);
int binarySearch(string [], int, string);
void problem7();

int main(int argc, char** argv) 
{
    string input;
    
    do 
    {
        int problem;
        
        //Prompts user to enter a problem
        menu();
        cin >> problem;
        cout << endl;
        
        switch (problem)
        {
            case 1: 
                problem1();
                break;
            case 2:
                problem2();
                break;
            case 3:
                problem3();
                break;
            case 4:
                problem4();
                break;
            case 5:
                problem5();
                break;
            case 6:
                problem6();
                break;
            case 7:
                problem7();
                break;
            default :
                cout << "Invalid number." << endl;     
        }
        
        //Prompt user try another problem
        cout << "Would you like to try a problem? Y/N" << endl;
        cin >> input;
        
        
    } while (tolower(input[0]) == 'y');
    
    return 0;
}

// Prompt user to enter a problem
void menu()
{
    cout << "Enter 1 for problem 1" << endl;
    cout << "Enter 2 for problem 2" << endl;
    cout << "Enter 3 for problem 3" << endl;
    cout << "Enter 4 for problem 4" << endl;
    cout << "Enter 5 for problem 5" << endl;
    cout << "Enter 6 for problem 6" << endl;
    cout << "Enter 7 for problem 7" << endl;
}

void problem1()
{
    //declare celcius
    float celcius;
    //declare fahrenheit 
    float frnheit;
    
    //prompt user to enter temperature
    cout << "Enter a temperature in celcius: ";
    cin >> celcius;
    
    //convert celcius to farhenheit 
    frnheit = static_cast<float>(9)/5 * celcius + 32  ;
    
    //Output results
    cout << "The temperature in fahrenheit is " << setprecision(1) << fixed 
            << frnheit << " degrees." << endl << endl;   
}

void problem2()
{
    const float YEN_PER_DOLLAR = 121.39;
    const float EUROS_PER_DOLLAR = 0.95;
    float yen;
    float euros;
    float dollar;
    
    // Prompt user to enter amount in U.S. dollar amount
    cout << "Enter amount in U.S. currency: ";
    cin >> dollar;
    
    //convert dollars to yen
    yen = dollar * YEN_PER_DOLLAR;
    //convert dollars to euros
    euros = dollar * EUROS_PER_DOLLAR;
    
    //Output results for converting dollars to yen and euros
    cout << "In yen: " << setprecision(2) << fixed << yen << endl;
    cout << "In euros: " << euros << endl << endl;   
}

void problem3()
{
    int month;
    int year;
    
    //prompt user to enter a month
    cout << "Enter a month: ";
    cin >> month;
    
    //prompt user to enter a year
    cout << "Enter a year: ";
    cin >> year;
    
    
    //determine month entered corresponds to 31 days
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
            || month == 10 || month == 12)
    {
        cout << "31 days";
    }
    //determine if month entered corresponds to 30 days
    if (month == 4 || month == 6 || month == 9 == 11)
    {
        cout << "30 days";
    }  
    //determine if month entered is february and a leapyear
    if (month == 2 && leapYr(year) == true)
    {
        cout << "29 days";
    }
    //determine if month entered is february and not a leapyear
    if (month == 2 && leapYr(year) == false)
    {
        cout << "28 days";
    }
    cout << endl << endl;
}

bool leapYr(int year)
{
    // determine if year is leap year
    if ((year % 100 == 0 && year % 400 == 0) 
            || (year % 100 != 0 && year % 4 == 0))
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void problem4()
{
    float organisms;
    //declare population increase
    float popIncr;
    //declare number of days organisms will multiply
    int numOfDays;
    
    //use loop to make sure user enters at least 2
    do 
    {
        //promp user to enter organisms
        cout << "Enter number of at least 2 organisms: ";  
        cin >> organisms;
        
    } while (organisms < 2);
    
    do 
    {
        //prompt user to enter population increase in percentage
        cout << "Enter a percentage for population increase: ";
        cin >> popIncr;
        
    } while (popIncr < 0);
    
    do 
    {
        //prompt user to enter number of days organisms will multiply
        cout << "Enter number of days organisms will multiply: ";
        cin >> numOfDays;
                
    } while (numOfDays < 1);
    
    cout << endl;
    
    //Output number of organisms for each day
    for (int i = 0; i < numOfDays; i++)
    {
        cout << setprecision(1) << fixed << "Day " << i + 1 << ": "
                << organisms << endl;
        
        //determine number of organisms from percentage increase entered
        organisms = organisms * (popIncr * .01 + 1);
    } 
    cout << endl;
}

void problem5()
{
    //Use loop to call frnToCell function to get temperature conversions
    //from fahrenheit to celcius from temperatures 0 - 20
    for (int i = 0; i <= 20; i++) {
        cout << "Fahrenheit: " << i << " Celcius: " << setprecision(1) << fixed
                << frnToCel(i) << endl;
    }
}

//fahrenheit to celcius conversion
float frnToCel(float frnheit)
{
    //convert fahrenheit to celcius
    float celcius = static_cast<float>(5)/9 * (frnheit - 32);
    
    return celcius;
}

void problem6()
{
    // declare array for days
    char days[3][30];
    //rainy, sunny, cloudy days for each month
    int rainy = 0, sunny = 0, cloudy = 0;
    //total rainy, sunny, cloudy days for all months combined
    int totalRain = 0, totalSun = 0, totalCloud = 0;
    //Rain for june, july, august
    int juneRain, julyRain, augustRain;
    //setting up bool for month with most rain
    bool rainyJune = false, rainyJuly = false, rainyAugust = false;
           
    ifstream infile;
    //open file to read from
    infile.open("RainOrShine.txt");
    
    //create loop to put values from file into array
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            infile >> days[i][j];
        }
    }
    
    //close file
    infile.close();
    
    //create loop to determine if it was rainy, sunny, or cloudy
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            //if it was rainy then add 1 to number of rainy days
            if (days[i][j] == 'R')
            {
                rainy += 1;
                totalRain += 1;
            }
            //if it was sunny then add 1 to number of sunny days
            else if (days[i][j] == 'S')
            {
                sunny += 1; 
                totalSun += 1;
            }
            //if it was cloudy then add 1 to number of cloudy days
            else
            {
                cloudy += 1;
                totalCloud += 1;
            }
        }
        // 0 represents june
        // if june output number of rainy, cloudy, and sunny days for june
        if (i == 0)
        {
            juneRain = rainy;
            cout << "June Weather: Rainy: " << rainy << " Sunny: " << sunny
                    << " Cloudy: " << cloudy << endl;
        }
        // 1 represents july
        // if july output number of rainy, cloudy, and sunny days for july
        else if (i == 1)
        {
            julyRain = rainy;
            cout << "July Weather: Rainy: " << rainy << " Sunny: " << sunny
                    << " Cloudy: " << cloudy << endl;
        }
        // 2 represents august
        // if august output number of rainy, cloudy, and sunny days for august
        else
        {
            augustRain = rainy;
            cout << "August Weather: Rainy: " << rainy << " Sunny: " << sunny
                    << " Cloudy: " << cloudy << endl;
        }
        
        //Determine which month had most rain
        if (julyRain > juneRain)
        {
            rainyJuly = true;
        }
        else 
        {
            rainyJune = true;
        }
        if (augustRain > julyRain)
        {
            rainyAugust = true;
            rainyJune = false;
            rainyJuly = false;
        }
        //reset rainy, sunny, and cloudy to 0 for each new month
        rainy = 0;
        sunny = 0;
        cloudy = 0;
    }
    
    cout << endl;
    //Output total rainy, sunny, and coudy days throughout summer
    cout << "Total Rainy: " << totalRain << " Total Sunny: " << totalSun
            << " Total Cloudy: " << totalCloud << endl;
    
    //Determine month with most rain
    cout << "Month with most rain: ";
    if (rainyJune)
    {
        cout << "June";
    }
    else if (rainyJuly)
    {
        cout << "July";
    }
    else
    {
        cout << "August";
    }
    cout << endl << endl;
}

void problem7()
{
    string inputName;
    const int NUM_NAMES = 20;
    string names[NUM_NAMES] = {"Collins, Bill", "Smith, Bart", "Allen, Jim",
                               "Griffin, Jim", "Stamey, Marty", "Rose, Geri", 
                               "Taylor, Terri", "Johnson, Jill",
                               "Allison, Jeff", "Looney, Joe", "Wolfe, Bill", 
                               "James, Jean", "Weaver, Jim", "Pore, Bob", 
                               "Rutherford, Greg", "Javens, Renee", 
                               "Harrison, Rose", "Setzer, Cathy",
                               "Pike, Gordon", "Holland, Beth" };
    
    //sort array
    sort(names, NUM_NAMES);
    //print array
    prntArray(names, NUM_NAMES, 5);
    //prompt user to enter a name from printed array
    cout << "Type in a name: ";
    cin.ignore();
    getline(cin, inputName);
    //Output location of name
    cout << "Name location : " << binarySearch(names, NUM_NAMES, inputName)
            << endl << endl;
    
}

//print array
void prntArray(string a[], int size, int perLine)
{
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " | ";
 
        if(i%perLine == (perLine -1))
        {
            cout << endl;
        }
    }
    cout << endl;
}

void sort(string names[], int size)
{
    //Sort array using bubble sort
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            //Sort with first letter of each string in array
            if(names[j].substr(0, 1) > names[j + 1].substr(0, 1))
            {
                swap(names[j], names[j + 1]);
            }
        }
    }
}


int binarySearch (string a[], int capacity, string val)
{
    int first = 0, //first element in array
        last = capacity - 1, //last element in array
        middle = 0, //middle of search
        position = -1; //position of string to be found
        bool found = false; //determines weather string is found

    while (!found && first <= last)

    {
        //determine midpoint of array
        middle = (first + last) / 2; 
        
        if (a[0] == val)
        {
            found = true;
            position = 0;
        }
        //determine if value is found at midpoint of array
        else if (a[middle] == val) 
        {
            found = true;
            position = middle;
        }
        //determine value is in lower half of array
        else if (a[middle].substr(0, 1) > val.substr(0, 1))
        {
            last = middle - 1;
        }
        //determine if value is in upper half of array
        else 
        {
            first = middle + 1;
        }
    }

    return position;
}