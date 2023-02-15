#include "sshell.h"

void	*memcpy1(void *dst, const void *src, size_t n)
{
	size_t sn;

	sn = n;
	if (!dst && !src)
		return (NULL);
	if (src == dst)
		return (dst);
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (dst - sn);
}

char	*strjoin1(char const *s1, char const *s2)
{
	char	*ret;
	size_t	sumlen;

	if (!s1)
		return (NULL);
	sumlen = strlen1(s1) + strlen1(s2);
	if (!(ret = malloc(sizeof(char) * (sumlen + 1))))
		return (NULL);
	memcpy1(ret, s1, strlen1(s1));
	memcpy1(ret + strlen1(s1), s2, strlen1(s2));
	ret[sumlen] = 0;
	return (ret);
}

size_t	strlen1(const char *s)
{
	size_t len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

char    **env_var(t_envlist *environment)
{
    char **env;
    t_envlist *tmp;
    int i;

    tmp = environment;
    int len;
    while (tmp)
    {
        tmp = tmp->next;
        len++;
    }
    env = (char **)malloc(sizeof(char*) * (len + 1));
    /*111*/
    i = 0;
    while (environment)
    {
        env[i] = environment->name;
        environment = environment->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}