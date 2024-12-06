#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>
#include <pthread.h>

enum type{IP, PORT};

int     scan_ports(int ac, char **av);


void    putstr_fd(const int fd, const char *str);
void    free_matrix(char **matrix, int len);
int     get_thread_count( void );
int	    ft_atoi(const char *str);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t len);
int     ft_isdigit(int x);
void	print_open_port (const int port);


int     is_correct (const char *str, enum type type);
int     ip_check(const char* ip);
int     check_arguments(int ac, char **av);

char	**ft_split(char const *s, char c);
size_t	getwordcount_split(char const *s, char c);