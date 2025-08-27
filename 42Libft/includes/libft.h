/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:23:46 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/09 18:16:00 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/** 
 * @brief Converts a string to an integer.
 * 
 * This function parses the string "nptr" to convert it into an integer.
 * Handles leading whitespaces and optionals signs "+/-".
 * 
 * @param nptr Pointer to the string containing the number.
 * @return The converted integer value.
*/
int		ft_atoi(const char *nptr);

/**
 * @brief Sets "n" bytes of memory to zero.
 * 
 * This function writes zeros to the first "n" bytes of the memory area
 * pointed to by "src".
 * 
 * @param src Pointer to the memory area.
 * @param n Number of bytes to set to zero.
 */
void	ft_bzero(void *src, size_t n);

/**
 * @brief Allocates memory for an array and initializes it to zero.
 * 
 * This function allocates memory for an array of "nmemb" elements, each of
 * size "size", and initializes all bytes in the allocated memory to zero.
 * 
 * @param nmemb Number of elements in the array.
 * @param size Size of each element in bytes.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Checks if a character is alphanumeric.
 * 
 * Returns non-zero if the character "c" is a letter or a digit
 * otherwise, returns zero.
 * 
 * @param c Character to check (as an int).
 * @return Non-zero if alphanumeric, zero otherwise.
 */
int		ft_isalnum(int c);

/**
 * @brief Checks if a character is alphabetic.
 * 
 * Returns non-zero if the character "c" is a letter (uppercase or lowercase)
 * otherwise, returns zero.
 * 
 * @param c Character to check (as an int).
 * @return Non-zero if alphabetic, zero otherwise.
 */
int		ft_isalpha(int c);

/**
 * @brief Checks if a character is part of ASCII table.
 * 
 * Returns non-zero if the character "c" is in the ASCII range (0-127)
 * otherwise, returns zero.
 * 
 * @param c Character to check (as an int);
 * @return Non-zero if ASCII, zero otherwise.
 */
int		ft_isascii(int c);

/**
 * @brief Checks if a character is a digit (0-9).
 * 
 * Returns non-zero f the character "c" is a digit
 * otherwise returns zero.
 * 
 * @param c Character to check (as an int).
 * @return Non-zero if digit, zero otherwise.
 */
int		ft_isdigit(int c);

/**
 * @brief Checks if a character is printable.
 * 
 * Returns non-zero if the character "c" is printable (including space)
 * otherwise, returns zero.
 * 
 * @param c Character to check (as an int).
 * @return Non-zero if printable, zero otherwise.
 */
int		ft_isprint(int c);

/**
 * @brief Converts an integer to a string representation.
 * 
 * Allocates and returns a string representing the integer "n".
 * 
 * @param n Integer to convert to a string.
 * @return A pointer to the newly allocated string containing the number,
 * or NULL if allocations fails.
 */
char	*ft_itoa(int n);

/**
 * @brief Searches for a byte in memory block.
 * 
 * Searches for the first occurrence of byte "c" in the first "n" bytes of
 * memory block pointed by "s".
 * 
 * @param s Pointer to memory block to search within.
 * @param c Byte value to search for (converted to unsigned char).
 * @param n Number of bytes to search through.
 * @return A pointer to the matching byte, or NULL if not found within "n" bytes
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares two memory areas.
 * 
 * @param s1 Pointer to the first memory area.
 * @param s2 Pointer to the second memory area.
 * @param n Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if s1 is found
 * to be less than, to match, or be greater than s2.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 * 
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source mmoery area.
 * @param n Number of bytes to copy.
 * @return A pointer to dest.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copies n bytes from src to dest, handling overlapping memory.
 * 
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return A pointer to dest.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Fills the first n bytes of the memory area pointed to by dest with
 * the constant byte c.
 * 
 * @param dest Pointer to the memory area to be filled.
 * @param c The byte to fill the memory with.
 * @param count Number of bytes to fill.
 * @return A Pointer to the memory area dest.
 */
void	*ft_memset(void *dest, int c, size_t count);

/**
 * @brief Outputs the character c to the given file descriptor.
 * 
 * @param c The character to output.
 * @param fd The file descriptor to write to.
 * @return The number of characters written.
 */
int		ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string s to the given file descriptor,
 * followed by a newline.
 * 
 * @param s The string to output.
 * @param fd The file descriptor to write to.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Outputs the integer n to the given file descriptor.
 * 
 * @param n The integer to output.
 * @param fd The file descriptor to write to.
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * @brief Outputs the string s to the given file descriptor.
 * 
 * @param s The string to output.
 * @param fd The file descriptor to write to.
 * @return The number of characters written.
 */
int		ft_putstr_fd(char *s, int fd);

/**
 * @brief Splits a string into an array of strings using a delimiter character.
 * 
 * @param s The string to split.
 * @param c The delimiter character.
 * @return An array of new strings resulting from the split, or NULL if
 * allocation fails.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief Splits a string into an array of strings using a charset as a
 * delimiter.
 * 
 * @param s The string to split.
 * @param charset The string to use as a delimiter.
 * @return An array of new strings resulting from the split, or NULL if 
 * allocation fails.
 */
char	**ft_split_charset(char const *s, const char *charset);

/**
 * @brief Locates the first occurrence of c in the string pointed to by "str".
 * 
 * @param str The string to search.
 * @param c The character to search for.
 * @return A pointer to the located character, or NULL if not found.
 */
char	*ft_strchr(const char *str, int c);

/**
 * @brief Creates a duplicate of the string src.
 * 
 * @param src The string to duplicate.
 * @return A pointer to the duplicated string, or NULL if allocations fails.
 */
char	*ft_strdup(const char *src);

/**
 * @brief Creates a duplicate of the string src, but with only n bytes.
 * 
 * @param src The string to duplicate.
 * @param n The number of bytes to duplicate
 * @return A pointer to the duplicated string, or NULL if allocations fails.
 */
char	*ft_strndup(const char *src, size_t n);

/**
 * @brief Applies the function f to each character of the string s.
 * 
 * @param s The string to iterate over.
 * @param f The function to apply to each character.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief Concatenates two strings into a new string.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A new string that is the concatenation of s1 and s2,
 * or NULL if allocations fails.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Concatenates two strings into a new string.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param sep The separator char to put between them.
 * @return A new string that is the concatenation of s1 and s2 with sep between
 * them, or NULL if allocation fails.
 */
char	*ft_strcjoin(char const *s1, char const *s2, char sep);

/**
 * @brief Appends the NULL-terminated string src to the end of dst.
 * 
 * @param dest The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * @return The total length of the string it tried to create.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size);

/**
 * @brief Copies up to size - 1 characters from the NUL-terminated string src
 * to dst.
 * 
 * @param dest The destination string.
 * @param src The source string.
 * @param size The size of the destionation buffer.abort
 * @return The total length of the string it tried to create.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

/**
 * @brief Calculates the length of the string s.
 * 
 * @param s The string to measure.
 * @return The number of characters in s.
 */
size_t	ft_strlen(const char *s);

/**
 * @brief Applies the function f to each character of the string s to create a
 * new string.
 * 
 * @param s The string to map.
 * @param f The function to apply to each character.
 * @return A new string created by applying f to each character of s, or NULL
 * if allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Compares two strings
 * 
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 */
int		ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Compares the first n bytes of two strings.
 * 
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @param n The number of bytes to compare
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Locates the first occurrence of the NULL-terminated string "little" in
 * the string "big".
 * 
 * @param big The string to search within.
 * @param little The substring to search for.
 * @param len The maximum number of characters to search.
 * @return A pointer to the first character of the first occurrence of little
 * in big, or NULL if not found.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Locates the last occurrence of "c" in the string pointed to by "str".
 * 
 * @param str The string to search within.
 * @param c The character to search for.
 * @return A pointer to the located character, or NULL if not found.
 */
char	*ft_strrchr(const char *str, int c);

/**
 * @brief Removes the leading and trailing occurrences of characters in set from
 * string s1.
 * 
 * @param s1 The string to trim.
 * @param set The set if characters to trim.
 * @return A new trimmed string, or NULL if allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Extracts a substring fromt string s.
 * 
 * @param s The string to extract from.
 * @param start The start index of the substring in s.
 * @param len The maximum length of the substring.
 * @return A new string containing the extracted substring, or NULL if
 * allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Converts an uppercase letter to lowercase.
 * 
 * @param c The character to convert.
 * @return The converted character, or c if it's not a uppercase letter.
 */
int		ft_tolower(int c);

/**
 * @brief Converts a lowercase letter to uppercase.
 * 
 * @param c The character to convert.
 * @return The converted character, or c if it's not a lowercase letter.
 */
int		ft_toupper(int c);

/**
 * @brief Creates a new list node.
 * 
 * @param content The content to put in the new node.
 * @return The new node, or NULL if allocations fails.
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Adds the node "new" at the beginning of the list.
 * 
 * @param lst The adress of a pointer to the first node of a list.
 * @param new The adress of a pointer to the node to be added to the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Adds the node "new" at the end of the list.
 * 
 * @param lst The adress of a pointer to the first node of a list.
 * @param new The adress of a pointer to the node to be added to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Deletes and frees the given node and every successor of that node.
 * 
 * @param lst The adress of a pointer to a node.
 * @param del The adress of the function used to delete the content of the node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Takes as a parameter a node and frees the memory of the node's
 * content.
 * 
 * @param lst The node to free.
 * @param del The adress of the function used to delete the content.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Returns the last element of the list.
 * 
 * @param lst The beginning of the list.
 * @return The last element of the list.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Counts the number of nodes in a list.
 * 
 * @param lst The beginning of the list.
 * @return The length of the list.
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Iterates the list "lst" and applies the function "f" to the content of
 * each nodes.
 * 
 * @param lst The adress of a pointer to a node.
 * @param f The adress of the function used to iterate on the list.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Iterates the list "lst" and applies the function "f" toe the content
 * of each node.
 * Creates a new list resulting of the successive applications of "f".
 *
 * @param lst The adress of a pointer to an element.
 * @param f The adress of the function used to iterate on the list.
 * @param del The adress of the function used to delete the content of a
 * node if needed.
 * @return The new list, or NULL if allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif