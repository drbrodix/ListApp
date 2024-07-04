#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "sqlite3.h"

void readList(sqlite3 *db);
void writeList(sqlite3 *db);
void removeItem(sqlite3 *db);
void clrBuff(void);

static int callback(void *data, int argc, char **argv, char **azColName)
{
    for(int i = 0; i<argc; i++){
        printf("%s \t", argv[i] ? argv[i] : "NULL");
    }
   
    printf("\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    
    //                          //
    //   CONNECTING TO THE DB   //
    //                          //
    sqlite3 *db;
    char *errMsg;
    int rc = sqlite3_open("db.db", &db);
    const char *createTable;
    
    //                             //
    //   REPORTING IF CONNECTION   //
    //       TO THE DB FAILED      //
    //                             //
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Problem encountered while attempting to open the database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    //                                //
    //   REPORTING IF CONNECTION TO   //
    //         DB IS SUCCESSFUL       //
    //                                //

    else
    {
        fprintf(stdout, "ALL GOOD, the DB has been successfully opened. \n");
    }

    //                          //
    //      CREATING TABLE      //
    //                          //
    
    createTable = "CREATE TABLE IF NOT EXISTS itemList (itemID INTEGER PRIMARY KEY, itemDesc TEXT NOT NULL);";
    
    rc = sqlite3_exec(db, createTable, 0, 0, &errMsg);
    
    //                                //
    //      REPORTING IF OPENING      //
    //          TABLE FAILED          //
    //                                //
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Problem encountered while attempting to create the list table: %s\n", errMsg);
    }
    
    //                                //
    //      REPORTING IF CREATING     //
    //       TABLE IS SUCCESSFUL      //
    //                                //
    
    else
    {
        fprintf(stdout, "ALL GOOD, the table has been successfully opened. \n\n");
    }
    
    //                        //
    //      CLI MENU FOR      //
    //    USER INTERACTION    //
    //                        //

    bool flag = true;

    while(flag)
    {
        printf("What would you like to do?\nEnter 'A' to add a new item, 'L' to list the items,\n'R' to remove an item from the list, or 'Q' to quit the program:\n");

        char usrInput = getc(stdin);

        clrBuff();

        switch (toupper(usrInput))
        {
        case 'A':
            writeList(db);
            break;
        
        case 'L':
            readList(db);
            break;

        case 'R':
            removeItem(db);
            break;

        case 'Q':
            flag = false;
            printf("See ya\n");
            break;
        
        default:
            printf("The input %c is not valid. Please try again!\n", usrInput);
            break;
        }
    }

    sqlite3_close(db);

    return 0;
}

//                                //
//       FUNCTIONS SECTION        //
//                                //

void readList(sqlite3 *db)
{
    char *sqlQuery = "SELECT * FROM itemList;";
    char *errMsg;
    
    fprintf(stdout, "###############\n");
    fprintf(stdout, "\nID \t Description\n");
    fprintf(stdout, "---------------\n");
    
    int rc = sqlite3_exec(db, sqlQuery, callback, 0, &errMsg);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Problem encountered while attempting to query data: %s\n", errMsg);
    }
    fprintf(stdout, "###############\n");
}

void writeList(sqlite3 *db)
{
    printf("Please enter what should be added to the list:\n");
    char usrInputToWrite[255];
    char *errMsg;
    char *sqlQuery = NULL;
    fgets(usrInputToWrite, sizeof(usrInputToWrite), stdin);
    
    asprintf(&sqlQuery, "INSERT INTO itemList (itemID, itemDesc) VALUES (NULL, '%s');", usrInputToWrite);
    
    int rc = sqlite3_exec(db, sqlQuery, 0, 0, &errMsg);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Problem encountered while attempting to add data to the list: %s\n", errMsg);
    }
}

void removeItem(sqlite3 *db)
{
    printf("Please enter the ID of the item that should be removed from the list:\n");
    int itemID;
    scanf("%d", &itemID);
    clrBuff();

    char *errMsg;
    char *sqlDelete = NULL;
    
    asprintf(&sqlDelete, "DELETE FROM itemList WHERE itemID = %d;", itemID);
    
    int rc = sqlite3_exec(db, sqlDelete, 0, 0, &errMsg);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Problem encountered while attempting to remove data from the list: %s\n", errMsg);
    }
}

void clrBuff(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}
