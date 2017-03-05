/* 
 * File:   main.cpp
 * Author: angelique
 *
 * Created on February 28, 2017, 9:25 PM
 */

#include <cstdlib>
#include "Hashtable.h"
#include "BinaryMaxHeap.h"
#include<fstream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    int i, j, len, operations = 0, Hashtable1NumOfEntries, Hashtable2NumOfEntries, BucketSize;
    char buf[100], *token; 
    
    for (i = 1; i < 7; i += 2)
    {
        //cout << "i = " << i << " " << argv[i] << " " << argv[i+1] << endl;
        if(strcmp(argv[i], "-o") == 0)  operations = i + 1;  
        else if (strcmp(argv[i], "-h1") == 0) Hashtable1NumOfEntries = atoi(argv[i+1]);
        else if (strcmp(argv[i], "-h2") == 0) Hashtable2NumOfEntries = atoi(argv[i+1]);
        else BucketSize = atoi(argv[i+1]);       
    }
    
    Hashtable HashtableCaller(Hashtable1NumOfEntries, BucketSize);      //Construct HashTable1 for caller info
    Hashtable HashtableCallee(Hashtable2NumOfEntries, BucketSize);      //Construct HashTable2 for callee info
    
   // BinaryMaxHeap MaxHeap;
    //cout << "1  " << operations<< endl;
    int flag = 1;
    FILE *file;
    
    if (operations != 0)    //If there is a file open it
    {      
        //cout << "2" << endl;
        file = fopen (argv[operations],"r");       
        if (file == NULL) 
        {           
            cout << "Unable to open file"; 
            operations = -1;
        }
        //cout << "3" << endl;
    }
    
    while(flag)
    {
        //cout << "4" << endl;
        i = 0;
        if (operations == 0){                 //If there is no file or the file has been read, continue with stdin
            if (strcmp(token,"bye") == 0) 
            {
                Hashtable HashtableCaller(Hashtable1NumOfEntries, BucketSize);      //Construct HashTable1 for caller info
                Hashtable HashtableCallee(Hashtable2NumOfEntries, BucketSize); 
            }        
            fgets(buf, sizeof(buf), stdin);
        }
        else{                                   //Else there is a file that needs to be read
            fgets(buf, sizeof(buf), file);
            printf("%s", buf);
            if (buf == NULL) operations = -1;
        }
        len = strlen(buf);
        if (buf[len - 1] == '\n') buf[len -1] = '\0';   //Get rid of the new line
        token = strtok(buf, "  ");
        
        if (strcmp(token,"insert") == 0) i = 1;
        else if (strcmp(token,"delete") == 0) i = 2;
        else if (strcmp(token,"find") == 0) i = 3;
        else if (strcmp(token,"lookup") == 0) i = 4;
        else if (strcmp(token,"indist1") == 0) i = 5;
        else if (strcmp(token,"topdest") == 0) i = 6;
        else if (strcmp(token,"top") == 0) i = 7;
        else if (strcmp(token,"bye") == 0) i = 8;
        else printf("Try again!\n");
        
        switch(i){
            case 1:                   //First case: syntax:insert cdr-record 
               // len = len - 13;         //Find how many N1 N2 N3 N4... we have
               // len = len / 7;
                token = strtok(NULL, "");
                //cout << "token = "<< token << endl;
                char *temp_str = new char[strlen(token) + 1];
                strcpy(temp_str, token);

                /*Insert caller into First Hashtable*/
                HashtableCaller.InsertIntoHashtable(token, 1); //1 is for caller
                //cout << "After insert caller" << endl;
                /*Insert callee into First Hashtable*/
                HashtableCallee.InsertIntoHashtable(temp_str, 2);   //2 is for callee 
                //cout << "After insert callee" << endl;
                
                
                free(temp_str);
                
            break;
            
            
        }
        //cout << "After switch" << endl;
        
        if (i == 8)
        {
            cout << "If you want to continue press 1, else press 0" << endl;
            cin >> flag;
        }
        
    }
    
    HashtableCallee.printTable();
    HashtableCaller.printTable();
    
    
    //cout << h.extractMax() << " ";
    //cout << h.getMax() << " ";
    //h.decreaseKey(2, 1);
    //cout << h.getMax();
    
    
    
    return 0;
}

