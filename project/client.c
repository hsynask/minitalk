/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasik <hasik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:27:12 by hasik             #+#    #+#             */
/*   Updated: 2023/01/28 15:38:45 by hasik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	send_to_server(int *s, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (s[i] == 0)
			kill(pid, SIGUSR1);
		else if (s[i] == 1)
			kill(pid, SIGUSR2);
		usleep(250);
		i++;
	}
}

void	sig_back(int signal, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	(void)signal;
	(void)siginfo;
	ft_putstr("SINGAL SENT\n");
}

int	main(int ac, char **av)
{
	int					sid;
	struct sigaction	act;
	int					*arr;
	int					i;

	i = 0;
	sid = ft_atoi(av[1]);
	if (ac != 3)
		return (0);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_back;
	sigaction(SIGUSR2, &act, NULL);
	ft_putstr("SENDING TO : ");
	ft_putnbr(sid);
	ft_putstr("\n");
	while (av[2][i])
	{
		arr = convert_binary((unsigned char)av[2][i]);
		send_to_server(arr, sid);
		i++;
	}
}
