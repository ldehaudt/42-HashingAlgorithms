/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:08:23 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/07/19 15:08:31 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

bool	check_file(char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory\n",
		g_dispatch[g_hash].name, str);
		g_count++;
		return (false);
	}
	return (true);
}

void	run_next_cont(char *str)
{
	if (g_rev)
	{
		if (!g_str && check_file(str) == 0)
			return ;
		if (g_str)
		{
			run_hash(str);
			ft_printf(" \"%s\"\n", str);
		}
		else
		{
			run_hash(str);
			ft_printf(" %s\n", str);
		}
		g_count++;
		return ;
	}
	if (!g_str && check_file(str) == 0)
		return ;
	if (g_str)
		ft_printf("%s (\"%s\") = ", g_dispatch[g_hash].out_str, str);
	else
		ft_printf("%s (%s) = ", g_dispatch[g_hash].out_str, str);
	run_hash(str);
	g_count++;
}

void	run_next_str(char *str)
{
	if (!g_str && g_flag && flag_check(str) == 1)
		return ;
	g_flag = false;
	g_print = true;
	if (g_stdin)
	{
		str = read_stdin();
		ft_printf("%s", str);
		g_dispatch[g_hash].func((unsigned char *)str);
		free(str);
		g_stdin = false;
		ft_printf("\n");
		return ;
	}
	if (g_quiet)
	{
		if (!g_str && check_file(str) == 0)
			return ;
		run_hash(str);
		g_count++;
		return ;
	}
	run_next_cont(str);
}

void	startup(int ac, char **av)
{
	if (ac == 1)
	{
		ft_printf("usage: ft_ssl command [command opts] [command args]");
		exit(0);
	}
	while (g_dispatch[g_hash].name != NULL &&
	ft_strcmp(g_dispatch[g_hash].name, av[1]))
	{
		g_hash++;
	}
	if (g_dispatch[g_hash].name == NULL)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n\
Message Digest commands:\nmd5\nsha256\n", av[1]);
		exit(0);
	}
}

int		main(int ac, char **av)
{
	char *str;

	g_count = 2;
	g_flag = true;
	g_quiet = false;
	g_rev = false;
	g_stdin = false;
	g_str = false;
	g_print = false;
	g_hash = 0;
	startup(ac, av);
	while (g_count < ac)
		run_next_str(av[g_count]);
	if (g_print == false)
	{
		str = read_stdin();
		if (g_stdin)
			ft_printf("%s", str);
		g_dispatch[g_hash].func((unsigned char *)str);
		free(str);
		ft_printf("\n");
	}
}
