/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:21:30 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/07/19 15:21:32 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_stdin(void)
{
	char *in;
	char *c;

	c = ft_strnew(1);
	in = ft_strnew(0);
	while (read(0, c, 1))
	{
		in = ld_stradd(in, c);
		c = ft_strnew(1);
	}
	free(c);
	return (in);
}

void	run_hash(char *str)
{
	int		fd;
	char	*buf;
	char	*in;

	if (g_str)
	{
		g_str = false;
		g_dispatch[g_hash].func((unsigned char *)str);
		if (g_quiet || !g_rev)
			ft_printf("\n");
		return ;
	}
	fd = open(str, O_RDONLY);
	buf = ft_strnew(1);
	in = ft_strnew(0);
	while (read(fd, buf, 1))
	{
		in = ld_stradd(in, buf);
		buf = ft_strnew(1);
	}
	g_dispatch[g_hash].func((unsigned char *)in);
	free(in);
	free(buf);
	if (g_quiet || !g_rev)
		ft_printf("\n");
}
