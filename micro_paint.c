#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>


typedef struct s_rect {
	int height;
	int width;
	float r_h;
	float r_w;
	float Xbr;
	float Ybr;
	char background;
	char asset;
	char type;
	float x;
	float y;
} t_rect;

void	ft_free(char **tab) {
	int i = 0;
	while (tab[i]) {
		free(tab[i]);
		i++;
	}
	free(tab);
}

int check_data(t_rect *rect) {
	if (rect->height > 0 && rect->height <=300 && rect->width > 0 && rect->width <= 300)
		return 1;
	return 0;
}

void	get_corner(t_rect *rect) {
	rect->Xbr = rect->x + rect->r_w;
	rect->Ybr = rect->y + rect->r_h;
}

int	in_rectangle(int x, int y, t_rect *rect) {
	get_corner(rect);

	if ((rect->x <= x && x <= rect->Xbr) && (rect->y <= y && y <= rect->Ybr)) {
		if ((x - rect->x < 1.0 || rect->Xbr - x < 1.0 || y - rect->y < 1.0 || rect->Ybr - y < 1.0) && rect->type == 'r')
			return (2);
		else if (rect->type == 'R')
			return (1);
	}
	return (0);
}

char**	draw(t_rect *rect){
	int i = 0;
	int j;
	char **tab;

	tab = malloc(sizeof(char *) * (rect->height + 1));
	while (i < rect->height) {
		j = 0;
		tab[i] = malloc(sizeof(char) * (rect->width + 1));
		while(j < rect->width) {
			tab[i][j] = rect->background;
			j++;
		}
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = NULL;
	return tab;
}

int main(int argc, char **argv) {
	int i,j;
	char **tab;
	char count;
	t_rect rect;
	FILE* fd = NULL;
	if (argc <= 1) {
		printf("Error: argumrents\n");
	}
	else {
		fd = fopen(argv[1], "r");
		if (fd == NULL)
		{
			printf("Error: Operation file corrupted\n");
			return (1);
		}
		count = fscanf(fd, "%d %d %c\n", &rect.width, &rect.height, &rect.background);
		if (!check_data(&rect))
		{
			printf("Error: Operation file corrupted\n");
			fclose(fd);
			return (1);
		}
		tab = draw(&rect);
		while(1) {
			count = fscanf(fd, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.r_w, &rect.r_h, &rect.asset);
			if (count == -1)
				break;
			if (count != 6 || (rect.type != 'r' && rect.type != 'R') || rect.r_h <= 0 || rect.r_w <= 0)
			{
				printf("Error: Operation file corrupted\n");
				fclose(fd);
				return (1);
			}
			i = 0;
			while(i < rect.height)
			{
				j = 0;
				while(j < rect.width)
				{
					if (in_rectangle(j, i, &rect) == 2)
						tab[i][j] = rect.asset;
					else if (in_rectangle(j, i, &rect) == 1)
						tab[i][j] = rect.asset;
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
	fclose(fd);
}
// printf("Xbr = %f Ybr = %f\nx = %f y = %f\n", rect.Xbr, rect.Ybr, rect.x, rect.y);
