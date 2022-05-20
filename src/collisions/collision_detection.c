/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:31:05 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/21 00:21:15 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

bool	c_collision_check(const t_cub *c, int x, int y)
{
	const char	tile = c->map[y][x];
	t_door		*door;

	if (ft_strchr("0abcd", tile) && tile != '\0')
		return (false);
	else if (tile == '1')
		return (true);
	else if (tile == '-' || tile == '|')
	{
		door = c_get_door(c->doors, c->n_doors, x, y);
		if (door->state == DOOR_OPENED)
			return (false);
		else
			return (true);
	}
	else
		return (true);
}

inline bool	c_collision_check_pnt(const t_cub *c, t_pnt p)
{
	return (c_collision_check(c, (int)p.x, (int)p.y));
}

t_box	c_get_player_bounding_box(float x, float y)
{
	t_box	box;

	box.pos.x = x;
	box.pos.y = y;
	{
		box.a.x = x - PLAYER_HBOX_HALFSIZE;
		box.a.y = y - PLAYER_HBOX_HALFSIZE;
	}
	{
		box.b.x = x + PLAYER_HBOX_HALFSIZE;
		box.b.y = y - PLAYER_HBOX_HALFSIZE;
	}
	{
		box.c.x = x - PLAYER_HBOX_HALFSIZE;
		box.c.y = y + PLAYER_HBOX_HALFSIZE;
	}
	{
		box.d.x = x + PLAYER_HBOX_HALFSIZE;
		box.d.y = y + PLAYER_HBOX_HALFSIZE;
	}
	return (box);
}

t_box	*c_recalc_bounding_box(t_box *box, float new_x, float new_y)
{
	t_pnt			offset;
	t_pnt *const	points[] = {&box->a, &box->b, &box->c, &box->d, NULL};
	unsigned int	i;

	offset.x = new_x - box->pos.x;
	offset.y = new_y - box->pos.y;
	box->pos.x = new_x;
	box->pos.y = new_y;
	i = 0;
	while (points[i] != NULL)
	{
		points[i]->x += offset.x;
		points[i]->y += offset.y;
		++i;
	}
	return (box);
}

char	c_bounds_check(const t_box *p_box, const t_cub *c)
{
	char	result;

	result = 0;
	if (c_collision_check_pnt(c, p_box->a))
		result |= 0b0001;
	if (c_collision_check_pnt(c, p_box->b))
		result |= 0b0010;
	if (c_collision_check_pnt(c, p_box->c))
		result |= 0b0100;
	if (c_collision_check_pnt(c, p_box->d))
		result |= 0b1000;
	return (result);
}

void	c_solve_collision(t_game *g, t_pnt pnt, t_box *box)
{
	t_pnt	offset;

	(void)g;
	offset.x = nearbyintf(pnt.x) - pnt.x;
	offset.y = nearbyintf(pnt.y) - pnt.y;
	if (fabsf(offset.x) < fabsf(offset.y))
	{
		box->pos.x += offset.x;
	}
	else
	{
		box->pos.y += offset.y;
	}
	c_recalc_bounding_box(box, box->pos.x, box->pos.y);
}

void	c_collision_handling(t_game *g, float vel_x, float vel_y)
{
	t_box	p_box_1;
	t_box	p_box_2;
	// const char	collisions = c_bounds_check(&p_box_2, g->c);
	// int			i;

	p_box_1 = c_get_player_bounding_box(g->x, g->y);
	p_box_2 = c_get_player_bounding_box(g->x + vel_x, g->y + vel_y);
	if (c_collision_check_pnt(g->c, p_box_2.a))
		c_solve_collision(g, p_box_2.a, &p_box_2);
	if (c_collision_check_pnt(g->c, p_box_2.b))
		c_solve_collision(g, p_box_2.b, &p_box_2);
	if (c_collision_check_pnt(g->c, p_box_2.c))
		c_solve_collision(g, p_box_2.c, &p_box_2);
	if (c_collision_check_pnt(g->c, p_box_2.d))
		c_solve_collision(g, p_box_2.d, &p_box_2);
	g->x = p_box_2.pos.x;
	g->y = p_box_2.pos.y;
}
