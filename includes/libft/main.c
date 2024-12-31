#include "libft.h"

typedef struct data
{
    void *t, *a, *b;
    char **s;
} data;

int main()
{
    data *d = track_alloc(1*sizeof(*d));
    d->a = track_alloc(1*sizeof(void*));
    d->b = track_alloc(1000*sizeof(void*));
    d->t = track_alloc(5*sizeof(void*));
    int *i = track_alloc(10*sizeof(int));
    d->s = track_alloc(10*sizeof(char *));
    for (int k = 0; k < 10; k++)
        d->s[k] = track_alloc( 10*sizeof(char));
    for(int j = 0;j < 10;j++)
        i[j] = j;

    for(int j = 0;j < 10;j++)
        printf("%d\n",i[j]);
    free_alloc(get_instance());
    return 0;
}