#include "cub3D.h"

// Նախաբաննա սկզբանավորումա պարսերը և խաղի կառուցվածքները, բացումա ֆայլը
int	init_parser_and_game(const char *path, t_parser *p, t_game *game)
{
	p->line = NULL;
	p->len = 0;
	p->map_lines = NULL;
	p->map_count = 0;
	p->in_map = 0;
	if (!path || !game)
	{
		fprintf(stderr, "Error\nparse_game: invalid arguments\n");
		return (0);
	}
	p->f = fopen(path, "r");
	if (!p->f)
	{
		fprintf(stderr, "Error\nparse_game: failed to open file %s\n", path);
		return (0);
	}
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	return (1);
}

// Կարդում է բոլոր ֆայլի տողերը և մշակում դրանք
int	read_file_lines(t_parser *p, t_game *game)
{
	p->rd = getline(&p->line, &p->len, p->f);
	if (!read_lines(p, game))
	{
		fclose(p->f);
		free(p->line);
		free_str_array(p->map_lines);
		fprintf(stderr, "Error\nparse_game: read_lines failed\n");
		return (0);
	}
	free(p->line);
	fclose(p->f);
	return (1);
}

// Ստեղծում է քարտեզի մատրիցը հավաքված տողերից
int	setup_map(t_parser *p, t_game *game)
{
	if (p->map_count == 0)
	{
		free_str_array(p->map_lines);
		fprintf(stderr, "Error\nparse_game: no map data found\n");
		return (0);
	}
	game->map.grid = p->map_lines;
	game->map.height = p->map_count;
	compute_map_width(p, game);
	return (1);
}

// Վավերացնում է բոլոր պարսված խաղի տվյալները (տեքստուրաներ և քարտեզ)
int	validate_game_data(t_game *game)
{
	if (!validate_textures(&game->textures))
	{
		fprintf(stderr, "Error\nparse_game: texture validation failed\n");
		return (0);
	}
	if (!validate_map(&game->map))
	{
		fprintf(stderr, "Error\nparse_game: map validation failed\n");
		return (0);
	}
	return (1);
}

// Կարդում է ֆայլը և վավերացնում բոլոր տվյալները
int	read_and_validate(t_parser *p, t_game *game)
{
	if (!read_file_lines(p, game))
		return (0);
	if (!setup_map(p, game))
		return (0);
	if (!validate_game_data(game))
		return (0);
	return (1);
}

// Հիմնական ֆունկցիա՝ .cub ֆայլը վերածում է `t_game` կառուցվածքի
int	parse_game(const char *path, t_game *game)
{
	t_parser	p;

	if (!init_parser_and_game(path, &p, game))
		return (0);
	if (!read_and_validate(&p, game))
		return (0);
	return (1);
}
