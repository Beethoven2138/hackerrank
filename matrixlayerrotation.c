//len(tmp) = (vert-1) * 2 + (hor-1) * 2
void tmp_ring(char even, int *tmp, int **matrix, int matrix_rows, int matrix_columns, int vert, int hor)
{
    int startx, starty;
    if (even)
    {
        startx = (matrix_rows - hor) / 2;
        starty = (matrix_columns - vert) / 2;
    }
    else
    {
        startx = (matrix_rows - vert) / 2;
        starty = (matrix_columns - hor) / 2;
    }
    int off = 0;
    for (int i = 0; i < vert-1; ++i)
    {
        tmp[1+/*i*/off++] = matrix[starty + i][startx];
    }
    for (int i = 0; i < hor-1; ++i)
    {
        tmp[1+/*i+vert*/off++] = matrix[starty + vert-1][startx + i];
    }
    for (int i = vert-1; i > 0; --i)
    {
        tmp[1+off++] = matrix[starty + i][startx + hor-1];
    }
    for (int i = hor-1; i > 1; --i)
    {
        tmp[1+off++] = matrix[starty][startx + i];
    }
    tmp[0] = matrix[starty][startx + 1];
}

void reverse_tmp_ring(char even, int *tmp, int **matrix, int matrix_rows, int matrix_columns, int vert, int hor)
{
    int startx, starty;
    if (even)
    {
        startx = (matrix_rows - hor) / 2;
        starty = (matrix_columns - vert) / 2;
    }
    else
    {
        startx = (matrix_rows - vert) / 2;
        starty = (matrix_columns - hor) / 2;
    }
    int off = 0;
    for (int i = 0; i < vert-1; ++i)
    {
        matrix[starty + i][startx] = tmp[off++];
    }
    for (int i = 0; i < hor-1; ++i)
    {
        matrix[starty + vert-1][startx + i] = tmp[off++];
    }
    for (int i = vert-1; i > 0; --i)
    {
        matrix[starty + i][startx + hor-1] = tmp[off++];
    }
    for (int i = hor-1; i > 0; --i)
    {
        matrix[starty][startx + i] = tmp[off++];
    }
}

// Complete the matrixRotation function below.
void matrixRotation(int matrix_rows, int matrix_columns, int** matrix, int r) {
    char row_even = (matrix_rows <= matrix_columns) ? 1 : 0;
    if (row_even)
    {
        while (r-- > 0)
        {
            int top_center = (matrix_rows/2)-1;
            int bottom_center = top_center + 1;
            int smallest_loop_len = matrix_columns - top_center * 2;
            for (int gap = 0; gap <= matrix_rows - 2; gap += 2)
            {
                int vert = gap + 2;
                int hor = smallest_loop_len + gap;
                int tmp_len = (gap+1)*2 + (smallest_loop_len + gap-1)*2;
                int *tmp = (int*)malloc(sizeof(int) * tmp_len);
                tmp_ring(1, tmp, matrix, matrix_rows, matrix_columns, vert, hor);
                reverse_tmp_ring(1, tmp, matrix, matrix_rows, matrix_columns, vert, hor);
                free(tmp);
            }
        }
    }
    else
    {
        while (r-- > 0)
        {
            int top_center = (matrix_columns/2)-1;
            int bottom_center = top_center + 1;
            int smallest_loop_len = matrix_rows - top_center * 2;
            for (int gap = 0; gap <= matrix_columns - 2; gap += 2)
            {
                int hor = gap + 2;
                int vert = smallest_loop_len + gap;
                int tmp_len = (gap+1)*2 + (smallest_loop_len + gap-1)*2;
                int *tmp = (int*)malloc(sizeof(int) * tmp_len);
                tmp_ring(0, tmp, matrix, matrix_rows, matrix_columns, vert, hor);
                reverse_tmp_ring(0, tmp, matrix, matrix_rows, matrix_columns, vert, hor);
                free(tmp);
            }
        }
    }

    for (int y = 0; y < matrix_rows; ++y)
    {
        for (int x = 0; x < matrix_columns; ++x)
        {
            printf("%d ", matrix[y][x]);
        }
        printf("\n");
    }
}
