/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:07:22 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/16 16:40:15 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init(t_cub3d *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->image = NULL;
	cub->img_ptr = NULL;
	cub->c_spr = NULL;
	ft_memset(&cub->buf, 0, sizeof(t_buf));
	ft_memset(&cub->map, 0, sizeof(char**));
	ft_memset(&cub->act, 0, sizeof(t_action));
	ft_memset(&cub->tex, 0, sizeof(t_tex) * 7);
	ft_memset(&cub->flr, 0, sizeof(t_floor));
	ft_memset(&cub->spr, 0, sizeof(t_sprite));
}

static void	set_buffer(int fd, t_cub3d *cub)
{
	char	*line;
	int		ret;

	cub->buf.content = ft_strdup("");
	while ((ret = get_next_line(fd, &line)))
	{
		cub->buf.content = ft_strjoin_free(cub->buf.content, line, 2);
		cub->buf.content = ft_strjoin_free(cub->buf.content, "\n", 1);
	}
	cub->buf.content = ft_strjoin_free(cub->buf.content, line, 2);
}

void		init_desc(t_cub3d *cub, char *desc)
{
	int		fd;

	init(cub);
	if ((fd = open(desc, O_RDONLY)) < 0)
	{
		close(fd);
		display_error(cub, "Could not find map description.\n");
	}
	set_buffer(fd, cub);
	cub->buf.buffer = ft_split_nl(cub->buf.content);
	close(fd);
}
