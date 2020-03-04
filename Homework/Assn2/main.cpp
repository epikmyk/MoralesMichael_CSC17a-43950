/* 
 * File:   main.cpp
 * Author: Mike
 *...
 * Created on March 17, 2015, 11:18 AM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

int* fillArry(int);
void prntArry(int*, int, int);
void sortArry(int*, int);
float mean(int*, int);
float median(int*, int);
int* mode(int*, int&);

int main(int argc, char** argv) {
    
    srand(time(0));
    int size = 20;
    int* array = fillArry(size);
    //sort array
    sortArry(array, size);
    //print Array
    prntArry(array, size, 5);
    
    //output mean
    cout << "The mean is: " << setprecision(1) << fixed 
            << mean(array, size) << endl;
    //output median
    cout << "The median is: " << median(array, size) << endl;
    
    //mode array
    int* modeArray = mode(array, size);
    //output number of modes
    cout << "The number of modes are: " << modeArray[0] << endl;
    //output frequencies
    cout << "The number of frequencies: " << modeArray[1] << endl;
    //print mode array
    prntArry(modeArray, size, size);
    
  
    delete []array;
    

    return 0;
}

int* fillArry(int size)
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

void sortArry(int* a, int size)
{   
    //sort array
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            //swap if a[j] greater than a[j + 1]
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void prntArry (int* a, int size, int perLine)
{       
    //print array
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
        //number of elements in array printed perline
        if(i % perLine == (perLine - 1))
        {
            cout << endl;
        }
    }
    cout << endl;
}

float mean(int* a, int size)
{
    float mean = 0;
    
    //get sum of all numbers in array
    for (int i = 0; i <= size; i++)
    {
        mean += a[i];
    }
    //divide by size to get mean
    mean /= size;
    
    return mean;
}

float median(int* a, int size)
{
    float median;
    
    //find median of array
    //if number of elements in array is even get average of two middle numbers
    if (size % 2 == 0)
    {
        median = static_cast<float>(a[size / 2] + a[size / 2 - 1]) / 2;
    }
    else
    {
        median = a[size / 2];
    }
    
    return median;
}

int* mode(int *a, int &size)
{
    int numOfModes = 0;
    int* modeArray = new int[numOfModes + 2];
    //number of current frequencies
    int count = 1;
    //number of most frequencies
    int prevCount = 0;
   
    for (int i = 0; i < size; i++)
    {
        //count number of times an element is in array
        if (a[i] == a[i + 1])
        {
            count++;
        }
        else
        { 
            //if element is not equal to next element in array
            //determine number of modes by counting amount of highest counts
            if (count == prevCount)
            {
                numOfModes++;
                //assign number of modes to  mode array
                modeArray[0] = numOfModes;
                //assign number of frequencies to mode array
                modeArray[1] = prevCount;
                //assign modes to mode array
                modeArray[1 + numOfModes] = a[i];
            }
            //determine if current count is greater than previous highest count
            if(count > prevCount)
            {
                prevCount = count; 
                //reset number of modes
                numOfModes = 1;
                //assign number of modes to  mode array
                modeArray[0] = numOfModes;
                //assign number of frequencies to mode array
                modeArray[1] = prevCount;
                //assign modes to mode array
                modeArray[1 + numOfModes] = a[i];
            }   
            //reset count
            count = 1; 
        }      
    }
    //size for mode array
    size = numOfModes + 2;
    
    return modeArray;
}