/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:08:32 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/17 17:25:44 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Libft/libft.h"

/*
** http://projet-moteur-3d.e-monsite.com/pages/raycasting/raycasting.html
** https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html
** https://user.oc-static.com/ftp/mateo21/sdlkeysym.html
**
** IMPORTANT: Event et EventMask: https://code.woboq.org/qt5/include/X11/X.h.html

** tuto raycasting: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
** code C tuto: http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=s3De
** https://lodev.org/cgtutor/raycasting.html
*/

/* Fonctions externes autorisées:
** -open, read, write, malloc, free, perror,
** strerror, exit
** -Toutes les fonctions de la lib math (-lm
** man man 3 math)
** -Toutes les fonctions de la MinilibX
http://www-igm.univ-mlv.fr/~berstel/Cours/Xlib/13-Evenements.pdf

textures: http://www.areyep.com/RIPandMCS-TextureLibrary-Walltextures.html
xpm converter: https://www.online-utility.org/image/convert/to/XPM


mlx_get_data_addr () returns information about the created image, allowing a user to modify it later.
The img_ptr parameter specifies the image to use. The three next parameters should be the  addresses of
three different valid integers.  bits_per_pixel will be filled with the number of bits needed to represent
a pixel color (also called the depth of the image).  size_line is the number of bytes used to store
one line of the image in memory.  This information is needed to move from one line to another in the image.
endian tells you wether the pixel color in the image needs to be stored in little endian ( endian
== 0), or big endian ( endian == 1).

mlx_get_data_addr  returns  a char * address that represents the begining of the memory area where the
image is stored. From this adress, the first bits_per_pixel bits represent the color of the first pixel
in the first line of the image. The second group of bits_per_pixel bits represent the second pixel of
the first line, and so on.  Add size_line to the adress to get the begining of the second line. You  can
reach any pixels of the image that way.
*/

# define BLUE 0x2CB4D5
# define GREEN 0x43D52C
# define RED 0xEB4006
# define YELLOW 0xE9F00F
# define PURPLE 0x8A1DC4
# define PINK 0xC41DB3

typedef struct	s_tex
{
	int			texture;
	int			color;
	int			width;
	int			height;
	char		*tex_path;
	void		*image;
	void		*img_ptr;
	int			bit_pix;
	int			size_line;
	int			endian;
}				t_tex;

typedef struct	s_cub3d
{
	char		**map;
	int			map_h;
	int			map_w;
	void		*mlx_ptr;
	void		*win_ptr;
	int			res_x;
	int			res_y;
	void		*image;
	void		*img_ptr;
	int			bit_pix;
	int			size_line;
	int			endian;
	int			map_x;
	int			map_y;
	double		pos_x;
	double		pos_y;		//x and y start position
	double		dir_x;
	double		dir_y;		//initial direction vector
	double		plane_x;
	double		plane_y;	//the 2d raycaster version of camera plane
	double		cam_plane;	//x-coordinate in camera space
    double		raydir_x;
    double		raydir_y;
	double		side_dx;	//length of ray from current position to next x or y-side
    double		side_dy;
    double		delta_dx;	//length of ray from one x or y-side to next x or y-side
	double		delta_dy;
    double		wall_dist;
    int			step_x;		//what direction to step in x or y-direction (either +1 or -1)
    int			step_y;
	int			wall_hit;	//was there a wall hit?
	int			side;		//was a NS or a EW wall hit?
	int			line_h;
	int			draw_start;
    int			draw_end;
	double		mov_speed;
	double		rot_speed;
	double		olddir_x;
	double		oldplane_x;
	int			up;
	int			down;
	int			left;
	int			right;
	t_tex		tex[7];
	double		wall_x;
	int			x_coor;
	int			y_coor;
	int			error;
	char		*err_message;
}				t_cub3d;

/*
** CREATE_MAP.C
*/
void			count_x(int fd, t_cub3d *cub);
void			create_map(int fd, t_cub3d *cub);
void			adjust_map(t_cub3d *cub);
void			complete_map(t_cub3d *cub);

/*
** CHECK_MAP.C
*/
void			check_map(t_cub3d *cub);

/*
** TEXTURES.C
*/
void			assign_tex(t_cub3d *cub, char *line, int i);
void			import_tex(t_cub3d *cub, int i);

/*
** INIT_VAR.C
*/
void			init_cub(t_cub3d *cub);
void			init_position(t_cub3d *cub);
void			init_direction(t_cub3d *cub);
void			init_plane(t_cub3d *cub);
void			init_var(t_cub3d *cub);

/*
** DRAWING.C
*/
void			draw_walls(t_cub3d *cub, int x);
void			draw_floor(t_cub3d *cub, int x);
void			draw_ceiling(t_cub3d *cub, int x);

/*
** SPRITE.C
*/
void			sprite(t_cub3d *cub, int x);

/*
** RAYCASTING.C
*/
void			raycasting(t_cub3d *cub);

/*
** ACTIONS.C
*/
int				press_key(int key, t_cub3d *cub);
int				real_key(int key, t_cub3d *cub);

/*
** MOTION.C
*/
int				motion(t_cub3d *cub);

int				exit_prog(void);

#endif
