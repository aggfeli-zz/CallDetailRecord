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
    //cout << "!!!!!!!!! = "<< hash << endl;
    return hash;
}



void Hashtable::InsertIntoHashtable(char *temp, int flag)
{    
    char *token, *number;
    
    int size = strlen(temp) + 1 - 14;
    char rest_info[size];
    //cout << "wholeeee " << temp <<  endl;
    if (flag == 1) //Flag for caller
    {
        token = strtok(temp, ";");
        strcpy(rest_info, token);
        token = strtok(NULL, ";");
        number = new char[strlen(token)];
        strcpy(number, token);
        //cout << "caller = "<< cdr_id << endl; 
        strcat(rest_info, ";");
        token = strtok(NULL, "");
        strcat(rest_info, token);
        //cout << "rest_info = "<< rest_info << endl; 
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
        //cout << "callee = "<< token << endl;
        strcat(rest_info, ";");
        token = strtok(NULL, "");
        //cout << "rest = "<< token << endl; 
        strcat(rest_info, token);
        
        
        //cout << "rest_info = "<< rest_info << endl; 
    }
    //cout << "!!!!!!!!!!!!!!!!!!!! = " << number << endl;
    int index = HashFunction(number);
    
    //cout << "index = " << index << endl;
    int found = array[index].SearchBucket(number, NULL, 0, NULL, index);
    array[index].insertPoint(number, rest_info, found);
    delete []number;
}


void Hashtable::printTable()
{
    //cout << length;
    //cout << "\nHash Table:\n";   
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
    //cout << "index = " << index << endl;
    int found = array[index].SearchBucket(caller, cdrid, 1, NULL, index);
    if (found == 1) cout << "CDR deleted successfully" << endl;
    else cout << "CDR not found" << endl;
}

void Hashtable::FindCaller(char *arr[], int counter, int flag)
{
    //for(int i = 0; i < counter; i++) cout << arr[i] << endl;
    int index = HashFunction(arr[0]);
    //cout << "index = " << index << endl;
    int found = array[index].SearchBucket(arr[0], NULL, 2, arr, counter);
    if (found == 1) cout << "CDR found" << endl;
    else cout << "CDR not found" << endl;
    
}

void Hashtable::Indist(char *contacts[], int &counter, int finalresults[])//char *caller1, char *caller2)
{
    /*char *callee1[strlen(caller1) + 1],  *callee2[strlen(caller1) + 1];
    
    /*Search who has been called by caller 1*
    int index = HashFunction(caller1) , counter1 = -1;
    cout << "index = " << index << endl;
    int found = array[index].SearchBucket(caller1, NULL, 3, callee1, counter1);
    cout << "caller1 has been contacted by: " << endl;
    for(int i = 0; i <= counter1; i++) cout << callee1[i] << endl;
    
    /*Search who has been called by caller 2 *
    index = HashFunction(caller2) ; int counter2 = -1;
    cout << "index = " << index << endl;
    found = array[index].SearchBucket(caller2, NULL, 3, callee2, counter2);
    cout << "caller2 has been contacted by: " << endl;
    for(int i = 0; i <= counter2; i++) cout << callee2[i] << endl;
    
    /*Search callee arrays to find which numbers exist in both arrays*
    for (int i = 0; i <= counter1; i++)
    {
        int found = 0;
        for(int j = 0; j <= counter2; j++)
        {           
            if (strcmp(callee1[i], callee2[j]) == 0)
            {   
                found = 1;
                break;
            }
        }
        if (found == 0) strcpy(callee1[i], "-");
    }
    cout << "counter1 " << counter1 << endl;
    cout << "counter2 " << counter2 << endl;
    for(int i = 0; i <= counter1; i++) cout << callee1[i] << endl;*/
    
    /*Search contacts array to find which numbers haven't connected*/
    /*Final result array -> 1 : contact complies conditions*/
    /*Final result array -> 0 : contact needs to be investigated*/
    /*Final result array -> 2 : contact has spoken at least with one more, doesn't comply conditions*/
    int counter2 = counter;
    for (int i = 0; i <= counter; i++)
    {       
        //cout << "i = " << i << endl;
        if(strcmp(contacts[i], "-") != 0 && finalresults[i] != 2)
        {
            //cout << "contacts of:  " << contacts[i] << endl;  
            int index = HashFunction(contacts[i]) ;
            //cout << "index = " << index << endl;
            int found = array[index].SearchBucket(contacts[i], NULL, 4, contacts, counter2);
            //cout << "found = " << found<< endl;
            
            if (found == 0 && finalresults[i] != 1) //Number hasn't contacted rest of numbers
            {                    
                finalresults[i] = 1; //To show that number comply wanted conditions
                //cout << "store  " << contacts[i] << endl;     
            }
            if(found == 1)
            {
               //cout << "finalresults = " << finalresults[i] << "   contact "<< contacts[i]<< endl;
                //cout << "contact that's gonna be deleted    " <<  contacts[i]<< endl;
                finalresults[i] = 2;  
            }
            
            
          /*  if (found == 0) 
            {
                for(int j = 0; j <= finalcount; j++)
                {
                    cout << "finalresults = " << finalresults[j] << "   contact "<< contacts[i]<< endl;
                    if(strcmp(finalresults[j], contacts[i]) == 0) //Contact already exists in final results
                    {
                        cout << "22222222222" << endl;
                        found = 2;
                        break;
                    }
                }
                cout << "found = " << found<< endl;
                if(found == 0)
                {
                    finalcount++;
                    finalresults[finalcount] = new char[strlen(contacts[i]) + 1];
                    strcpy(finalresults[finalcount] , contacts[i]);
                    cout << "store  " << contacts[i] << endl; 
                }
            }
            if(found == 1)
            {
                for(int j = 0; j <= finalcount; j++)
                {
                    cout << "finalresults = " << finalresults[j] << "   contact "<< contacts[i]<< endl;
                    if(strcmp(finalresults[j], contacts[i]) == 0)
                    {
                        cout << "contact that's gonna be deleted    " <<  finalresults[j] << endl;
                        strcpy(finalresults[j] , "-");
                        break;
                    }
                }
            }*/
        }
        if(i == counter) return;
    }       
    cout << "Not found" << endl;
}

void Hashtable::StoreContacts(char *caller, char *contacts[], int &counter, int flag)
{
    /*Search who has been called by caller*/
    int index = HashFunction(caller);
    //cout << "index = " << index << endl;
    int found = array[index].SearchBucket(caller, NULL, flag, contacts, counter);   
}

void Hashtable::TopDest(char *contacts[], int counter)
{    
    //cout <<"$$$$$$$$$$      " << counter << endl;
    int CountryCode[counter];
    for(int i = 0; i <= counter; i++) CountryCode[i] = 1;
    char Codes[counter][4], *token;
    for(int i = 0; i <= counter; i++)
    {
        char *temp = new char[strlen(contacts[i]) + 1];
                    //cout << "2" << endl;
        strcpy(temp, contacts[i]);
                    //cout << "3" << temp << endl;
        token = strtok(temp, ";"); 
                    //cout << "4" << endl;
        token = strtok(NULL, ";"); // This is callee
        
        token = strtok(token, "-");
        cout << "code   " << token << endl;
        strcpy((Codes[i]), token);
        delete temp;
    }
    
    for(int i = 0; i <= counter; i++)
    {
        if(strcmp(Codes[i],"-") != 0)
        {
            for(int j = i+1; j <= counter; j++)
            {
                if(strcmp(Codes[i], Codes[j]) == 0)
                {
                    CountryCode[i]++;
                    strcpy(Codes[j],"-");
                }
            }
        }
    }
    
    int num;
    char *temp;
    for (int i = 0; i <= counter; ++i)
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
                
                temp = new char[strlen(contacts[i]) + 1];
                strcpy(temp , contacts[i]);
                strcpy(contacts[i] , contacts[j]);
                strcpy(contacts[j] , temp);    
                delete temp;
            }
        }
    }
    
    //for (int i = 0; i <= counter; ++i)
        //cout << CountryCode[i] << "     " << Codes[i] << endl;
    
    int i = 0;
    while ( i <= counter)
    {
        if(CountryCode[i] == CountryCode[0])
            cout << CountryCode[i] << "     "  << Codes[i] << endl;
        else break;
        i++;
    }
}
