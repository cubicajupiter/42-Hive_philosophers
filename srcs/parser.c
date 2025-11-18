/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:28:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/18 18:33:39 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_arg(const char *arg);
static int	ft_atoi(const char *str);
static bool	is_digit(const int c);

void	parse_args(int ac, char **av, t_state **state)
{
	int			data;
	int			i;

	i = 1;
	while (i < ac)
	{
		if (check_arg(av[i]) == EINVAL)
			exit_with_instructions(EINVAL);
		data = ft_atoi(av[i]);
		(*state)->init_data[i - 1] = data;
		i++;
	}
	if (ac == 5)
		(*state)->init_data[i - 1] = -1;
}

static int	check_arg(const char *arg)
{
	size_t		i;

	i = 0;
	while(arg[i])
	{
		if (!is_digit(arg[i]))
			return (EINVAL);
		i++;
	}
	return (SUCCESS);
}

static int	ft_atoi(const char *str)
{
	unsigned int		value;
	int					i;

	i = 0;
	value = 0;
	while (str[i])
	{
		value += str[i] - '0';
		if (str[i + 1])
			value *= 10;
		i++;
	}
	if (value > INT_MAX)
		exit_with_instructions(EINVAL);
	return ((int)value);
}

static bool	is_digit(const int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}
