/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:28:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 17:57:34 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	parse_args(int ac, char **av, t_state **state)
{
	int			data;
	size_t		i;

	i = 0;
	while (i < ac)
	{
		if (screen_arg(av[i]) == EINVAL)
			exit_with_instructions(EINVAL);
		data = ft_atoi(av[i]);
		(*state)->data[i] = data;
		i++;
	}
	if (ac == 5)
		(*state)->data[i] = -1;
}

int	screen_arg(char *arg)
{
	size_t		i;

	i = 0;
	while(arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (EINVAL);
		i++;
	}
	return (SUCCESS);
}
