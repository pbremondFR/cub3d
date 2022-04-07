/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:36:03 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/07 20:40:53 by pbremond         ###   ########.fr       */
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
	game->i.i = NULL;
	game->i.addr = NULL;
	game->c = NULL;
	return (game);
}

static void	_c_tests(t_cub const *c, t_game const *g)
{
	(void)g;
	c_map_print_error((const char **)c->map, UINT_MAX, UINT_MAX);
	if (c->f == -1)
		ft_printf("Floor color error\n");
	if (c->c == -1)
		ft_printf("Ceiling color error\n");
	ft_printf("F: %x-%x-%x\nC: %x-%x-%x\n",
		c->f >> 16 & 0xff, c->f >> 8 & 0xff, c->f & 0xff,
		c->c >> 16 & 0xff, c->c >> 8 & 0xff, c->c & 0xff);
	ft_printf("Map length: %d\nMap height: %d\n", c->sx, c->sy);
}

void	c_init_player_pos(t_game *g, t_cub *c)
{
	int	i;
	int	j;
	int	done;

	done = 0;
	i = 0;
	while (c->map[i] && !done)
	{
		j = 0;
		while (c->map[i][j] && !done)
		{
			if (ft_strchr("NESW", c->map[i][j]))
			{
				g->x = j + 0.5f;
				g->y = i + 0.5f;
				done = 1;
			}
			j++;
		}
		i++;
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
	if (c_parse_cub_file(argv[1], &c) == NULL || c_init_t_game(&g) == NULL
		|| c_map_error_check((const char **)c.map) != EXIT_SUCCESS)
		return (1);
	_c_tests(&c, &g);
	g.c = &c;
	c_init_player_pos(&g, &c);
	g.mlx = mlx_init();
	g.mw = mlx_new_window(g.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	g.i.i = mlx_new_image(g.mlx, WIN_WIDTH, WIN_HEIGHT);
	g.i.addr = mlx_get_data_addr(g.i.i, &g.i.bpp, &g.i.ls, &g.i.e);
	mlx_hook(g.mw, E_KDWN, 0, &c_keypress_handler, &g);
	mlx_hook(g.mw, E_KUP, 0, &c_keyrelease_handler, &g);
	mlx_loop_hook(g.mlx, &c_render, &g);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, g.i.i);
	mlx_loop(g.mlx);
	return (0);
}
