/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:36:03 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/05 20:17:01 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

int	main(int argc, const char *argv[])
{
	t_cub	*c;

	if (argc != 2)
	{
		ft_dprintf(2, "usage: %s map.cub\n", argv[0]);
		return (1);
	}
	c = c_parse_cub_file(argv[1]);
	if (c == NULL)
		return (1);
	int	tmp = c_map_error_check((const char **)c->map);
	if (tmp)
		return (tmp);
	c_map_print_error((const char **)c->map, UINT_MAX, UINT_MAX);
	if (c->f == -1)
		ft_printf("Floor color error\n");
	if (c->c == -1)
		ft_printf("Ceiling color error\n");
	ft_printf("F: %x-%x-%x\nC: %x-%x-%x\n",
		c->f >> 16, c->f >> 8 & 0xff, c->f & 0xff,
		c->c >> 16, c->c >> 8 & 0xff, c->c & 0xff);
	void	*mlx = mlx_init();
	void	*mlx_win = mlx_new_window(mlx, 720, 540, "Test");
	(void)mlx_win;
	mlx_loop(mlx);
	return (0);
}
