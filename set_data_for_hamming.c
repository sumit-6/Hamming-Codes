#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

int columnsum(int index,int Nrows,int* data);
int columnsum(int index,int Nrows,int* data)
{
    int j,sum = 0;
    for (j = 0; j<Nrows; j++)
    {
        if (*(data + ((Nrows*j) + index)) == 1)
        sum = sum + 1;
    }
    return sum;
}

int rowsum(int index,int Ncolumns,int* data);
int rowsum(int index,int Ncolumns,int* data)
{
    int j,sum = 0;
    for (j = 0; j<Ncolumns; j++)
    {
        if (*(data + ((Ncolumns*index) + j)) == 1)
        sum = sum + 1;
    }
    return sum;
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

void setforHAMMING(int Nrows,int power,int* bin,int* data);
void setforHAMMING(int Nrows,int power,int* bin,int* data)
{
    int i = 0,j = 0,res = 0,index = 0,point = power,parity = 0;
    for (i = power-1; i>=0; i--)
    {
        index = 0;
        res = 0;
        if (i >= power/2)
        {
            for (j = 0; j<Nrows; j++)
            {
                decTObin(j,bin,power);
                if (*(bin+point-1) == 1)
                {
                    res = res + columnsum(index,Nrows,data);
                }
                index++;
            }
            if (res % 2 == 0)
            {
                *(data + putpow(2,parity)) = 0;
            }
            else
            {
                *(data + putpow(2,parity)) = 1;
            }
        }
        else
        {
            for (j = 0; j<putpow(2,power); j=j+Nrows)
            {
                decTObin(j,bin,power);
                if (*(bin+point-1) == 1)
                {
                    res = res + rowsum(index,Nrows,data);
                }
                index++;
            }
            if (res % 2 == 0)
            {
                *(data + putpow(2,parity)) = 0;
            }
            else
            {
                *(data + putpow(2,parity)) = 1;
            }
        }
        point--;
        parity++;
    }
}

int put_parity_bit(int rows,int columns,int *data);
int put_parity_bit(int rows,int columns,int *data)
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

void sizeoffile(int *Size,char *filename);
void sizeoffile(int *Size,char *filename)
{
    int max_length = 1024,row = 0,i = 0,count = 0,summ = 0;
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
            summ = summ + count;
        }
    }
    *Size = summ;
    fclose(file_ptr);
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

int abs(int a);
int abs(int a)
{
    if (a < 0)
    {
        return -a;
    }
    else
    {
        return a;
    }
}

int func(int N,int num);
int func(int N,int num)
{
    int i,index = 0;
    for (i = 1; i<N; i=putpow(2,index))
    {
        if (num == i)
        {
            return 1;
        }
        index++;
    }
    return 0;
}

int inject(int Size,int* List,int index);
int inject(int Size,int* List,int index)
{
    static int count = 0;
    int n = 1,flag = 0;
    *(List + index) = 2*n;
    if (Size <= 0)
    {
        return 0;
    }
    while ((Size - putpow(2,2*n) + 2*n + 1) >= 0)
    {
        if ((Size <= (putpow(2,2*n) - 2*n - 1)) && (Size < (putpow(2,2*(n+1)) - 2*(n+1) - 1)))
        {
            *(List + index) = putpow(2,n);
            flag = 0;n++;
        }
        else if ((Size > (putpow(2,2*n) - 2*n - 1)) && (Size <= (putpow(2,2*(n+1)) - 2*(n+1) - 1)))
        {
            if (((Size - (putpow(2,2*n) - 2*n - 1))/(putpow(2,2*n) - 2*n - 1))*(2*n + 1) < ((putpow(2,2*(n+1))) - Size))
            {
                *(List + index) = putpow(2,n);
                flag = 0;n++;
            }
            else
            {
                *(List + index) = putpow(2,(n+1));
                flag = 1;n=n+2;
            }
        }
        else if ((Size > (putpow(2,2*n) - 2*n - 1)) && (Size > (putpow(2,2*(n+1)) - 2*(n+1) - 1)))
        {
            *(List + index) = putpow(2,(n+1));
            flag = 1;n=n+2;
        }
    }
    count++;

    if (n != 1)
    {
        n--;
    }
    inject((Size - putpow(2,2*n) + 2*n + 1),List,index+1);
    return count;
}

int main()
{
    int sides[100],Size,n,Nrow,Ncolumn,max_length = 1024,i,j,k,index = 0,counter = 0,power;
    char filename[] = "C:\\Users\\verma\\OneDrive\\Desktop\\Raw_Data.txt";
    sizeoffile(&Size,filename);
    n = inject(Size,&sides[0],0);
    FILE* file_ptr = fopen(filename,"r");
    char line[max_length];
    fgets(line,max_length,file_ptr);
    for (i = 0; i<n; i++)
    {
        char directory[] = "C:\\Users\\verma\\OneDrive\\Desktop\\";
        Nrow = sides[i];
        Ncolumn = sides[i];
        int data[Nrow][Ncolumn];
        char corrected_data[Nrow][Ncolumn],str[Ncolumn+2],txtname[max_length];
        int binary[Power_of_two(Nrow*Nrow)];
        for (j = 0; j<Nrow; j++)
        {
            for (k = 0;k < Ncolumn; k++)
            {

                if (counter >= Size)
                {
                    data[j][k] = 0;
                    counter++;
                    continue;
                }
                else if (line[index] == '\n')
                {
                    fgets(line,max_length,file_ptr);
                    index = 0;
                    k--;
                }
                else if ((j == 0) && (k == 0))
                {
                    data[j][k] = 0;
                    continue;
                }
                else if (func(Nrow*Ncolumn,((Ncolumn*j) + k)) == 1)
                {
                    data[j][k] = 0;
                    continue;
                }
                else if (func(Nrow*Ncolumn,((Ncolumn*j) + k)) == 0)
                {
                    counter++;
                    if (line[index] == '1')
                    {
                        data[j][k] = 1;
                        index++;
                    }
                    else if (line[index] == '0')
                    {
                        data[j][k] = 0;
                        index++;
                    }
                }
            }
        }
        power = Power_of_two(Nrow*Nrow);
        setforHAMMING(Nrow,power,binary,&data[0][0]);
        put_parity_bit(Nrow,Ncolumn,&data[0][0]);
        printdata(Nrow,Ncolumn,&data[0][0]);
        printf("\n");
        printf("Enter the name of the txt file in which you want to store this set of data:");
        printf("\n");
        gets(txtname);
        strcat(directory,txtname);
        FILE* file_ptr1;
        file_ptr1 = fopen(directory,"w");
        for (j = 0; j<Nrow; j++)
        {
            for (k = 0; k<Ncolumn; k++)
            {
                if (data[j][k] == 0)
                {
                    corrected_data[j][k] = '0';
                }
                else
                {
                    corrected_data[j][k] = '1';
                }
            }
            if (j != Nrow-1)
            {
                for (k = 0; k<Ncolumn; k++)
                {
                    str[k] = corrected_data[j][k];
                }
                str[Ncolumn] = '\n';str[Ncolumn + 1] = '\0';
                fputs(str,file_ptr1);
            }
            else if (j == Nrow -1 )
            {
                for (k = 0; k<Ncolumn; k++)
                {
                    str[k] = corrected_data[j][k];
                }
                str[Ncolumn] = '\0';
                fputs(str,file_ptr1);
            }
        }
        fclose(file_ptr1);
    }
    fclose(file_ptr);
    return 0;
}

