//
//  main.c
//  ListApp
//
//  Created by Adam Rigely on 02.07.24.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "sqlite3.h"

void readList(void);
void writeList(void);
void createList(void);
void removeItem(void);
void clrBuff(void);

int main(int argc, char const *argv[])
{
    
    sqlite3 *db;
    char *errMsg;
    int rc = sqlite3_open("db.db", &db);
    const char *createTable;
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Problem encountered while attempting to open the database: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    else
    {
        fprintf(stdout, "ALL GOOD, the DB has been successfully opened. \n");
    }
    
    createTable = "CREATE TABLE IF NOT EXISTS itemList (itemID INTEGER PRIMARY KEY, itemDesc TEXT NOT NULL);";
    
    rc = sqlite3_exec(db, createTable, 0, 0, &errMsg);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Problem encountered while attempting to create the list table: %s\n", errMsg);
    }
    else
    {
        fprintf(stdout, "ALL GOOD, the table has been successfully created.");
    }
    
    sqlite3_close(db);
    
    
//    FILE *pList = fopen("list.txt", "r");
//    if(pList == NULL)
//    {
//        createList();
//    }
//    else
//    {
//        readList();
//    }
//
//    bool flag = true;
//
//    while(flag)
//    {
//        printf("What would you like to do?\nEnter 'A' to add a new item, 'L' to list the items, 'R' to remove an item from the list, or 'Q' to quit the program:\n");
//
//        char usrInput = getc(stdin);
//
//        clrBuff();
//
//        switch (toupper(usrInput))
//        {
//        case 'A':
//            writeList();
//            break;
//        
//        case 'L':
//            readList();
//            break;
//
//        case 'R':
//            removeItem();
//            break;
//
//        case 'Q':
//            flag = false;
//            printf("See ya");
//            break;
//        
//        default:
//            printf("The input %c is not valid. Please try again!\n", usrInput);
//            break;
//        }
//    }
//
    return 0;
//}
//
//void readList(void)
//{
//    FILE *pReadList = fopen("list.txt", "r");
//    printf("####################\n");
//    printf("\nID\tItem\n");
//    printf("--------------------\n");
//    int counter = 1;
//    char buff[255];
//    while(fgets(buff,255,pReadList) != NULL)
//    {
//        printf("%d)\t %s", counter, buff);
//        counter++;
//    }
//    printf("\n####################\n");
//    fclose(pReadList);
//}
//
//void writeList(void)
//{
//    FILE *pWriteList = fopen("list.txt", "a");
//    printf("Please enter what should be added to the list:\n");
//    char usrInputToWrite[255];
//    fgets(usrInputToWrite, 255, stdin);
//    fputs(usrInputToWrite, pWriteList);
//    fclose(pWriteList);
//}
//
//void createList(void)
//{
//    FILE *pCreateList = fopen("list.txt", "w");
//    fputs("", pCreateList);
//    fclose(pCreateList);
//}
//
//void removeItem(void)
//{
//    FILE *pReadList = fopen("list.txt", "r");
//    printf("Please enter the ID of the item that should be removed from the list:\n");
//    int itemID;
//    scanf("%d", &itemID);
//    clrBuff();
//    FILE *pTempList = fopen("tempList.txt", "w");
//    int nrOfLines = 0;
//    pReadList = fopen("list.txt", "r");
//    char buff[255];
//    while(fgets(buff, 255, pReadList) != NULL)
//    {
//        nrOfLines++;
//        if(nrOfLines == itemID)
//        {
//            continue;
//        } else
//        {
//            fputs(buff, pTempList);
//        }
//    }
//    fclose(pReadList);
//    fclose(pTempList);
//    remove("list.txt");
//    rename("tempList.txt", "list.txt");
//}
//
//void clrBuff(void)
//{
//    int c;
//    while ((c = getchar()) != '\n' && c != EOF){}
}
