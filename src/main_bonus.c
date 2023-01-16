/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:36:03 by pbremond          #+#    #+#             */
/*   Updated: 2023/01/14 20:10:38 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

t_game	*c_init_t_game(t_game *g)
{
	t_game	*game;

	if (g)
		game = g;
	else
		game = (t_game *)malloc(sizeof(t_game));
	if (game == NULL)
		return (NULL);
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
	g->sprts_lst = NULL;
	g->n_sprt = 0;
	g->t.tv_nsec = 0;
	g->t.tv_sec = 0;
	return (game);
}

static void	_fill_buffer_with_colour(t_img *img, t_uint colour)
{
	t_uint			*int_buf;
	t_uint			i;
	const t_uint	limit = img->h * (img->ls / 4);

	int_buf = (t_uint *)img->addr;
	i = 0;
	while (i < limit)
		int_buf[i++] = colour;
}

static void	_init_vars_and_hooks(t_game *g, t_cub *c)
{
	c_init_player_pos(g, c);
	if (g->x == 0.0f || g->y == 0.0f)
	{
		ft_dprintf(2, "Error\nMissing player start position\n");
		exit(1);
	}
	c_init_sprites_pos(g);
	c_init_doors(c);
	g->f.i = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->f.addr = mlx_get_data_addr(g->f.i, &g->f.bpp, &g->f.ls, &g->f.e);
	g->f.w = WIN_WIDTH;
	g->f.h = WIN_HEIGHT;
	g->olay.w = MINIMAP_WIDTH * MM_TIL_SIZ + (MM_BORD_SIZ * 2);
	g->olay.h = MINIMAP_HEIGHT * MM_TIL_SIZ + (MM_BORD_SIZ * 2);
	g->olay.i = mlx_new_image(g->mlx, g->olay.w, g->olay.h);
	g->olay.addr = mlx_get_data_addr(g->olay.i, &g->olay.bpp, &g->olay.ls,
			&g->olay.e);
	_fill_buffer_with_colour(&g->olay, 0xc0000000);
	c_load_font(g);
	mlx_hook(g->mw, E_KDWN, 0, &c_keypress_handler, g);
	mlx_hook(g->mw, E_KUP, 0, &c_keyrelease_handler, g);
	mlx_hook(g->mw, E_MPRESS, 0, &c_mousepress_handler, g);
	mlx_hook(g->mw, E_MREL, 0, &c_mouserelease_handler, g);
	mlx_hook(g->mw, E_DSTR, 0, &c_exit_program_hook, g);
	mlx_loop_hook(g->mlx, &c_render, g);
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
		exit(1);
	_init_vars_and_hooks(&g, &c);
	mlx_loop(g.mlx);
	return (0);
}
