
#include "fdf.h"

static int		ft_rank(int nb)
{
	int i;

	i = 0;
	while (nb > 1)
	{
		nb /= 10;
		i++;
	}
	return (i + 1);
}

/* Affiner cette fonction*/
static int		ft_lin_is_good(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != ' '))
			return (0);
		i++;
	}
	return (1);
}

static int		ft_add_list(char *str, t_list **list, int y)
{
	int i;
	int nb;
	int x;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			nb = ft_atoi(str + i);
			ft_add(x, y, nb, list);
			i += ft_rank(nb);
			x++;
		}
	}
	return (x);
}

static void		ft_open(char *str, t_list **list, t_parse *parse)
{
	int 	fd;
	int 	y;
	char	*lin;
	int		x;

	y = 0;
	if (((fd = open(str, O_RDONLY))) == -1)
	{
		ft_putstr_fd("can't open files\n", 2);
		exit(1);
	}
	while (get_next_line(fd, &lin) > 0)
	{
		if (!ft_lin_is_good(lin))
		{
			free(lin);
			close(fd);
			// free la liste
			ft_putstr("fsdfsdf\n");
			exit(0);
		}
		x = ft_add_list(lin, list, y);
		parse->nb_elem_line = (x > parse->nb_elem_line) ? x : parse->nb_elem_line;
		free(lin);
		y++;
	}
	parse->nb_line = y;
	close(fd);
}

int		ft_parse(char *str, t_list **list, t_parse *parse)
{
	int len;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	ft_open(str, list, parse);
	return (1);
}