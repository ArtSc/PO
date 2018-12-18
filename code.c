#include <stdio.h>
#define N 9
#define UNASSIGNED 0

int get_int(int min,int max)
{
    int a;
    char l;
    while(scanf("%d%c",&a,&l)!=2||l!='\n'||(a<min)||(a>max))
    {
        rewind(stdin);
        printf("Error,please enter between %d-%d",min,max);
        printf("\nPlease input number again =");
    }
    return a;
}
void Read_File(char *filename, int grid[N][N],int *n)
{
    FILE *fp;
    int i, j, value;
    if((fp = fopen(filename, "r")) != NULL)
        {
        for(i = 0; i < N; i++)
        {
            for(j = 0; j < N; j++)
            {
                fscanf(fp, "%d",&value);
                grid[i][j] = value;
            }
        }
        printf("Read file '%s' success\n",filename);
        fclose(fp);
        *n = 1;
    }
    else
    {
        printf("Cannot open file '%s' [file not found or invalid input].\n", filename);
        *n = 0;
    }
}

int is_exist_row(int grid[N][N], int row, int num)
{
	for (int col = 0; col < 9; col++)
        {
		if (grid[row][col] == num)
		{
			return 1;
		}
	}
	return 0;
}

int is_exist_col(int grid[N][N], int col, int num)
{
	for (int row = 0; row < 9; row++)
        {
		if (grid[row][col] == num)
		{
			return 1;
		}
	}
	return 0;
}

int is_exist_box(int grid[N][N], int startRow, int startCol, int num)
{
	for (int row = 0; row < 3; row++)
        {
		for (int col = 0; col < 3; col++)
		{
			if (grid[row + startRow][col + startCol] == num)
			{
				return 1;
			}
		}
	}
	return 0;
}

int is_safe_num(int grid[N][N], int row, int col, int num)
{
	return !is_exist_row(grid, row, num)
			&& !is_exist_col(grid, col, num)
			&& !is_exist_box(grid, row - (row % 3), col - (col %3), num);
}

int find_unassigned(int grid[N][N], int *row, int *col)
{
	for (*row = 0; *row < N; (*row)++)
        {
		for (*col = 0; *col < N; (*col)++)
		{
			if (grid[*row][*col] == 0)
			{
				return 1;
			}
		}
	}
	return 0;
}

int solve(int grid[N][N])
{
	int row = 0;
	int col = 0;
	if (!find_unassigned(grid, &row, &col))
    {
		return 1;
	}
	for (int num = 1; num <= N; num++ )
        {
		if (is_safe_num(grid, row, col, num))
            {
                grid[row][col] = num;
                if (solve(grid))
                    {
                        return 1;
                    }
                grid[row][col] = UNASSIGNED;
            }
        }
	return 0;
}

void print_grid(int grid[N][N])
{
	for (int row = 0; row < N; row++)
    {
		for (int col = 0; col < N; col++)
		{
            if(grid[row][col]==0) printf(" .");
			else printf("%2d", grid[row][col]);
		}
		printf("\n");
	}
}


int main() {
    int grid[N][N];
    char key[100000];
    int n = 1;
	printf("Do you want to get the value from the file.txt[0] or put by yourself[1] :");
	int a = get_int(0,1);
    if(a==0)
    {
        printf("Users:\\File Name+.txt >");
        gets(key);
        Read_File(key,grid,&n);
        if(n == 1)
        {
            printf("Your sudoku is \n");
            print_grid(grid);
            printf("================================\n");
        }
    }
    else if(a==1)
    {
        printf("If it is a space, enter 0.\n");
        for(int i=0;i<N;i++)
             for(int j=0;j<N;j++)
             {
                printf("SUDOKU[%d][%d] : ",i+1,j+1);
                grid[i][j] = get_int(0,9);
             }
        printf("Your sudoku is \n");
        print_grid(grid);
        printf("================================\n");
    }
    if (n == 1)
    {
        if(solve(grid))
            {
            print_grid(grid);
            }
        else
            {
            printf("no solution");
            }
    }
return 0;
}
