/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 22:24:46 by cpaquet           #+#    #+#             */
/*   Updated: 2017/09/05 09:00:20 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrev(char *str)
{
	int		i;
	int		n;
	char	t;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	i = i - 1;
	while (n < i)
	{
		t = str[i];
		str[i] = str[n];
		str[n] = t;
		i--;
		n++;
	}
	return (str);
}