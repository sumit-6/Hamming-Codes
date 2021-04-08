#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


int cfileexists(const char* filename);
int cfileexists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void inject(int *Nrows,int *Ncolumns,char *filename);
void inject(int *Nrows,int *Ncolumns,char *filename)
{
    int max_length = 1024,Ncolumn = 0,row = 0,i = 0,count = 0;
    char line[max_length];
    FILE *file_ptr;
    file_ptr = fopen(filename,"r");
    if (cfileexists(filename) == 1)
    {
        row = 0;
        while (fgets(line,max_length,file_ptr))
        {
            count = 0;
            for (i = 0; i<strlen(line); i++)
            {
                if (line[i] != '\n')
                {
                    count++;
                }
            }
            row++;
        }
    }
    *Nrows = row;
    *Ncolumns = count;
    fclose(file_ptr);
}

void printdata(int rows,int columns,int* data);
void printdata(int rows,int columns,int* data)
{
    int i = 0, j= 0;int *address;
    for (i = 0; i<rows; i++)
    {
        for (j = 0; j<columns; j++)
        {
            address = data + ((columns*i) + j);
            printf("%d ",*(address));
        }
        printf("\n");
    }
}

int check_parity_bit(int rows,int columns,int *data);
int check_parity_bit(int rows,int columns,int *data)
{
        int i,j,count = 0;
    for (i = 0; i<rows; i++)
    {
        for (j = 0; j<columns; j++)
        {
            if ((i == 0) && (j == 0))
            {
                continue;
            }
            else
            {
                if (*(data + (columns*(i) + j)) == 1)
                    count++;
            }

        }
    }
    if (count%2 == 0)
    {
        if (*(data + (columns*(0) + 0)) == 0)
        {
            return 1;
        }
        else if (*(data + (columns*(0) + 0)) == 1)
        {
            return 0;
        }
    }
    else
    {
        if (*(data + (columns*(0) + 0)) == 1)
        {
            return 1;
        }
        else if (*(data + (columns*(0) + 0)) == 0)
        {
            return 0;
        }
    }
}

void enter_parity_bit(int rows,int columns,int *data);
void enter_parity_bit(int rows,int columns,int *data)
{
    int i,j,count = 0;
    for (i = 0; i<rows; i++)
    {
        for (j = 0; j<columns; j++)
        {
            if ((i == 0) && (j == 0))
            {
                continue;
            }
            else
            {
                if (*(data + (columns*(i) + j)) == 1)
                    count++;
            }

        }
    }
    if (count%2 == 0)
    {
        *(data + (columns*(0) + 0)) = 0;
    }
    else
    {
        *(data + (columns*(0) + 0)) = 1;
    }
}

int main()
{
    int row,Nrow,Ncolumn,col,i = 0,count = 0;
    FILE *file_ptr;
    int max_length = 1024;
    char filename[max_length];
    printf("Enter location of your file: ");
    gets(filename);
    inject(&Nrow,&Ncolumn,filename);
    int data[Nrow][Ncolumn];
    char line[max_length];

    file_ptr = fopen(filename,"r");
    if (cfileexists(filename) == 1)
    {
        row = 0;
        while (fgets(line,max_length,file_ptr))
        {
            count = 0;
            for (i = 0; i<strlen(line); i++)
            {
                if (line[i] != '\n')
                {
                    count++;
                }
            }
            for (col = 0; col<count; col++)
            {
                if ((line[col] != '\n') && (line[col] != '\0'))
                {
                    if (line[col] == '1')
                    {
                        data[row][col] = 1;
                    }
                    else if (line[col] == '0')
                    {
                        data[row][col] = 0;
                    }
                    else
                    {
                        continue;
                    }
                }
                else if (line[col] == '\n')
                {
                    continue;
                }
            }
            row++;
        }
    }
    else
    {
        printf("Sorry your file doesn't exist");
    }
    fclose(file_ptr);
    printf("Input data is:\n");
    printdata(Nrow,Ncolumn,&data[0][0]);
    printf("\nResult: ");
    if (check_parity_bit(Nrow,Ncolumn,&data[0][0]) == 0)
    {
        printf("There is some odd number of discrepencies.");
    }
    else if (check_parity_bit(Nrow,Ncolumn,&data[0][0]) == 1)
    {
        printf("There may be some even number of discrepencies or no discrepencies at all.");
    }
    printf("\n\n");
    return 0;
}
