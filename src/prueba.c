void	ft_dda_data(t_game *g)
{
	g->map_x = (int)g->pos.x;
	g->map_y = (int)g->pos.y;
	g->delta_dist.x = 1e30;
	if (g->delta_dist.x != 0)
		g->delta_dist.x = fabs(1.0 / g->ray.x);
	g->delta_dist.y = 1e30;
	if (g->delta_dist.y != 0)
		g->delta_dist.y = fabs(1.0 / g->ray.y);
	g->step_x = 1;
	if (g->ray.x < 0)
	{
		g->step_x = g->step_x * -1;
		g->side_dist.x = (g->pos.x - g->map_x) * g->delta_dist.x;
	}
	else
		g->side_dist.x = (g->map_x + 1.0 - g->pos.x) * g->delta_dist.x;
	g->step_y = 1;
	if (g->ray.y < 0)
	{
		g->step_y = g->step_y * -1;
		g->side_dist.y = (g->pos.y - g->map_y) * g->delta_dist.y;
	}
	else
		g->side_dist.y = (g->map_y + 1.0 - g->pos.y) * g->delta_dist.y;
}

void	ft_dda(t_game *g)
{
	int	hit;

	ft_dda_data(g);
	hit = 0;
	while (!hit)
	{
		if (g->side_dist.x < g->side_dist.y)
		{
			g->side_dist.x += g->delta_dist.x;
			g->map_x += g->step_x;
			g->side = X;
		}
		else
		{
			g->side_dist.y += g->delta_dist.y;
			g->map_y += g->step_y;
			g->side = Y;
		}
		printf("mapx es %d y mapy es %d\n", g->map_x, g->map_y);
		if (g->map[g->map_x][g->map_y] == 1)
			hit = 1;
	}
	if (g->side == X)
		g->perp_wall_dist = (g->side_dist.x - g->delta_dist.x);
	else
		g->perp_wall_dist = (g->side_dist.y - g->delta_dist.y);
}

nt	ft_color(t_game *g)
{
	int	color;

	color = 0;
	if (g->side == 0 && g->ray.x > 0)
		color = *(g->n_addr->mlx_addr + (g->mlx_x * g->texy + g->texx));
	else if (g->side == 0 && g->ray.x < 0)
		color = *(g->s_addr->mlx_addr + (g->mlx_x * g->texy + g->texx));
	else if (g->side == 1 && g->ray.y > 0)
		color = *(g->w_addr->mlx_addr + (g->mlx_x * g->texy + g->texx));
	else if (g->side == 1 && g->ray.y < 0)
		color = *(g->e_addr->mlx_addr + (g->mlx_x * g->texy + g->texx));
	return (color);