#include "portscanner.h"

typedef struct
{
    const char *ip;
    int start_port;
    int end_port;
    int thread_id;
    int total_threads;
} ThreadData;

void *scan_ports_thread(void *arg)
{
    ThreadData *data    = (ThreadData *)arg;
    const char *ip      = data->ip;
    int thread_id       = data->thread_id;
    int total_threads   = data->total_threads;
    int start_port      = data->start_port;
    int end_port        = data->end_port;

    struct sockaddr_in  dest;

    ft_memset(&dest, 0, sizeof(dest));
    dest.sin_family     = AF_INET;

    if (inet_pton(AF_INET, ip, &dest.sin_addr) <= 0)
    {
        putstr_fd(2, "Error converting target IP to binary\n");
        pthread_exit(NULL);
    }

    for (int port = start_port + thread_id; port <= end_port; port += total_threads)
    {
        dest.sin_port = htons(port);

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            putstr_fd(2, "Socket creation failed");
            continue;
        }

        int flags = fcntl(sock, F_GETFL, 0);
        fcntl(sock, F_SETFL, flags | O_NONBLOCK);

        int con = connect(sock, (struct sockaddr *)&dest, sizeof(dest));
        if (con < 0 && errno == EINPROGRESS) {
            fd_set writefds;
            struct timeval tv;

            FD_ZERO(&writefds);
            FD_SET(sock, &writefds);
            tv.tv_sec = 0;
            tv.tv_usec = 100000; // Timeout in microseconds (10 ms)

            if (select(sock + 1, NULL, &writefds, NULL, &tv) > 0)
            {
                int         optval;
                socklen_t   optlen;
                
                optlen = sizeof(optval);
                
                if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &optval, &optlen) == 0 && optval == 0)
                    print_open_port(port);

            }
        }
        else if (con == 0)
            print_open_port(port);
        close(sock);
    }

    pthread_exit(NULL);
}

int scan_ports(int ac, char **av)
{
    const char *ip;
    int st_port;
    int end_port;
    int thread_count;

    ip = av[1];
    thread_count = get_thread_count() * 32;

    if (ac > 3)
    {
        st_port = ft_atoi(av[3]);
        end_port = (ac == 5) ? ft_atoi(av[4]) : st_port;
    }
    else
    {
        st_port = 1;
        end_port = 65535;
    }

    pthread_t threads[thread_count];
    ThreadData thread_data[thread_count];

    for (int i = 0; i < thread_count; i++)
    {
        thread_data[i].ip = ip;
        thread_data[i].start_port = st_port;
        thread_data[i].end_port = end_port;
        thread_data[i].thread_id = i;
        thread_data[i].total_threads = thread_count;

        if (pthread_create(&threads[i], NULL, scan_ports_thread, &thread_data[i]) != 0)
        {
            putstr_fd(2, "Thread creation failed");
            return (1);
        }
    }

    for (int i = 0; i < thread_count; i++)
        pthread_join(threads[i], NULL);

    return (0);
}