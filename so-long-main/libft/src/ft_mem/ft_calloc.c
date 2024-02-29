/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:15:08 by afavier           #+#    #+#             */
/*   Updated: 2023/11/15 13:06:50 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	size_t	sz;
	size_t	i;

	sz = 0;
	i = 0;
	sz = nmemb * size;
	if ((sz == 0) || sz / nmemb != size)
	{
		tab = malloc(0);
		return (tab);
	}
	tab = malloc(sz);
	if (!tab)
		return (NULL);
	while (i < sz)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}
