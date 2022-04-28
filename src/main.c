/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:36:03 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/28 22:17:07 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

t_game	*c_init_t_game(t_game *g)
{
	t_game	*game;

	if (g)
		game = g;
	else
		game = (t_game *)malloc(sizeof(t_game));
	if (game == NULL)
		return (NULL);
	game->x = 0.5f;
	game->y = 0.5f;
	game->dx = 0.0f;
	game->dy = -1.0f;
	game->cx = 0.66f;
	game->cy = 0.0f;
	game->vx = 0.0f;
	game->vy = 0.0f;
	game->va = 0.0f;
	game->k = 0;
	game->mlx = NULL;
	game->mw = NULL;
	game->f.i = NULL;
	game->f.addr = NULL;
	game->c = NULL;
	game->m_cap = 0;
	return (game);
}

static void	_debug_tests(t_cub const *c, t_game const *g)
{
	(void)g;
	c_map_print_error((const char **)c->map, UINT_MAX, UINT_MAX);
	if (c->f == -1)
		ft_printf("Floor color error\n");
	if (c->c == -1)
		ft_printf("Ceiling color error\n");
	printf("F: %2X-%2X-%2X\nC: %2X-%2X-%2X\n",
		c->f >> 16 & 0xff, c->f >> 8 & 0xff, c->f & 0xff,
		c->c >> 16 & 0xff, c->c >> 8 & 0xff, c->c & 0xff);
	ft_printf("Map length: %d\nMap height: %d\n", c->sx, c->sy);
}

// TESTME: What to do when changing FOV, or aspect ratio of window ?
static void	_set_player_direction(const char c, t_game *g)
{
	const float	fov = PLAYER_FOV;

	if (c == 'N' || c == 'S')
	{
		g->dx = 0.0f;
		if (c == 'N')
			g->dy = -1.0f;
		else
			g->dy = 1.0f;
		g->cx = -g->dy * fov;
		g->cy = g->dx;
	}
	else if (c == 'E' || c == 'W')
	{
		if (c == 'E')
			g->dx = 1.0f;
		else
			g->dx = -1.0f;
		g->dy = 0.0f;
		g->cx = -g->dy;
		g->cy = g->dx * fov;
	}
}

void	c_init_player_pos(t_game *g, t_cub *c)
{
	int	i;
	int	j;
	int	done;

	done = 0;
	i = -1;
	while (c->map[++i] && !done)
	{
		j = -1;
		while (c->map[i][++j] && !done)
		{
			if (ft_strchr("NESW", c->map[i][j]))
			{
				g->x = j + 0.5f;
				g->y = i + 0.5f;
				_set_player_direction(c->map[i][j], g);
				done = 1;
			}
		}
	}
}

int	main(int argc, const char *argv[])
{
	t_cub	c;
	t_game	g;

	if (argc != 2)
	{
		ft_dprintf(2, "usage: %s map.cub\n", argv[0]);
		return (1);
	}
	if (c_init_t_game(&g) == NULL)
		return (1);
	g.mlx = mlx_init();
	g.mw = mlx_new_window(g.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	g.c = &c;
	if (c_parse_cub_file(argv[1], &c, &g) == NULL
		|| c_map_error_check((const char **)c.map) != EXIT_SUCCESS)
		return (1);
	_debug_tests(&c, &g);
	c_init_player_pos(&g, &c);
	g.f.i = mlx_new_image(g.mlx, WIN_WIDTH, WIN_HEIGHT);
	g.f.addr = mlx_get_data_addr(g.f.i, &g.f.bpp, &g.f.ls, &g.f.e);
	g.f.w = WIN_WIDTH;
	g.f.h = WIN_HEIGHT;
	// mlx_put_image_to_window(g.mlx, g.mw, g.f.i, 0, 0);
	mlx_hook(g.mw, E_KDWN, 0, &c_keypress_handler, &g);
	mlx_hook(g.mw, E_KUP, 0, &c_keyrelease_handler, &g);
	mlx_hook(g.mw, E_DSTR, 0, &c_exit_program, &g);
	mlx_loop_hook(g.mlx, &c_render, &g);
	mlx_loop(g.mlx);
	return (0);
}
