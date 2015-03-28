/* 
 * File:   main.cpp
 * Author: Mike
 *
 * Created on March 26, 2015, 8:57 PM
 */

#include <cstdlib>
#include <iostream>
#include <cstddef>
#include <iomanip>
#include <cctype>
#include <ctime>

using namespace std;

void menu();
int numOfWords(char*);
float avgNumOfLett(char[], int);
void problem1();
int numOfCons(char*);
int numOfVowels(char*);
void prob2Menu();
void problem2();
bool checkLength(char*, int);
bool checkUpper(char*);
bool checkLower(char*);
bool checkDigit(char*);
void problem3();
void problem4();
void problem5();
void problem6();
void problem7();
void problem8();
void problem9();
void problem10();

int main(int argc, char** argv) {
    
    srand(time(0));
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
            case 7:
                problem7();
            case 8:
                problem8();
            case 9:
                problem9();
            case 10:
                problem10();
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
    cout << "Enter 1 for problem 6" << endl;
    cout << "Enter 2 for problem 7" << endl;
    cout << "Enter 3 for problem 8" << endl;
    cout << "Enter 4 for problem 9" << endl;
    cout << "Enter 5 for problem 10" << endl;
}

////////////////////////////////////
//Problem 1////////////////////////
///////////////////////////////////
//10.4
void problem1()
{
    int wordCount;
    char cstring[71];
    //Prompt user to enter string
    cout << "Enter a string with 70 characters or less. ";
    cin.ignore();
    cin.getline(cstring, 71);
   
    wordCount = numOfWords(cstring);
    cout << "Number of words: " << wordCount << endl;
    cout << setprecision(1) << fixed << "Average number of letters per word: "
            << avgNumOfLett(cstring, wordCount);
    
    cout << endl << endl;
}

int numOfWords(char* cstring)
{
    //declare word counter
    int wordCount = 0; 
    //detect letter in string
    int letterDetect = 0;
    
    for (int i = 0; cstring[i] != '\0'; i++)
    {
        //detect if there is not a space
        if (isalnum(cstring[i]))
        {
            letterDetect++;
            
            //only count word for first letter
            if (letterDetect < 2)
            {
               //count number of words
               wordCount++; 
            }
        }
        //if there is a space and word has already been detected then count word
        if (isspace(cstring[i]))
        {
            //reset letters to 0
            letterDetect = 0;
        }
    }
    
    return wordCount;
}

float avgNumOfLett(char cstring[], int words)
{
    //declare letter counter
    int letters = 0;
    //declare average number of letters
    float avgNumOfLett;
    
    for (int i = 0; cstring[i] != '\0'; i++)
    {
        //determine if character is a letter
        if (isalpha(cstring[i]))
        {
            //count number of letters
            letters++;
        }
    }
    
    avgNumOfLett = static_cast<float>(letters)/words;
    
    return avgNumOfLett;
}

////////////////////////////////////
//Problem 2////////////////////////
///////////////////////////////////
//10.6
void problem2()
{
    string input;
    char cstring[71];
    //declare total for consonants and vowels
    int total;
    //declare exit for menu
    bool exit = false;
    //declare problem for menu
    char problem;
    bool enterString = true;
    
    do 
    {
        //prompt user to enter string
        if (enterString)
        {
            cout << "Enter a string with 70 characters or less: ";
            cin.ignore();
            cin.getline(cstring, 71);
            //total number of consonants and vowels
            total = numOfCons(cstring) + numOfVowels(cstring);
        }
        cout << endl;
        enterString = false;
        
        //Prompts user to enter a problem
        prob2Menu();
        cin >> problem;
        cout << endl;
        
        switch (problem)
        {
            case 'a': 
                //output number of vowels
                cout << "Number of vowels: " << numOfVowels(cstring) << endl;
                break;
            case 'b':
                //output number of consonants
                cout << "Number of consonants: " << numOfCons(cstring) << endl;
                break;
            case 'c':
                //output total number of consonants and vowels
                cout << "Number of consonants and vowels: " << total << endl;
                break;
            case 'd':
                //set enter string to true to enter another string
                enterString = true;
                break;
            case 'e':
                //set exit to true to exit 
                exit = true;
                break;
            default :
                cout << "Invalid" << endl;     
        }
        
    } while (!exit);
    
    cout << endl << endl;
}

void prob2Menu()
{
    cout << "Enter a to count number of vowels in string" << endl;
    cout << "Enter b to count number of consonants in string" << endl;
    cout << "Enter c to count both vowels and consonants in string" << endl;
    cout << "Enter d to enter another string" << endl;
    cout << "Enter e to exit" << endl;
}

int numOfCons(char* cstring)
{
    const int SIZE = 5;
    //array of vowels
    char vowels[SIZE] = {'a', 'e', 'i', 'o', 'u'};
    //declare consonants and set to false
    bool cons = false;
    //declare count for number of consonants
    int count = 0;
    
    for(int i = 0; cstring[i] != '\0'; i++)
    {
        //set consonants to true if character is a letter
        //else set to false
        if (isalpha(cstring[i]))
        {
            cons = true;
        }
        else
        {
            cons = false;
        }
        //second loop to compare characters to vowels
        for (int j = 0; j < SIZE; j++)
        {
            //if a character from cstring is equal to a vowel
            //set consonant to false
            if (tolower(cstring[i]) == vowels[j])
            { 
               cons = false; 
            }
        }
        //if consonant is true 
        if (cons)
        {
            count++;
        }
    }
    return count;
}

int numOfVowels(char* cstring)
{
    const int SIZE = 5;
    //array of vowels
    char vowels[SIZE] = {'a', 'e', 'i', 'o', 'u'};
    //declare count for number of vowels
    int count = 0;
    
    for(int i = 0; cstring[i] != '\0'; i++)
    {
        //loop to compare to vowels
        for (int j = 0; j < SIZE; j++)
        {
            //if a character from cstring is equal to a vowel
            //add to vowel count
            if (tolower(cstring[i]) == vowels[j])
            { 
               count++; 
            }
        }
    }
    return count;
}

////////////////////////////////////
//Problem 3////////////////////////
///////////////////////////////////
//10.12
void problem3()
{   
    //declare password array
    char password[30];
    //declare valid boolean for password
    bool valid;
    
    //set criteria for password
    cout << "Must contain at least 6 characters " << endl;
    cout << "Must contain at least one uppercase and lowercase letter " << endl;
    cout << "Must contain at least one digit " << endl;
    
    do
    {
        valid = true;
        
        //prompt user to enter password
        cout << "Enter password: " << endl;
        cin.getline(password, 30);
        
        cout << endl;
        //if password is too short output message
        if (!checkLength(password, 6))
        {
            cout << "Must be at least 6 characters. " << endl;
            valid = false;
        }
    
        //if password does not contain an uppercase letter output message
        if (!checkUpper(password))
        {
            cout << "Must contain at least one uppercase letter. " << endl;
            valid = false;
        }
    
        //if password does not contain a lowercase letter output message
        if (!checkLower(password))
        {
            cout << "Must contain at least one lowercase letter. " << endl;
            valid = false;
        }
    
        //if password does not contain a digit output message
        if (!checkDigit(password))
        {
            cout << "Must contain at least one digit. " << endl;
            valid = false;
        }
        
        cout << endl;
        
    } while (!valid);
    
}

bool checkLength(char* password, int length)
{
    //declare count for number of characters
    int count = 0;
    
    //count number of characters in password
    for (int i = 0; password[i] != '\0'; i++)
    {
            count++;
    }
    
    //if count is less than required length return false
    if (count < length)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool checkUpper(char* password)
{
    //check for any uppercase letters in password
    for (int i = 0; password[i] != '\0'; i++)
    {
        //if uppercase letter is found return true
        if (isupper(password[i]))
        {
            return true;
        }
    }
    
    return false;
}
bool checkLower(char* password)
{
    //check for any lowercase letters in password
    for (int i = 0; password[i] != '\0'; i++)
    {
        //if lowercase letter is found return true
        if (islower(password[i]))
        {
            return true;
        }
    }
    
    return false;
}

bool checkDigit(char* password)
{
    //check for any digits in password
    for (int i = 0; password[i] != '\0'; i++)
    {
        //if digit is found return true
        if (isdigit(password[i]))
        {
            return true;
        }
    }
    
    return false;
}

////////////////////////////////////
//Problem 4////////////////////////
///////////////////////////////////
//11.9
void problem4()
{
    
}

void problem5()
{
    
}

void problem6()
{
    
}

void problem7()
{
    
}

void problem8()
{
    
}

void problem9()
{
    
}

void problem10()
{
    
}