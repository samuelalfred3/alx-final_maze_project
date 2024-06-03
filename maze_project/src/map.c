#include <stdio.h>
#include <string.h>
#include "../inc/config.h"
#include "../inc/game.h"

char map[MAP_HEIGHT][MAP_WIDTH + 1];

/**
 * load_map - Load the map from a file.
 * @filename: The name of the file containing the map.
 */
void load_map(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Could not open map file %s\n", filename);
		return;
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		if (fgets(map[i], MAP_WIDTH + 2, file) == NULL)
		{
			fprintf(stderr, "Error reading map file %s\n", filename);
			fclose(file);
			return;
		}
		/* Remove newline character if present */
		map[i][strcspn(map[i], "\n")] = '\0';
	}

	fclose(file);
}

