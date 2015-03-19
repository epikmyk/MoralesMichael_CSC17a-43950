/* 
 * File:   main.cpp
 * Author: mikemorales
 *
 * Created on March 18, 2015, 2:06 PM
 */

#include <cstdlib>
#include <iostream>
#include <cstddef>
#include <ctime>

using namespace std;

void menu();
int *fillArray(int);
void printArray(int*, int, int);
void printArray(int*[], int, int);
void sortArray(int*, int);
int avg(int*, int);
void revSort(int*, int);
void revSort(int*[], int);
void problem1();
void problem2();
void problem3();
void problem4();
int* fillArryRnd(int);
void problem5();

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
}

////////////////////////////////////
//Problem 1////////////////////////
///////////////////////////////////
//9.1
void problem1()
{
    int size = 50;
    int* array = fillArryRnd(size);
    //print array
    printArray(array, size, 10);
    
    cout << endl << endl;
}

int* fillArryRnd(int size)
{
    //declare and allocate array
    int* a = new int[size];
    //fill array with random numbers
    for (int i = 0; i < size; i++)
    {
        a[i] = rand()%9;
    }
    
    return a;
}

////////////////////////////////////
//Problem 2////////////////////////
///////////////////////////////////
//9.2
void problem2()
{
    int amount;
    int scores;
    
    //prompt user to enter test score amount
    cout << "How many test scores do you want to enter? " << endl;
    cin >> amount;
    //prompt user to enter test scores
    cout << "Enter test scores: " << endl;
    //call fill array function to fill with test score
    int* testScores = fillArray(amount);
    //sort array
    sortArray(testScores, amount);
    //print array and output test scores
    cout << "Test Scores: "  << endl;
    printArray(testScores, amount, 10);
    //the average from all test scores
    cout << "Average score: " << endl 
            << avg(testScores, amount);
    
    cout << endl << endl;
}

//fill array with values entered from user
int* fillArray(int amount)
{
    int* a = new int[amount];
    int input;
    
    for (int i = 0; i < amount; i++)
    {
        cin >> input;
        a[i] = input;
    }
    return a;          
}

//sort array
void sortArray(int* a, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if(a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

//print array
void printArray(int* a, int size, int perLine)
{
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
        
        if (i % perLine == (perLine - 1))
        {
            cout << endl;
        }
    }   
}

//get average
int avg(int* a, int size)
{
    //declare sum
    int sum = 0;
    //declare average
    int average;
    
    //get sum of all numbers in array
    for(int i = 0; i < size; i++)
    {
        sum += a[i];
    }
    
    //calculate average
    average = sum / size;
    
    return average;
}

////////////////////////////////////
//Problem 3////////////////////////
///////////////////////////////////
//9.6
void problem3()
{
    
    int num_donations;
    
    //prompt user to enter number of donations
    cout << "How many donations do you want to enter? " << endl;
    cin >> num_donations;
    //prompt user to enter donation amounts
    cout << "Enter donation amounts: " << endl;
    //call fill array function to fill with donations
    int* donations = fillArray(num_donations);
    //sort array
    sortArray(donations, num_donations);
    //print array and output donation amounts
    cout << "Donation amounts: "  << endl;
    printArray(donations, num_donations, 10);

    cout << endl << endl;
}

////////////////////////////////////
//Problem 4////////////////////////
///////////////////////////////////
//9.7
void problem4()
{
    int num_donations;
    
    //prompt user to enter number of donations
    cout << "How many donations do you want to enter? " << endl;
    cin >> num_donations;
    //prompt user to enter donation amounts
    cout << "Enter donation amounts: " << endl;
    //call fill array function to fill with donations
    int* donations = fillArray(num_donations);
    //sort array
    revSort(donations, num_donations);
    //print array and output donation amounts
    cout << "Donation amounts: "  << endl;
    printArray(donations, num_donations, 10);

    cout << endl << endl;
}

//sort array in reverse order
void revSort(int* a, int size)
{
    for (int i = size; i > 0; i--)
    {
        for (int j = size; j > 0; j--)
        {
            if(a[j - 1] < a[j])
            {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }
}

////////////////////////////////////
//Problem 5////////////////////////
///////////////////////////////////
//9.10
void problem5()
{
    const int SIZE = 10;
    
    //original array
    int array[10] = {1, 22, 33, 47, 12, 11, 76, 63, 99, 55};
    
    //array of pointers
    int* arrPtr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    //copy array
    for (int i = 0; i < SIZE; i++)
    {
        arrPtr[i] = &array[i];
    }
    
    //reverse array pointer
    revSort(arrPtr, SIZE);
    
    //print array pointer
    printArray(arrPtr, SIZE, 10);
}

//print array pointer
void printArray(int* a[], int size, int perLine)
{
    for (int i = 0; i < size; i++)
    {
        cout << *(a[i]) << " ";
        
        if (i % perLine == (perLine - 1))
        {
            cout << endl;
        }
    }   
}

//sort array in reverse order
void revSort(int* a[], int size)
{
    int* temp;
    for (int i = size; i > 0; i--)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if(*(a[j - 1]) < *(a[j]))
            {
                temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }
}

