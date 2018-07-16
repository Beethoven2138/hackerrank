#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct _cache
{
	size_t num;
	double sqrt;
} SQRT_CACHE;

SQRT_CACHE *cache;
size_t cache_size;
size_t cache_index;

SQRT_CACHE *cache_init(int size)
{
	cache = (SQRT_CACHE*)malloc(size * sizeof(SQRT_CACHE));
	cache_size = size;
	cache_index = 0;
	return cache;
}

void cache_free(void)
{
	if (cache)
	{
		free(cache);
		cache = NULL;
	}
	cache_size = 0;
	cache_index = 0;
}

SQRT_CACHE *cache_expand(size_t amount)
{
	cache = realloc(cache, (cache_size + amount) * sizeof(SQRT_CACHE));
	cache_size += amount;
	return cache;
}

double sqrt_cache(size_t value)
{
	for (size_t i = 0; i < cache_size; ++i)
	{
		if (cache[i].num == value)
			return cache[i].sqrt;
	}
	double ret = 0;
	for (size_t num2 = (value > 0) ? value-1 : value; num2 <= value + 1; ++num2)
	{
		if (cache_index == cache_size)
	        {
        	        if (cache_expand(5) == NULL)
                	        return -1;
        	}
	        cache[cache_index].num = num2;
        	cache[cache_index].sqrt = sqrt((double)num2);
		if (num2 == value)
			ret = cache[cache_index].sqrt;
       		++cache_index;
	}
	return ret;
}

int main(void)
{
	cache_init(10);


	for (int i = 0; i <= 1000; ++i)
		printf("%d: %f\n", i, sqrt_cache(i));

	cache_free();
}
