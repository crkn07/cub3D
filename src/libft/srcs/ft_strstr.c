/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:18:18 by crtorres          #+#    #+#             */
/*   Updated: 2024/02/28 16:21:03 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function ft_strstr searches for the first occurrence of a substring within
 * a string and returns a pointer to the beginning of the substring if found.
 * 
 * @param haystack The `haystack` parameter is a pointer to a character array
 * that represents the string in which you want to search for the
 * `needle` string.
 * @param needle The `needle` parameter in the `ft_strstr` function is a 
 * pointer to a null-terminated string that represents the substring we are 
 * searching for within the `haystack` string.
 * 
 * @return The function `ft_strstr` returns a pointer to the first occurrence of
 * the `needle` string within the `haystack` string. If the `needle` string
 * is not found within the `haystack` string, the function returns `NULL`.
 */
char	*ft_strstr(char *haystack, char *needle)
{
	char	*h;
	char	*n;

	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*haystack && *n && *haystack == *n)
		{
			haystack++;
			n++;
		}
		if (!*n)
			return (h);
		haystack = h + 1;
	}
	return (NULL);
}
