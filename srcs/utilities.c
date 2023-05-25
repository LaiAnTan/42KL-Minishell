#include "../headers/minishell.h"

void	free_2d_array(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	(*arr) = NULL;
}

int	is_numeric(char *str)
{
	while (*str != '\0')
		if ((*str < '0' || *str > '9') && str++)
			return (0);
	return (1);
}

int	count_double(char **e)
{
	int	i;

	i = 0;
	while (e[i])
		++i;
	return (i);
}

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	// maybe i should include a failswitch as well~
	if (!s1 || !s2)
		return (!(!s1 && !s2));
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

int	ft_strcmp_equals(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '=' && s2[i] != '=')
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
	if (str == NULL)
		return NULL;
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
	if (!s && start > end)
		return (0);
	if (end >= (unsigned int) ft_strlen(s))
		end = ft_strlen(s);
	if (start >= (unsigned int) ft_strlen(s))
		return (ft_strdup(""));
	str = (char *) malloc(sizeof(char) * ((end - start) + 2));
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
	free_2d_array(&src);
	return (new);
}

char	*ft_append(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s1 != NULL)
	{
		while (s1[j] != '\0')
			temp[i++] = s1[j++];
	}
	if (s2 != NULL)
	{
		while (*s2 != '\0')
			temp[i++] = *s2++;
	}
	temp[i] = '\0';
	free(s1);
	return (temp);
}