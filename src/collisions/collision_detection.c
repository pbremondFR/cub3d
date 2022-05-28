/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:31:05 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/28 08:22:49 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

bool	c_is_tile_collider(const t_cub *c, int x, int y)
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

inline bool	c_is_tile_collider_pnt(const t_cub *c, t_pnt p)
{
	return (c_is_tile_collider(c, (int)p.x, (int)p.y));
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
	if (c_is_tile_collider_pnt(c, p_box->a))
		result |= 0b0001;
	if (c_is_tile_collider_pnt(c, p_box->b))
		result |= 0b0010;
	if (c_is_tile_collider_pnt(c, p_box->c))
		result |= 0b0100;
	if (c_is_tile_collider_pnt(c, p_box->d))
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

void	c_collision_handling_shit(t_game *g, float vel_x, float vel_y)
{
	t_box	p_box_1;
	t_box	p_box_2;
	// const char	collisions = c_bounds_check(&p_box_2, g->c);
	// int			i;

	p_box_1 = c_get_player_bounding_box(g->x, g->y);
	p_box_2 = c_get_player_bounding_box(g->x + vel_x, g->y + vel_y);

	if (vel_x > 0 && (c_is_tile_collider_pnt(g->c, p_box_2.b)
			|| c_is_tile_collider_pnt(g->c, p_box_2.d)))
	{
		// check and solve right side of hitbox
		g->x += (nearbyintf(p_box_2.b.x) - p_box_2.b.x);
		c_recalc_bounding_box(&p_box_2, g->x, g->y);
	}
	else if (vel_x < 0 && (c_is_tile_collider_pnt(g->c, p_box_2.a)
			|| c_is_tile_collider_pnt(g->c, p_box_2.c)))
	{
		// check and solve for left side
		g->x += (nearbyintf(p_box_2.a.x) - p_box_2.a.x);
		c_recalc_bounding_box(&p_box_2, g->x, g->y);
	}
	if (vel_y > 0 && (c_is_tile_collider_pnt(g->c, p_box_2.c)
			|| c_is_tile_collider_pnt(g->c, p_box_2.d)))
	{
		// check and solve for bottom side
		g->y += (nearbyintf(p_box_2.c.y) - p_box_2.c.y);
		c_recalc_bounding_box(&p_box_2, g->x, g->y);
	}
	else if (vel_y < 0 && (c_is_tile_collider_pnt(g->c, p_box_2.a)
			|| c_is_tile_collider_pnt(g->c, p_box_2.b)))
	{
		// check and solve for top side
		g->y += (nearbyintf(p_box_2.a.y) - p_box_2.a.y);
		c_recalc_bounding_box(&p_box_2, g->x, g->y);
	}
	// if (c_is_tile_collider_pnt(g->c, p_box_2.a))
	// 	ft_printf("A\t");
	// if (c_is_tile_collider_pnt(g->c, p_box_2.b))
	// 	ft_printf("B\t");
	// if (c_is_tile_collider_pnt(g->c, p_box_2.c))
	// 	ft_printf("C\t");
	// if (c_is_tile_collider_pnt(g->c, p_box_2.d))
	// 	ft_printf("D\t");
	// ft_printf("\n");
	g->x = p_box_2.pos.x;
	g->y = p_box_2.pos.y;
}

// ========================================================================== //
// ========================================================================== //
// ========================================================================== //

// Get distance between player's hitbox and wall in X and Y
t_pnt	c_get_AABB_dist(float pl_x, float pl_y, const t_pnt hbox,
	const t_ipair wall)
{
	t_pnt	dist;

	if (pl_x < (float)wall.a)
		dist.x = -(wall.a - (pl_x + hbox.x));
	else if (pl_x > (float)wall.a)
		dist.x = -((pl_x - hbox.x) - (wall.a + 1));
	else
		dist.x = 0;
	if (pl_y < (float)wall.b)
		dist.y = -(wall.b - (pl_y + hbox.y));
	else if (pl_y > (float)wall.b)
	{
		dist.y = -((pl_y - hbox.y) - (wall.b + 1));
		printf("EEEEELSE IF\n");
	}
	else
		dist.y = 0;
	printf("%s%.3f;%.3f%s\n", RED, dist.x, dist.y, RESET);
	return (dist);
}

t_pnt	c_get_closest_wall_dist(float pl_x, float pl_y, const t_pnt hbox,
	const t_ipair wall)
{
	t_pnt	w_dist;
	float	x1;
	float	x2;
	float	y1;
	float	y2;

	x1 = ((float)wall.a - (pl_x + hbox.x));
	x2 = ((pl_x - hbox.x) - (wall.a + 1));
	y1 = (wall.b - (pl_x + hbox.y));
	y2 = ((pl_y - hbox.y) - (wall.b + 1));
	printf("%.3f - %.3f ; %.3f - %.3f\n", x1, x2, y1, y2);
	w_dist.x = fminf(fabsf(x1), fabsf(x2));
	w_dist.y = fminf(fabsf(y1), fabsf(y2));
	return (w_dist);
}

bool	c_does_player_collide(float pl_x, float pl_y, t_pnt hbox, t_ipair wall)
{
	const float		offset = 0.0001f;
	const t_ipair	a = {pl_x - hbox.x + offset, pl_y - hbox.y + offset};
	const t_ipair	b = {pl_x + hbox.x - offset, pl_y - hbox.y + offset};
	const t_ipair	c = {pl_x - hbox.x + offset, pl_y + hbox.y - offset};
	const t_ipair	d = {pl_x + hbox.x - offset, pl_y + hbox.y - offset};

	return ((a.a == wall.a && a.b == wall.b)
		|| (b.a == wall.a && b.b == wall.b)
		|| (c.a == wall.a && c.b == wall.b)
		|| (d.a == wall.a && d.b == wall.b));
}

void	c_collision_handling(t_game *g, float vel_x, float vel_y)
{
	const t_pnt		hbox = {PLAYER_HBOX_HALFSIZE, PLAYER_HBOX_HALFSIZE};
	// const t_ipair	to_solve[] = {{g->x - 1, g->y - 1}, {g->x, g->y - 1},
	// {g->x + 1, g->y - 1}, {g->x - 1, g->y}, {g->x + 1, g->y},
	// {g->x - 1, g->y + 1}, {g->x, g->y + 1}, {g->x + 1, g->y + 1}};
	const t_ipair	to_solve[] = {
		{g->x, g->y - 1},
		{g->x - 1, g->y},
		{g->x + 1, g->y},
		{g->x, g->y + 1},
		{g->x - 1, g->y - 1},
		{g->x + 1, g->y - 1},
		{g->x - 1, g->y + 1},
		{g->x + 1, g->y + 1}
		};
	const t_uint	num_solve = 8;
	int				i;
	t_pnt			dist;
	t_pnt			pos = {g->x + vel_x, g->y + vel_y};

	for (i = 0; (unsigned int)i < num_solve; ++i)
		printf("to_solve[%d]: (%d;%d)\n", i, to_solve[i].a, to_solve[i].b);

	i = -1;
	while ((t_uint)++i < num_solve)
	{
		// If this tile isn't a wall, skip
		if (!c_is_tile_collider(g->c, to_solve[i].a, to_solve[i].b))
			continue ;
		printf("%s(%d;%d)\tCollider%s\n", YEL, to_solve[i].a, to_solve[i].b, RESET);
		// If player's box isn't in this tile, skip
		if (!c_does_player_collide(pos.x, pos.y, hbox, to_solve[i]))
			continue ;
		printf("%sCollision ! (%d)%s\n", GRN, i + 1, RESET);
		// dist = c_get_AABB_dist(pos.x, pos.y, hbox, to_solve[i]);
		dist = c_get_AABB_dist(pos.x, pos.y, hbox, to_solve[i]);
		if (dist.x < dist.y)
		{
			if (pos.x < to_solve[i].a)
				pos.x -= dist.x;
			else
				pos.x += dist.x;
			printf("XXXX\n");
		}
		// else if (dist.y < dist.x)
		else
		{
			if (pos.y < to_solve[i].b)
				pos.y -= dist.y;
			else
				pos.y += dist.y;
			printf("YYYY\n");
		}
		// if (to_solve[i].a != (int)pos.x)
		// 	pos.x += dist.x;
		// else if (to_solve[i].b != (int)pos.y)
		// 	pos.y += dist.y;
	}
	printf("======================\n");
	g->x = pos.x;
	g->y = pos.y;
}
