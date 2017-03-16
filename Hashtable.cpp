/* 
 * File:   Hashtable.cpp
 * Author: angelique
 * 
 * Created on February 28, 2017, 10:06 PM
 */

#include "Hashtable.h"
#include <math.h>


Hashtable::Hashtable(int TableSize, int BucketSize) //Hashtable Constructor
{   
    length = TableSize;   //Length is the size of the HashTable array. 
    array = new LinkedList[ length ];
    bucketsize = BucketSize;
}

Hashtable::Hashtable(const Hashtable& orig) {
}

Hashtable::~Hashtable() 
{
    cout << "\n~Hashtable\n";
    delete [] array;
}

int Hashtable::HashFunction(char *token)  
{
    int hash = 0;
    for(int i = strlen(token) -1; i >= 0; i--)
    {
        hash = (token[i] + 128 * hash) % length;
    }
    return hash;
}



void Hashtable::InsertIntoHashtable(char *temp, int flag)
{    
    char *token, *number;
    
    int size = strlen(temp) + 1 - 14;
    char rest_info[size];
    if (flag == 1) //Flag for caller
    {
        token = strtok(temp, ";");
        strcpy(rest_info, token);
        token = strtok(NULL, ";");
        number = new char[strlen(token)];
        strcpy(number, token); 
        strcat(rest_info, ";");
        token = strtok(NULL, "");
        strcat(rest_info, token); 
    }
    else          //Flag == 2 for callee
    {
        token = strtok(temp, ";");
        strcpy(rest_info, token);
        strcat(rest_info, ";");
        token = strtok(NULL, ";");
        
        strcat(rest_info, token);
        token = strtok(NULL, ";");
        number = new char[strlen(token)];
        strcpy(number, token);

        strcat(rest_info, ";");
        token = strtok(NULL, "");
 
        strcat(rest_info, token);
 
    }

    int index = HashFunction(number);

    int found = array[index].SearchBucket(number, NULL, 0, NULL, index);
    array[index].insertPoint(number, rest_info, found);
    delete []number;
}


void Hashtable::printTable()
{
    //cout << length;
    cout << "\nHash Table:\n";   
    for (int i = 0; i < length; i++)
    {
        cout << "\nBucket " << i << ": ";
        array[i].printList();
    }
}

int Hashtable::getLength()
{
    return length;
}


void Hashtable::DeleteCDR(char *caller, char *cdrid)
{
    int index = HashFunction(caller);
    int found = array[index].SearchBucket(caller, cdrid, 1, NULL, index);
    if (found == 1) cout << "CDR deleted successfully" << endl;
    else cout << "DError" << endl;
}

void Hashtable::FindCaller(char *arr[], int counter, int flag)
{
    int index = HashFunction(arr[0]);
    int found = array[index].SearchBucket(arr[0], NULL, 2, arr, counter);
    if(found != 1) cout << "No CDRs found" << endl;
}

void Hashtable::Indist(char *contacts[], int &counter, int finalresults[])//char *caller1, char *caller2)
{    
    /*Search contacts array to find which numbers haven't connected*/
    /*Final result array -> 1 : contact complies conditions*/
    /*Final result array -> 0 : contact needs to be investigated*/
    /*Final result array -> 2 : contact has spoken at least with one more, doesn't comply conditions*/
    int counter2 = counter;
    for (int i = 0; i <= counter; i++)
    {       
        if(strcmp(contacts[i], "-") != 0 && finalresults[i] != 2)
        { 
            int index = HashFunction(contacts[i]) ;
            int found = array[index].SearchBucket(contacts[i], NULL, 4, contacts, counter2);

            if (found == 0 && finalresults[i] != 1) //Number hasn't contacted rest of numbers
            {                    
                finalresults[i] = 1; //To show that number comply wanted conditions    
            }
            if(found == 1)
            {
                finalresults[i] = 2;  
            }      
        }
        if(i == counter) return;
    }       
    cout << "Not found" << endl;
}

void Hashtable::StoreContacts(char *caller, char *contacts[], int &counter, int flag)
{
    /*Search who has been called by caller*/
    int index = HashFunction(caller);
    int found = array[index].SearchBucket(caller, NULL, flag, contacts, counter);   
}

void Hashtable::TopDest(char *contacts[], int counter)
{    
    int CountryCode[counter];
    for(int i = 0; i <= counter; i++) CountryCode[i] = 1;
    char Codes[counter][4], *token;
    for(int i = 0; i <= counter; i++)
    {
        char *temp = new char[strlen(contacts[i]) + 1];
        strcpy(temp, contacts[i]);
        token = strtok(temp, ";"); 
        token = strtok(NULL, ";"); // This is callee      
        token = strtok(token, "-"); //Get code of country that caller has contacted
        strcpy((Codes[i]), token);  //Store code
        delete temp;
    }
    
    for(int i = 0; i <= counter; i++) { CountryCode[i] = 1;}
    
    for(int i = 0; i <= counter; i++)
    {
        if(strcmp(Codes[i],"-") != 0) 
        {
            for(int j = i+1; j <= counter; j++) //Count how many times a code exists in array
            {
                if(strcmp(Codes[i], Codes[j]) == 0) //If code exists multiple times
                {
                    CountryCode[i]++;               //Increase number of times that code exists
                    strcpy(Codes[j],"-");           //Delete certain code that exists multiple times in order to count it only once
                }
            }
        }
    }
    //for (int i = 0; i <= counter; ++i)
        //cout << CountryCode[i] << "     " << Codes[i] << endl;
    
    int num;
    char *temp;
    for (int i = 0; i <= counter; ++i)              //Sort arrays of codes and number of times that codes exist(ascending order)
    {
        for (int j = i + 1; j <= counter; ++j)
        {
            if ( CountryCode[i] <  CountryCode[j])
            {
                num = CountryCode[i];
                CountryCode[i] = CountryCode[j];
                CountryCode[j] = num;
                
                temp = new char[strlen(Codes[i]) + 1];
                strcpy(temp , Codes[i]);
                strcpy(Codes[i] , Codes[j]);
                strcpy(Codes[j] , temp);    
                delete temp;               
            }
        }
    }
    
    
    int i = 0;
    while ( i <= counter)
    {
        if(CountryCode[i] == CountryCode[0])       //Print only the country codes that caller has contacted the most 
            cout << "Country code: " << Codes[i]  << "  , Calls made:  "  << CountryCode[i]<< endl;
        else break;
        i++;
    }
    if(i == 0) cout << "No calls found" << endl;
}
