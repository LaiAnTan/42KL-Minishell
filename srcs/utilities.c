#include "minishell.h"

void	free_2d_array(char **a)
{
	int	i;

	i = 0;
	while (a[i] != NULL)
		free(a[i++]);
	free(a);
}

int	ft_strlen(char *s)
{
	int	i;
	i = 0;
	while (s[i++] != '\0') {}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	i = -1;
	if (!s)
		return (0);
	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s) || !len)
		return (ft_strdup(""));
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	while (++i < len && s[start] != '\0')
	{
		str[i] = s[start];
		start++;
	}
	str[i] = '\0';
	return (str);
}