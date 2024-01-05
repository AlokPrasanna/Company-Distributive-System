#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX 20
int i = 0;
struct driver
{
    char drivId[6];
    char drivName[31];
    char vechiNo[11];
};

struct stock
{
    int loadAmount;
    int balanceAmount;
};

struct salesman
{
    _Bool check;
    char salId[6];      //id of the salesman
    char salName[31];   //name of the salesman
    int salAmout;     //sales amount
    int totalSales;
    struct driver approDiv; //appropriate driver
    struct stock approStock; //appropriate stock
};

//prototypes of functions
char mainMenu(void);
void memoryLoad(struct salesman salesmanArr[]);
_Bool checking(struct salesman salesmanArr[]);
void createAcc(struct salesman salesmanArr[]);
void dailyLoad(struct salesman salesmanArr[]);
void balanceLoad(struct salesman salesmanArr[]);
void Analatics(struct salesman salesmanArr[]);
void displayRecord(void);
void accountDetails(void);


_Bool checking(struct salesman salesmanArr[])
{
    char checkId[6];
    printf("Enter salesman's user Id : ");
    gets(checkId);
    for(i=0; i<MAX; i++)
    {
        if(strcmp(salesmanArr[i].salId, checkId) == 0)
            return 1;
        else
            return 0;
    }
}
int ch;// choice...

void createAcc(struct salesman salesmanArr[])
{
    if(salesmanArr[19].check)
    {
        printf("Account Is Reach Maximum!!...\n\n");
    }
    else{
    printf("\n\n\t\t\t--->>>Create New Account<<<---\n\n\n\n");
    char checkId[6];
    printf("\t>. Enter salesman's user Id : ");
    gets(checkId);

    for(i=0; i<MAX; i++)
    {
        if(strcmp(salesmanArr[i].salId, checkId) == 0)
        {
            printf("\n\n\t\tThis salesman ID already has an account!!!\n\n**Please Create new account :)");
            return;
        }
    }

    for(i=0; i<MAX; i++)
    {
        if(salesmanArr[i].check == 0)
        {
            salesmanArr[i].check = 1;
            strcpy(salesmanArr[i].salId, checkId);
            printf("\t>. Enter salesman's name : ");
            gets(salesmanArr[i].salName);
            printf("\t>. Enter driver Id : ");
            gets(salesmanArr[i].approDiv.drivId);
            printf("\t>. Enter driver name : ");
            gets(salesmanArr[i].approDiv.drivName);
            printf("\t>. Enter vehicle number : ");
            gets(salesmanArr[i].approDiv.vechiNo);
            FILE *insertData;
            insertData = fopen("data.txt", "a");
            fprintf(insertData, "%s%15s%15s%15s%15s\n", salesmanArr[i].salId, salesmanArr[i].salName, salesmanArr[i].approDiv.drivId, salesmanArr[i].approDiv.drivName,salesmanArr[i].approDiv.vechiNo);

            fclose(insertData);
            printf("\n\n\tAccount has created sucessfuly\n");
            printf("\n\n\tPress any key to continue...\n");
            getchar();
            system("cls");

            memoryLoad(salesmanArr);
            return;
        }
      }
   }
}



void dailyLoad(struct salesman salesmanArr[])
{
    FILE *recFile;
    recFile = fopen("daily_record_log.txt", "a");
    time_t rawtime;
    time (&rawtime);
    struct tm *timeinfo = localtime (&rawtime);
    char findId[6];
    printf("\n\n\t\t--->>> Loading Section <<<---\n\n\n\n");
    printf("\t>. Enter salesman's Id : ");
    gets(findId);
    int load;
    printf("\t>. Enter loaded stock amount : ");
    scanf("%d", &load);
    getchar();
    for(i=0; i<MAX; i++)
    {
        if(strcmp(salesmanArr[i].salId, findId) == 0)
        {
            salesmanArr[i].approStock.loadAmount = load;
            break;
        }
    }
    fprintf(recFile, "%0d/%d/%d%20s%25s%20d\n", timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900, salesmanArr[i].salId, salesmanArr[i].salName, load);
    fclose(recFile);
            printf("\n\n\tPress any key to continue...\n");
            getchar();
            system("cls");
    return;
}

void balanceLoad(struct salesman salesmanArr[])
{
    FILE *balanceFile;
    balanceFile = fopen("final_daily_rec.txt", "a");
    time_t rawtime;
    time (&rawtime);
    struct tm *timeinfo = localtime (&rawtime);
    char findId[6];
    printf("\n\n\t\t\t--->>> Balance Section <<<---\n\n\n\n");
    printf("\t>. Enter salesman's Id : ");
    gets(findId);
    int balance;
    printf("\t>. Enter balance stock amount : ");
    scanf("%d", &balance);
    getchar();
    for(i=0; i<MAX; i++)
    {
        if(strcmp(salesmanArr[i].salId, findId) == 0)
        {
            salesmanArr[i].approStock.balanceAmount = balance;
            salesmanArr[i].salAmout = salesmanArr[i].approStock.loadAmount - balance;
            break;
        }
    }
    fprintf(balanceFile, "%0d/%d/%d%20s%25s%20d%20d%20d\n", timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900, salesmanArr[i].salId, salesmanArr[i].salName, salesmanArr[i].approStock.loadAmount, balance, salesmanArr[i].approStock.loadAmount-balance);
    fclose(balanceFile);

    //*************************
    FILE *totalSales;
    totalSales = fopen("analaticsData.txt", "a");
    fprintf(totalSales,"%s %d\n", salesmanArr[i].salId, salesmanArr[i].salAmout);
    fclose(totalSales);
            printf("\n\n\tPress any key to continue...\n");
            getchar();
            system("cls");
    return;
}

/********************************/
void Analatics(struct salesman salesmanArr[])
{
    system("cls");
    FILE *salFile;
    salFile = fopen("analaticsData.txt", "a+");
    int n=0, ch;
    while(EOF != (ch = getc(salFile)))
    {
        if(ch == '\n')
            n++;
    }
    rewind(salFile);
    for(i=0; i<n; i++)
    {
        char checkId[6];
        int amount = 0;
        fscanf(salFile, "%s %d", checkId, &amount);
        int j;
        for(j=0; j<MAX; j++)
        {
            if(strcmp(checkId, salesmanArr[j].salId) == 0)
            {
                salesmanArr[j].totalSales += amount;
                break;
            }
        }
    }
    printf("\n\n\t\t\t--->>> Analytics Section <<<---\n\n\n\n");
    //int q = i;
    for(i=0; i<MAX; i++)
    {
        printf("\t>. %0s\t", salesmanArr[i].salId);
        int j;
        for(j=0; j<salesmanArr[i].totalSales/100; j++)
        {
            printf("#");
        }
        printf("  %d", salesmanArr[i].totalSales);
        salesmanArr[i].totalSales = 0;
        printf("\n\n");
    }

    fclose(salFile);

    printf("\n\n\tPress any key to continue...\n");
    getchar();
    system("cls");
    return;
}
void displayRecord(void)
{
    FILE *display;
    display = fopen("final_daily_rec.txt","r");
    printf("\n\n\t\t\t--->>> Display Records Section <<<---\n\n\n\n");
    printf("%0s%25s%25s%25s%25s%20s\n","Date", "SalID", "SalName", "LoadingAmount", "UnloadingAmount", "SaleAmout");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");

    char c;
    while((c = getc(display)) != EOF)
    {
        printf("%c", c);

    }
    fclose(display);
    printf("----------------------------------------------------------------------------------------------------------------------------\n");

    printf("\n\n\tPress any key to continue...\n");
    getchar();
    system("cls");
    return ;
}
void accountDetails(void)
{
    FILE *showdetails;
    showdetails = fopen("data.txt","r");
    printf("\n\n\t\t\t--->>> Account Details Section <<<---\n\n\n\n");
    printf("%0s%15s%15s%15s%15s\n", "SalID", "SalName", "DriID", "DrName", "VehiNO\n");
    printf("----------------------------------------------------------------------\n");

    char c;
    while((c = getc(showdetails)) != EOF)
    {
        printf("%c", c);

    }
    fclose(showdetails);
    printf("----------------------------------------------------------------------\n");
    printf("\n\n\tPress any key to continue...\n");
    getchar();
    system("cls");
    return ;
}

void memoryLoad(struct salesman salesmanArr[])
{
    FILE *loadFile;
    loadFile = fopen("data.txt", "a+");
    int n = 0, ch;
    while(EOF != (ch = getc(loadFile)))
    {
        if(ch == '\n')
            n++;
    }
    rewind(loadFile);
    for(i=0; i<n; i++)
    {
        ////////************************************//////////
        fscanf(loadFile, "%s %s %s %s %s", salesmanArr[i].salId, salesmanArr[i].salName, salesmanArr[i].approDiv.drivId, salesmanArr[i].approDiv.drivName, salesmanArr[i].approDiv.vechiNo);
        salesmanArr[i].check = 1;
    }printf("\n");
    system("cls");
    return;
}


char mainMenu(void)
{
    char choise;
    char arg[] = {'c','l','b','a','q','d','r'};
    printf("\n\n\t\t------ WELCOME TO XYZ COMPANY DISTRIBUTION SYSTERM ------\n\n");
    printf("\t--->>> Main Menu <<<---\n\n");
    printf("* Create New Account          -> Press c \n");
    printf("* Manage Loading              -> Press l \n");
    printf("* Manage Unloading            -> Press b \n");
    printf("* Display Daily Records       -> Press r \n");
    printf("* Account Details             -> Press d \n");
    printf("* Analyze salesman Progress   -> Press a \n");
    printf("* Quite                       -> Press q \n");
    printf("\n\n* Your Choice : ");
    gets(&choise);

    for(i=0; i<strlen(arg); i++)
    {
        if(arg[i] == choise)
            return choise;
    }
    printf("Wrong choise!\n");
    return mainMenu();

}


int main(void)
{
    struct salesman salesmanArr[MAX] = {0};
    memoryLoad(salesmanArr);

    char choise = mainMenu();
    while(1)
    {
        if(choise == 'c')
        {   system("cls");

            createAcc(salesmanArr);
            choise = mainMenu();
        }
        if(choise == 'l')
        {   system("cls");
            dailyLoad(salesmanArr);
            choise = mainMenu();
        }
        if(choise == 'b')
        {   system("cls");
            balanceLoad(salesmanArr);
            choise = mainMenu();
        }
          if(choise == 'r')
        {   system("cls");
            displayRecord();
            choise = mainMenu();
        }
        if(choise == 'd')
        {   system("cls");
            accountDetails();
            choise = mainMenu();
        }
        if(choise == 'a')
         {
            system("cls");
            Analatics(salesmanArr);
            choise = mainMenu();
        }
        if(choise == 'q')
            break;
    }
    printf("\n\n\t\tGOOD BYE!!!\n\n\n\n");

    return 0;
}
