#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

int Power_of_two(int Size);
int Power_of_two(int Size)
{
    int iter = 0;
    while (Size != 1)
    {
        Size = Size/2;
        iter++;
    }
    return iter;
}

int putpow(int x,int y);
int putpow(int x,int y)
{
    int i = 0,res=1;
    for (i = 0; i<y; i++)
    {
        res = res*x;
    }
    return res;
}

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

int binaryTOdecimal(int binary[], int len);
int binaryTOdecimal(int binary[], int len)
{
    int i = 0,res = 0;
    for (i = len-1; i>=0; i--)
    {
        if (binary[i] == 1)
        {
            res = res + putpow(2,len-1-i);
        }
    }
    return res;
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

void decTObin(int num,int* bin,int power);
void decTObin(int num,int* bin,int power)
{
    int i = 0,temp;
    for (i = 0; i<power; i++)
    {
        *(bin + i) = 0;
    }
    for (i = 0; num>0; i++)
    {
        *(bin + i) = num%2;
        num = num/2;
    }
    for (i = 0; i<power/2; i++)
    {
        temp = *(bin + i);
        *(bin + i) = *(bin + power-1 - i);
        *(bin + power-1 - i) = temp;
    }
}

int FindERROR(int *data,int Nrows,int Ncolumns);
int FindERROR(int *data,int Nrows,int Ncolumns)
{
    int i = 0, j = 0,res = 0;
    for (i = 0; i<Nrows; i++)
    {
        for (j = 0; j<Ncolumns; j++)
        {
            if (*(data + (Ncolumns*(i) + j)) == 1)
                {
                    res = res ^ (Ncolumns*(i) + j);
                }
        }
    }
    return res;
}

int main()
{
    int Nrow,Ncolumn,max_length = 1024,i = 0,j=0,row = 0,col = 0,count = 0,flag = 0;
    int error_no,power,x_error_index,y_error_index;
    FILE *file_ptr;
    char filename[] = "C:\\Users\\verma\\OneDrive\\Desktop\\datass.txt";
    inject(&Nrow,&Ncolumn,filename);
    int data[Nrow][Ncolumn];
    char corrected_data[Nrow][Ncolumn],str[Ncolumn+2];

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
        printf("Input data is:\n");
        printdata(Nrow,Ncolumn,&data[0][0]);
        power = Power_of_two(Nrow*Ncolumn);
        int i_array[power/2],j_array[power/2],location[power];
        error_no = FindERROR(&data[0][0],Nrow,Ncolumn);
        decTObin(error_no,&location[0],power);
        printf("\n");
        for (i = 0; i<power; i++)
        {
            if (location[i] == 1)
            {
                flag++;
            }
        }
        if (flag != 0)
        {
            printf("\n");
            for (i = 0; i<sizeof(i_array)/sizeof(int); i++)
            {
                i_array[i] = location[i];
            }
            for (i = 0; i<sizeof(j_array)/sizeof(int); i++)
            {
                j_array[i] = location[(sizeof(i_array)/sizeof(int))+i];
            }
            x_error_index = binaryTOdecimal(i_array,power/2);
            y_error_index = binaryTOdecimal(j_array,power/2);
            printf("Error is at the location: (%d , %d)",x_error_index,y_error_index);
            if (data[x_error_index][y_error_index] == 1)
            {
                data[x_error_index][y_error_index] = 0;
            }
            else
            {
                data[x_error_index][y_error_index] = 1;
            }
        }
        else
        {
            printf("\n");
            if (check_parity_bit(Nrow,Ncolumn,&data[0][0]) == 1)
            {
                printf("There is no error in this dataset.");
                fclose(file_ptr);
            }
            else
            {
                printf("Error is at location: (0 , 0)");
                fclose(file_ptr);
            }
        }
    }
    else
    {
        printf("Sorry your file doesn't exist");
    }
    printf("\n");
    if (flag != 0)
    {
        printf("The original data is: \n");
        printdata(Nrow,Ncolumn,&data[0][0]);

        file_ptr = fopen(filename,"w");
        for (i = 0; i<Nrow; i++)
        {
            for (j = 0; j<Ncolumn; j++)
            {
                if (data[i][j] == 0)
                {
                    corrected_data[i][j] = '0';
                }
                else
                {
                    corrected_data[i][j] = '1';
                }
            }
            if (i != Nrow-1)
            {
                for (j = 0; j<Ncolumn; j++)
                {
                    str[j] = corrected_data[i][j];
                }
                str[Ncolumn] = '\n';str[Ncolumn + 1] = '\0';
                fputs(str,file_ptr);
            }
            else if (i == Nrow -1 )
            {
                for (j = 0; j<Ncolumn; j++)
                {
                    str[j] = corrected_data[i][j];
                }
                str[Ncolumn] = '\0';
                fputs(str,file_ptr);
            }
        }
        fclose(file_ptr);
    }
    return 0;
}
