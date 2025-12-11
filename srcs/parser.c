/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:28:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 13:45:51 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		check_arg(const char *arg);
static uint64_t	ft_atoi(const char *str);
static bool		is_digit(const int c);

uint8_t	init_parsed_args(int ac, char **av, t_state *state)
{
	uint64_t	data;
	int			i;

	i = 1;
	while (i < ac)
	{
		if (check_arg(av[i]) == EINVAL)
			return (clean(state, EINVAL, (int []){0, PARSE}));
		data = ft_atoi(av[i]);
		if (data == 0)
			return (clean(state, EINVAL, (int []){0, PARSE}));
		if (i == 1 && data > 1000)
			return (clean(state, EINVAL, (int []){0, PARSE}));
		if (data > INT_MAX)
			return (clean(state, EINVAL, (int []){0, PARSE}));
		state->init_data[i - 1] = (int)data;
		i++;
	}
	if (ac == 5)
		state->init_data[i - 1] = -1;
	return (SUCCESS);
}

static int	check_arg(const char *arg)
{
	size_t		i;

	i = 0;
	while (arg[i])
	{
		if (!is_digit(arg[i]))
			return (EINVAL);
		i++;
	}
	if (i > 10)
		return (EINVAL);
	return (SUCCESS);
}

static uint64_t	ft_atoi(const char *str)
{
	uint64_t			value;
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
	return (value);
}

static bool	is_digit(const int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}
