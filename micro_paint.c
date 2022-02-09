#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>


typedef struct s_rect {
	int height;
	int width;
	float r_h;
	float r_w;
	char background;
	char asset;
	char type;
	float x;
	float y;
} t_rect;

int check_data(t_rect *rect) {
	if (rect->height == 0 || rect->height > 300 || rect->width == 0 || rect->width > 300)
		return 0;
	return 1;
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
	FILE* fd;
	if (argc <= 1) {
		printf("Error:argumrents\n");
	}
	else {
		fd = fopen(argv[1], "r");
		if (fd == NULL)
			printf("Error: open1\n");
		count = fscanf(fd, "%d %d %c\n", &rect.height, &rect.width, &rect.background);
		if (!check_data(&rect))
		{
			printf("Error:open2\n");
			fclose(fd);
		}
		tab = draw(&rect);
		while(1) {
			count = fscanf(fd, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.r_h, &rect.r_w, &rect.asset);
			if (count == -1)
				break;
			if (count != 6)
			{
				printf("Error:open3\n");
				fclose(fd);
			}
		}
		i = 0;
		while(tab[i]) {
			printf("%s\n", tab[i++]);
		}
	}
}
