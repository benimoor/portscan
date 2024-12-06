#include "portscanner.h"

void    putstr_fd(const int fd, const char *str)
{
    write(fd, str, ft_strlen(str));
}

void    free_matrix(char **matrix, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        free(matrix[i]);
        ++i;
    }
}

int get_thread_count( void )
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

size_t	ft_strcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	x;

	srclen = ft_strlen(src);
	x = 0;
	if (dstsize == 0)
		return (srclen);
	while (x < (dstsize - 1) && src[x])
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = '\0';
	return (srclen);
}

size_t	ft_strcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	src1;
	size_t	x;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	src1 = dstlen;
	x = 0;
	if (dstsize == 0)
		return (srclen);
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	while (x < (dstsize - src1 - 1) && src[x])
	{
		dst[dstlen] = src[x];
		x++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (src1 + srclen);
}

void	print_open_port (const int port)
{
	char	*port_t;
	char	*port_n;
	char	*open_t;
	char	*res;

	port_t = "PORT \033[32m";
	port_n = ft_itoa(port);
	open_t = "\033[0m OPEN\n";

	res = malloc(ft_strlen(port_t) + ft_strlen(port_n) + ft_strlen(open_t) + 1);
	res[ft_strlen(port_t) + ft_strlen(port_n) + ft_strlen(open_t)] = 0;

	ft_strcpy(res, port_t, 50);
	ft_strcat(res, port_n, 50);
	ft_strcat(res, open_t, 50);

	putstr_fd(1, res);
	
	free(port_n);
	free(res);
}

int	ft_atoi(const char *str)
{
	int	is_negative;
	int	res;

	res = 0;
	is_negative = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		is_negative *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * is_negative);
}

static size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	n /= 10;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str_num;
	size_t		digits;
	long int	num;

	num = n;
	digits = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	str_num = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str_num)
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str_num + 0) = '-';
	return (str_num);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

	str = (char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	ft_isdigit(int x)
{
	if (x >= '0' && x <= '9')
		return (1);
	return (0);
}