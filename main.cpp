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
 * ./werhauz -o temp.txt -h1 3 -h2 5 -s 10
 */
int main(int argc, char** argv)
{
    int i, j, len, operations = 0, Hashtable1NumOfEntries, Hashtable2NumOfEntries, BucketSize;
    char buf[100],buf2[100], *token, temp[10]; 
    
    for (i = 1; i < 7; i += 2)
    {
        //cout << "i = " << i << " " << argv[i] << " " << argv[i+1] << endl;
        if(strcmp(argv[i], "-o") == 0)  operations = i + 1;  
        else if (strcmp(argv[i], "-h1") == 0) Hashtable1NumOfEntries = atoi(argv[i+1]);
        else if (strcmp(argv[i], "-h2") == 0) Hashtable2NumOfEntries = atoi(argv[i+1]);
        else BucketSize = atoi(argv[i+1]);       
    }
    
    cout << "Please enter tarrif file" << endl;
    cin >> temp ;
    
    Hashtable *HashtableCaller = new Hashtable(Hashtable1NumOfEntries, BucketSize);      //Construct HashTable1 for caller info
    Hashtable *HashtableCallee = new Hashtable(Hashtable2NumOfEntries, BucketSize);      //Construct HashTable2 for callee info

    BinaryMaxHeap MaxHeap;
    //cout << "1  " << operations<< endl;
    int flag = 1;
    FILE *file;
    
    file = fopen (temp,"r");   
    char tarrif[5][3][4];
    if (file == NULL)   cout << "Unable to open file"; 
    else 
    {
        fgets(buf, sizeof(buf), file);
        //printf("%s", buf);

        for(i = 0; i < 5; i++)
        {
            fgets(buf, sizeof(buf), file);
            //printf("%s", buf);
            token = strtok(buf, "\t");
            for(j = 0; j < 3; j++)
            {
                //printf( "token = %s\n", token );
                strncpy(tarrif[i][j], token, 3);

                if(j != 2) token = strtok(NULL, "\t");
                else token = strtok(NULL, "(");
            }
        }        
        
        /*for(i = 0; i < 5; i++){
            for(j = 0; j < 3; j++) cout << tarrif[i][j] << "\t"; 
            printf( "\n");}*/
        
        fclose(file);
    }
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
        //cout << "!!!!!!!!!!!!" << endl;
        i = 0;
        if (operations == 0 || flag == 2){                 //If there is no file or the file has been read, continue with stdin
            if (strcmp(token,"bye") == 0) 
            {
                Hashtable *HashtableCaller = new Hashtable(Hashtable1NumOfEntries, BucketSize);      //Construct HashTable1 for caller info
                Hashtable *HashtableCallee = new Hashtable(Hashtable2NumOfEntries, BucketSize);      //Construct HashTable2 for callee info
            }
            cout << "44444444" << endl;
            fgets(buf, sizeof(buf), stdin);
        }
        else{                                   //Else there is a file that needs to be read
            fgets(buf, sizeof(buf), file);
            printf("%s", buf);
           // printf("%s", buf2);
            if (buf == NULL) {operations = -1; flag = 2;}            
            //strcpy(buf2, buf);           
        }
        len = strlen(buf);
        if (buf[len - 1] == '\n') buf[len -1] = '\0';   //Get rid of the new line
        token = strtok(buf, "  ");
        
        if (strcmp(token,"insert") == 0) i = 1;
        else if (strcmp(token,"delete") == 0) i = 2;
        else if (strcmp(token,"find") == 0) i = 3;
        else if (strcmp(token,"lookup") == 0) i = 4;
        else if (strcmp(token,"indist") == 0) i = 5;
        else if (strcmp(token,"topdest") == 0) i = 6;
        else if (strcmp(token,"top") == 0) i = 7;
        else if (strcmp(token,"bye") == 0) i = 8;
        else if (strcmp(token,"print") == 0) i = 9;
        else printf("Try again!\n");
        
        switch(i){
            case 1:                   //First case: syntax:insert cdr-record 
            {
               // len = len - 13;         //Find how many N1 N2 N3 N4... we have
               // len = len / 7;
                token = strtok(NULL, "");
                //cout << "token = "<< token << endl;
                char *temp_str = new char[strlen(token) + 1];
                strcpy(temp_str, token);
                char *temp_str2 = new char[strlen(token) + 1];
                strcpy(temp_str2, token);

                /*Insert caller into First Hashtable*/
                HashtableCaller->InsertIntoHashtable(token, 1); //1 is for caller
                
                MaxHeap.Insert(temp_str2, tarrif);
                //cout << "After insert caller" << endl;
                /*Insert callee into First Hashtable*/
                HashtableCallee->InsertIntoHashtable(temp_str, 2);   //2 is for callee 
                //cout << "After insert callee" << endl;
                             
                
                delete temp_str; 
                delete temp_str2; 
            break;}
            case 2:{               //Second case: syntax:delete caller cdr-id
                token = strtok(NULL, " ");
                char *cdrid = new char[strlen(token) + 1];
                strcpy(cdrid, token);
                //cout << "delete cdrid " << cdrid << endl;
                token = strtok(NULL, "");
                char *caller = new char[strlen(token) + 1];
                strcpy(caller, token);               
                
                //cout << "delete caller " << caller << endl;
                
                HashtableCaller->DeleteCDR(caller, cdrid);

                delete caller;
                delete cdrid;
            break;}
            case 3: {       //Third case: syntax: find caller [time1][year1] [time2][year2]
                token = strtok(NULL, " ");  
                int counter = -1;
                char *arr[5];
                //cout <<"here"<< endl;
                while (token != NULL)
                {
                    counter++;
                    arr[counter] = new char[strlen(token)];
                    strcpy(arr[counter], token);
                    
                    token = strtok(NULL, " ");
                }
                //for(int i = 0; i < counter; i++) cout << arr[i] << endl;
                HashtableCaller->FindCaller(arr, counter, 2);
                //cout <<"after find caller" << endl;
                for(int i = 0; i < counter; i++) delete arr[i];
                //cout <<"after delete caller" << endl;
            break;}
            case 4:{        //Fourth case: syntax: lookup callee [time1][year1] [time2][year2]
                token = strtok(NULL, " ");  
                int counter = -1;
                char *arr[5];
                while (token != NULL)
                {
                    counter++;
                    arr[counter] = new char[strlen(token)];
                    strcpy(arr[counter], token);                   
                    token = strtok(NULL, " ");
                }
                //for(int i = 0; i < counter; i++) cout << arr[i] << endl;
                HashtableCallee->FindCaller(arr, counter, 2);
                
                for(int i = 0; i < counter; i++) delete arr[i];
            break;}
            case 5:{     //Fifth case: syntax: indist caller1 caller2
                token = strtok(NULL, " ");
                char *caller1 = new char[strlen(token) + 1];
                strcpy(caller1, token);
                token = strtok(NULL, " ");
                char *caller2 = new char[strlen(token) + 1];
                strcpy(caller2, token);
                
                /*Search and store incoming - outgoing calls of caller1*/
                char **contacts1 = new char*[strlen(caller1) + 1];
                int counter1 = -1;   
                HashtableCaller->StoreContacts(caller1, contacts1, counter1, 3);
                HashtableCallee->StoreContacts(caller1, contacts1, counter1, 3);
                cout << "caller1 has been contacted by: " << endl;
                for(int i = 0; i <= counter1; i++) cout << contacts1[i] << endl;
                
                
                /*Search and store incoming - outgoing calls of caller2*/               
                char **contacts2 = new char*[strlen(caller2) + 1];
                int counter2 = -1;
                HashtableCaller->StoreContacts(caller2, contacts2, counter2, 3);                  
                //for(int i = 0; i <= counter1; i++) cout << contacts1[i] << endl;
                HashtableCallee->StoreContacts(caller2, contacts2, counter2, 3);
                cout << "caller2 has been contacted by: " << endl;
                for(int i = 0; i <= counter2; i++) cout << contacts2[i] << endl;
          
                               
                /*Check which contacts exist on both arrays*/
                for (int i = 0; i <= counter1; i++)
                {
                    //cout << contacts1[i]<< endl;
                    int found = 0;
                    for(int j = 0; j <= counter2; j++)
                    {           
                        //cout << contacts1[i]<< "    " << contacts2[j] << endl;
                        if (strcmp(contacts1[i], contacts2[j]) == 0)
                        {   
                            //cout <<"here" << endl;
                            found = 1;
                            break;
                        }
                    }
                    if (found == 0) strcpy(contacts1[i], "-");
                }
                cout << "Same contacts of caller1 and caller2: " << endl;
                for(int i = 0; i <= counter1; i++) if (strcmp(contacts1[i], "-") != 0 )cout << contacts1[i] << endl;
                
                //for(int i = 0; i <= counter1; i++)
                    //if(strcmp(contacts1[i], "-") != 0)
                int finalresults [counter1 + 1];
                for(int i = 0; i <= counter1; i++) finalresults[i] = 0;
                HashtableCaller->Indist( contacts1, counter1, finalresults);
                HashtableCallee->Indist( contacts1, counter1, finalresults);
                cout << "Results:   "  << endl;
                for(int i = 0; i <= counter1; i++)
                    if (finalresults[i] == 1)
                        cout << contacts1[i] << endl;
                //HashtableCallee->Indist(caller1, caller2);
                
                for (int i = 1; i <= counter1; i++){//cout << "i   "  << i << endl;
                    delete[] contacts1[i];}
        
                for (int i = 1; i <= counter2; i++){//cout << "i   "  << i << endl;
                    delete[] contacts2[i];}

                delete caller1;
                delete caller2;
                /*for (int i = 0 ; i < counter1 ; i++)
                    delete[] contacts1[i] ;
                delete[] contacts1 ;
                for (int i = 0 ; i < counter2 ; i++)
                    delete[] contacts2[i] ;
                delete[] contacts2 ;*/
                //for (int i = 0; i <= counter1; i++) delete tem[i];
                //for (int i = 0; i <= counter2; i++) delete contacts2[i];
            break;}
            case 6:{       //Sixth case: syntax:  topdest caller
                token = strtok(NULL, " ");
                char *caller = new char[strlen(token) + 1];
                strcpy(caller, token);
                cout << "caller " << caller << endl;
                
                /*Search and store outgoing calls of caller1*/
                char **contacts = new char*[strlen(caller) + 1];
                int counter = -1;   
                HashtableCaller->StoreContacts(caller, contacts, counter, 5);
                
                for(int i = 0; i <= counter; i++) cout << contacts[i] << endl;
                
                HashtableCaller->TopDest(contacts, counter);
                
                delete caller;
            break;}
            case 7:
                token = strtok(NULL, "");
            break;
            case 8:
                delete HashtableCaller;
                HashtableCaller = NULL;
                cout << "HashtableCaller has been deleted" << endl;
                delete HashtableCallee;
                HashtableCallee = NULL;
                cout << "HashtableCallee has been deleted" << endl;
            break;
            case 9:
                token = strtok(NULL, "");                
                if (strcmp(token, "hashtable1") == 0)
                    HashtableCaller->printTable();
                else
                    HashtableCallee->printTable();
                //cout << "\n\n\n" << endl;
                //MaxHeap.levelOrder();
            break;
        }
        //cout << "After switch" << endl;
        
        if (i == 8)
        {
            cout << "If you want to continue press 1, else press 0" << endl;
            cin >> flag;
            
        }
        
    }   
    cout << "after switch" << endl;
    if (HashtableCaller != NULL)
    {
        cout << "HashtableCaller delete" << endl;
        delete HashtableCaller;
        cout << "HashtableCaller has been deleted" << endl;
    }
    if (HashtableCallee != NULL)
    {
        cout << "HashtableCallee delete" << endl;
        delete HashtableCallee;
        cout << "HashtableCallee has been deleted" << endl;
    }
                
    return 0;
}

