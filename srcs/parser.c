/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:28:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/12 12:42:03 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopers.h"

void	parse_args(int ac, char **av) //insert in struct
{
	t_states	state;
	int			data;
	int			i;

	i = 0;
	while (i < ac)
	{
		data = ft_atoi(av[i]);
		state->data[i] = data;
		i++;
	}
	if (ac == 5)
		state->data[i] = 0;
	return (&state);
}
