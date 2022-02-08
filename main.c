#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

typedef struct s_circle
{
	char background;
	int width;
	int height;
	char type;
	char draw;
	float X;
	float Y;
	float r;
} t_circle;

int in_circle(int x, int y, t_circle *circle)
{
	float distance;

	distance = sqrtf(powf((float)x - circle->X, 2.) + powf((float)y - circle->Y, 2.));
	if (distance > circle->r)
		return (0);
	if (circle->type == 'c' && circle->r - distance < 1.0)
		return (2);
	return (1);
}

int check_data(int w, int h)
{
	if (w == 0 || w > 300 || h == 0 || h > 300)
		return (0);
	return (1);
}

void draw_background(t_circle *circle)
{
	int i;
	int j;

	i = 0;
	while (i < circle->height)
	{
		j = 0;
		while (j < circle->width)
		{
			if (in_circle(i, j, circle))
			{
				printf("%c", circle->draw);
			}
			else
				printf("%c", circle->background);
			j++;
		}
		// if (in_circle(i, j, circle))
		// 	printf("%c", circle->draw);
		printf("\n");
		i++;
	}
}

char **draw(t_circle *circle)
{
	char **tab;
	int i;
	int j;

	tab = malloc(sizeof(char *) * circle->height + 1);
	i = 0;
	while (i < circle->height)
	{
		j = 0;
		tab[i] = malloc(sizeof(char) * circle->width + 1);
		while (j < circle->width)
		{
			tab[i][j] = circle->background;
			j++;
		}
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = NULL;
	return tab;
}

int main(int argc, char **argv)
{
	t_circle circle;
	char **tab;
	int i, j;

	if (argc <= 1)
	{
		printf("Error: argument\n");
		return (1);
	}
	FILE *fd = fopen(argv[1], "r");
	if (fd == NULL)
	{
		printf("Error: Operation file corrupted\n");
		return (1);
	}
	else
	{
		int count = fscanf(fd, "%d %d %c\n", &circle.width, &circle.height, &circle.background);
		if (!check_data(circle.width, circle.height))
		{
			
			return 1;
		}
		tab = draw(&circle);
		while (1)
		{
			count = fscanf(fd, "%c %f %f %f %c\n", &circle.type, &circle.X, &circle.Y, &circle.r, &circle.draw);
			if (count == -1)
				break;
			if (count != 5)
			{
				printf("Error: Operation file corrupted\n");
				return (1);
			}
			if (circle.r <= 0)
			{
				fclose(fd);
				return (1);
			}
			i = 0;
			while (i < circle.height)
			{
				j = 0;
				while (j < circle.width)
				{
					if (in_circle(j, i, &circle) == 2)
						tab[i][j] = circle.draw;
					else if (in_circle(j, i, &circle) == 1 && circle.type == 'C')
						tab[i][j] = circle.draw;
					j++;
				}
				i++;
			}
		}
		i = 0;
		while (tab[i])
		{
			printf("%s\n", tab[i]);
			i++;
		}
	}
	fclose(fd);
}