/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:32:15 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/03/11 13:30:55 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function ft_realloc reallocates memory for a given pointer with a new
 * size and copies the existing data if necessary.
 * 
 * @param ptr The `ptr` parameter in the `ft_realloc` function represents a
 * pointer to the memory block that needs to be reallocated. This pointer
 * points to the start of the memory block that was previously allocated
 * using `malloc`, `calloc`, or `realloc`.
 * @param len The `len` parameter in the `ft_realloc` function represents the
 * length of the data that you want to copy from the existing memory block
 * pointed to by `ptr` to the newly allocated memory block. It is used in the
 * `ft_memcpy` function to copy `len` bytes of data
 * @param size The `size` parameter in the `ft_realloc` function represents the
 * new size in bytes that you want to allocate for the memory block pointed
 * to by `ptr`. This parameter determines the total size of the memory block
 * after reallocation.
 * 
 * @return The function `ft_realloc` returns a pointer to the newly allocated
 * memory block, or NULL if the allocation fails.
 */
void	*ft_realloc(void *ptr, size_t len, size_t size)
{
	void	*new;

	if (size == 0)
		return (NULL);
	new = malloc(size);
	if (!new)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new, ptr, len);
		free(ptr);
	}
	return (new);
}
