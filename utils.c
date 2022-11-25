int		contain_alnum(const void *str)
{
	size_t	i;
	char	*s;

	s = (char*)str;
	if (!str)
		return (0);
	i = 0;
	while(s[i])
	{
		if (ft_isalnum(s[i]))
			return (1);
		++i;
	}
	return (0);
}

size_t	array_len(const char **str)

{
	size_t	len;
	
	if (!str)
		return (0);
	len = 0;
	while (str[len])
		++len;
	return (len);
}

char	**array_dub(const char **str, t_data *data)
{
	char	**ret;
	size_t	i;
	size_t	len;

	len = array_len(str);
	ret = cub_malloc(sizeof(char *) * (len + 1), data);
	i = 0;
	while(str[i])
	{
		ret[i] = cub_strdup(str[i], data);
		++i;
	}
	ret[i] = NULL;
	return (ret);
}