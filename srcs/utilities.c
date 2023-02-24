#include "../headers/minishell.h"

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_strlen(char *s)
{
	int	i;
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *) malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (dest == NULL)
		return (0);
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	if (str[i] == '\0')
		dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, unsigned int end)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	if (end >= ft_strlen(s))
		end = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str = (char *) malloc(sizeof(char) * (end - start + 1));
	if (str == 0)
		return (0);
	while (start <= end && s[start] != '\0')
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**realloc_append(char **src, char *str)
{
	int		i;
	int		len;
	char	**new;

	i = 0;
	len = 0;
	while (src[len] != NULL)
		len++;
	new = (char **) malloc (sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = ft_strdup(src[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free_2d_array(src);
	return (new);
}

