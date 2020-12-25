#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

// Complete the matrixRotation function below.
void matrixRotation(int matrix_rows, int matrix_columns, long** matrix, int r) {
for(long k=0;k<r;k++)
{
  long temp[matrix_columns];
  int c=0;
  int d;
  if(matrix_rows<matrix_columns)
    d=matrix_rows/2;
  else d=matrix_columns/2;

  for(long i=0;i<d;i++)
  {
    c++;
    temp[i]=matrix[i][i];
    for(long j=i;j<matrix_columns-1-i;j++)
    {
        matrix[i][j]=matrix[i][j+1];
    }
  }
  for(long j=matrix_columns-1;j>matrix_columns-1-c;j--)
  {
     for(long i=matrix_columns-1-j;i<matrix_rows-matrix_columns+j;i++)
     {
         matrix[i][j]=matrix[i+1][j];
     }
  } 
  for(long i=matrix_rows-1;i>=matrix_rows/2;i--)
  {
    for(long j=matrix_columns-matrix_rows+i;j>matrix_rows-i-1;j--)
    {
        matrix[i][j]=matrix[i][j-1];
    }
  }
  for(long j=0;j<c;j++)
  {
      long i;
     for(i=matrix_rows-1-j;i>j+1;i--)
     {
         matrix[i][j]=matrix[i-1][j];
     }
     matrix[i][j]=temp[j];
  }
}
  for(long i=0;i<matrix_rows;i++)
  {
      for(long j=0;j<matrix_columns;j++)
      {
          printf("%ld ",matrix[i][j]);
      }
      printf("\n");
  }
}

int main()
{
    char** mnr = split_string(rtrim(readline()));

    char* m_endptr;
    char* m_str = mnr[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mnr[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* r_endptr;
    char* r_str = mnr[2];
    int r = strtol(r_str, &r_endptr, 10);

    if (r_endptr == r_str || *r_endptr != '\0') { exit(EXIT_FAILURE); }

    long** matrix = malloc(m * sizeof(long*));

    for (int i = 0; i < m; i++) {
        *(matrix + i) = malloc(n * (sizeof(int)));

        char** matrix_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < n; j++) {
            char* matrix_item_endptr;
            char* matrix_item_str = *(matrix_item_temp + j);
            int matrix_item = strtol(matrix_item_str, &matrix_item_endptr, 10);

            if (matrix_item_endptr == matrix_item_str || *matrix_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(matrix + i) + j) = matrix_item;
        }
    }

    int matrix_rows = m;
    int matrix_columns = n;

    matrixRotation(matrix_rows, matrix_columns, matrix, r);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

