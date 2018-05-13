#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct _word
{
	char dir;//1 == vertical, 0 == horizontal
	int startx, starty;
	int len;
} WORD;

WORD words[10];
int word_cnt;

char free_words[10]; //1 if free

int min_free_word(void)
{
	for (int i = 0; i < word_cnt; ++i)
	{
		if (free_words[i] == 1)
			return i;
	}
	return -1;
}

int next_free_word(int cur)
{
	for (cur = cur + 1; cur < word_cnt; ++cur)
	{
		if (free_words[cur] == 1)
			return cur;
	}
	return -1;
}

char fits(int word, int cur_line, char *grid, char *word_list)
{
	char dir = words[cur_line].dir;
	int points[10];
	int point_iter = 0;
	if (((strlen(&word_list[word * 10]) > 10) ? 10 : strlen(&word_list[word * 10])) != words[cur_line].len)
		goto exit;
	if (words[cur_line].dir == 1)
	{
		for (int y = words[cur_line].starty; y < words[cur_line].starty + words[cur_line].len; ++y)
		{
			char c = grid[y * 10 + words[cur_line].startx];
			if (c != 0 && c != word_list[word * 10 + y - words[cur_line].starty])
				goto exit;
			if (c == 0)
			{
				points[point_iter] = y - words[cur_line].starty;
				++point_iter;
			}
			grid[y * 10 + words[cur_line].startx] = word_list[word * 10 + y - words[cur_line].starty];
		}
	}
	else
	{
		for (int x = words[cur_line].startx; x < words[cur_line].startx + words[cur_line].len; ++x)
		{
			char c = grid[words[cur_line].starty * 10 + x];
			if (c != 0 && c != word_list[word * 10 + x - words[cur_line].startx])
				goto exit;
			if (c == 0)
			{
				points[point_iter] = x - words[cur_line].startx;
				++point_iter;
			}
			grid[words[cur_line].starty * 10 + x] = word_list[word * 10 + x - words[cur_line].startx];
		}
	}
	free_words[word] = 0;
	for (int i = min_free_word(); i != -1; i = next_free_word(i))
	{
		if (fits(i, cur_line + 1, grid, word_list))
			return 1;
	}
	if (min_free_word() == -1)
		return 1;
exit:
	free_words[word] = 1;
	if (dir == 1)
	{
		for (int i = 0; i < point_iter; ++i)
		{
			int y = words[cur_line].starty + points[i];
			grid[y * 10 + words[cur_line].startx] = 0;
		}
	}
	else
	{
		for (int i = 0; i < point_iter; ++i)
		{
			int x = words[cur_line].startx + points[i];
			grid[words[cur_line].starty * 10 + x] = 0;
		}
	}
	return 0;
}


void print_grid(char *grid)
{
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			printf("%c", grid[y * 10 + x]);
		}
		printf("\n");
	}
}

void fill_words(char *grid)
{
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (grid[y * 10 + x] == '-' || grid[y * 10 + x] == 0)
			{
				words[word_cnt].startx = x;
				words[word_cnt].starty = y;
				int len = 0;
				if (x < 9 && grid[y * 10 + x + 1] == '-')
				{
					words[word_cnt].dir = 0;
					for (int i = x; i < 10 && (grid[y * 10 + i] == '-' || grid[y * 10 + i] == 0); ++i)
					{
						++len;
						grid[y * 10 + i] = 0;
					}
				}
				else if (y < 9 && grid[(y+1) * 10 + x] == '-')
				{
					words[word_cnt].dir = 1;
					for (int i = y; y < 10 && (grid[i * 10 + x] == '-' || grid[i * 10 + x] == 0); ++i)
					{
						++len;
						grid[i * 10 + x] = 0;
					}
				}
				else if (grid[y * 10 + x] == '-')
				{
					len = 1;
				}
				words[word_cnt].len = len;
				if (len > 0)
					++word_cnt;
			}
		}
	}
}

int main() {

	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	char grid[100];
	char words[100];
	char c;
	memset(free_words, 1, 10);
	memset(words, 0, 100);
	for (int i = 0; i < 10; i++)
	{
		scanf("%s", &grid[i * 10]);
	}
	char tmp[100];
	scanf("%s", tmp);
	int global_pos = 0;

	for (int i = 0; i < 10 && global_pos < 100; i++)
	{
		int local = 0;
		while (tmp[global_pos] != 0 && tmp[global_pos] != ';')
		{
			words[i * 10 + local++] = tmp[global_pos++];
		}
		while (global_pos < 100 && tmp[global_pos] == 0 || tmp[global_pos] == ';')
		{
			++global_pos;
		}
	}
    
	fill_words(grid);
    
	for (int i = 0; i < word_cnt; ++i)
	{
		if (fits(i, 0, grid, words))
		{
			print_grid(grid);
			return 0;
		}
	}
    
	return 0;
}
