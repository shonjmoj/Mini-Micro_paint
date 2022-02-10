#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_circle {
	int height;
	int width;
	float x;
	float y;
	float r;
	char background;
	char asset;
	char type;
} t_circle;

int	check_data(t_circle *circle){
	if (circle->height > 0 && circle->height <= 300 && circle->width > 0 && circle->width <= 300)
		return (1);
	return(0);
}

void	ft_free(char **tab) {
	int i = 0;
	while (tab[i]) {
		free(tab[i]);
		i++;
	}
	free(tab);
}

int in_circle(int x, int y, t_circle *circle) {
	float distance;

	distance = sqrtf(powf((float)x - circle->x, 2.) + powf((float)y - circle->y, 2.));
	if (distance > circle->r)
		return (0);
	else if (circle->r - distance < 1.0)
		return (2);
	return (1);
}

char**	draw(t_circle *circle) {
	int i = 0;
	int j;
	char **tab;

	tab = malloc(sizeof(char *) * (circle->height + 1));
	while(i < circle->height) {
		j = 0;
		tab[i] = malloc(sizeof(char) * (circle->width + 1));
		while(j < circle->width) {
			tab[i][j] = circle->background;
			j++;
		}
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int main(int argc, char **argv)
{
	int i,j;
	char **tab;
	t_circle circle;
	FILE *fd;
	int count;
	if (argc <= 1)
		printf("Error:argument\n");
	else {
		fd = fopen(argv[1], "r");
		if (fd == NULL) {
			printf("Error:open\n");
		}
		else {
			count = fscanf(fd,"%d %d %c\n", &circle.height, &circle.width, &circle.background);
			if (!check_data(&circle))
			{
				fclose(fd);
				return (1);
			}
			tab = draw(&circle);
			while(1)
			{
				count = fscanf(fd ,"%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.r, &circle.asset);
				if (count == -1)
					break;
				if (count != 5)
				{
					printf("Error:open\n");
					fclose(fd);
				}
				if (circle.r <= 0 || !(circle.type == 'c' || circle.type == 'C'))
				{
					fclose(fd);
					return (1);
				}
				i = 0;
				while(i < circle.height)
				{
					j = 0;
					while(j < circle.width) {
						if (in_circle(j, i ,&circle) == 2)
							tab[i][j] = circle.asset;
						else if (in_circle(j , i, &circle) && circle.type == 'C')
							tab[i][j] = circle.asset;
						j++;
					}
					i++;
				}
			}
			i = 0;
			while(tab[i]) {
				printf("%s\n", tab[i++]);
			}
			ft_free(tab);
		}
	} 
}

