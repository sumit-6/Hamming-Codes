#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

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

int b_to_d(int location[], int len);
int b_to_d(int location[], int len)
{
    int i,sum = 0;
    for(i=len-1;i>=0;i--)
    {
        if(location[i] == 1)
        {
            sum = sum + pow(2,len-i-1);
        }
    }
    return sum;
}

int columnsum(int index,int Nrows,int* data);
int columnsum(int index,int Nrows,int* data)
{
    int j,sum = 0;
    for (j = 0; j<Nrows; j++)
    {
        sum = sum + *(data + ((Nrows*j) + index));
    }
    return sum;
}

int rowsum(int index,int Ncolumns,int* data);
int rowsum(int index,int Ncolumns,int* data)
{
    int j,sum = 0;
    for (j = 0; j<Ncolumns; j++)
    {
        sum = sum + *(data + ((Ncolumns*index) + j));
    }
    return sum;
}

void decTObin(int num,int* bin);
void decTObin(int num,int* bin)
{
    int i = 0,temp;
    for (i = 0; i<8; i++)
    {
        *(bin + i) = 0;
    }
    for (i = 0; num>0; i++)
    {
        *(bin + i) = num%2;
        num = num/2;
    }
    for (i = 0; i<4; i++)
    {
        temp = *(bin + i);
        *(bin + i) = *(bin + 7 - i);
        *(bin + 7 - i) = temp;
    }
}

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

void findERROR(int Nrows,int power,int* location,int* bin,int* data);
void findERROR(int Nrows,int power,int* location,int* bin,int* data)
{
    int i = 0,j = 0,res = 0,index = 0,point = power;
    for (i = power-1; i>=0; i--)
    {
        index = 0;
        res = 0;
        if (i >= power/2)
        {
            for (j = 0; j<Nrows; j++)
            {
                decTObin(j,bin);
                if (*(bin+point-1) == 1)
                {
                    res = res + columnsum(index,Nrows,data);
                }
                index++;

            }
            if (res % 2 == 0)
            {
                *(location + i) = 0;
            }
            else
            {
                *(location + i) = 1;
            }
        }
        else
        {
            for (j = 0; j<putpow(2,power); j=j+Nrows)
            {
                decTObin(j,bin);
                if (*(bin+point-1) == 1)
                {
                    res = res + rowsum(index,Nrows,data);
                }
                index++;
            }
            if (res % 2 == 0)
            {
                *(location + i) = 0;
            }
            else
            {
                *(location + i) = 1;
            }
        }
        point--;
    }
}

int main()
{
    int Nrow,Ncolumn,row,col,i = 0,count = 0,power;
    int x_error_index,y_error_index,j = 0;
    FILE *file_ptr;
    int max_length = 1024,flag = 0;
    char filename[] = "C:\\Users\\verma\\OneDrive\\Desktop\\abcTEXT.txt";
    //char filename[max_length];
    //printf("Enter file location: ");
    //gets(filename);
    inject(&Nrow,&Ncolumn,filename);
    int data[Nrow][Ncolumn];
    int binary[Power_of_two(Nrow*Ncolumn)];
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
        findERROR(Nrow,power,&location[0],&binary[0],&data[0][0]);

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
            x_error_index = b_to_d(i_array,power/2);
            y_error_index = b_to_d(j_array,power/2);
            printf("Error is at location: (%d , %d)",x_error_index,y_error_index);
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
    fclose(file_ptr);
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
