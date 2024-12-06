#include "portscanner.h"

int     ip_check(const char* ip)
{
    //Եթե չկա 4 հատ ՛.՛, վերադարձնում ենք 1
    if (getwordcount_split(ip, '.') != 4)
    {
        putstr_fd(2, "Please read what is IP V4\n");
        return (1);
    }

    // Բաժանում ենք օկտետների, ու սկսում ենք հերթով ստուգել․ եթե ինչ որ մի օկտետ չի գտնվում 1-255 սահմանում, free ենք անում և վերադարձնում ենք 2
    char    **octets;
    int     i;

    octets = ft_split(ip, '.');
    i = 0;
    while(octets[i])
    {
        if(is_correct(octets[i], IP) == 0)
            i++;
        else
        {
            putstr_fd(2, "Please read what is IP V4\n");
            free_matrix(octets, 4);
            free(octets);
            return (2);
        }
    }

    // եթե ամեն ինչ նորմալ է, free ենք անում և վերադարձնում ենք 0
    free_matrix(octets, 4);
    free(octets);

    return (0);
}

int     is_correct (const char *str, enum type type)
{
    //Եթե չկա պորտը, վերադարձնում ենք 1
    if (!str || !*str)
        return 1;
    
    int i;
    i = 0;

    //Ցիկլով պտտվում ենք, որ տեսնենք արդյոք բոլոր char-երը թիվ են, եթե չէ, վերադարձնում ենք 2
    while (str[i] != '\0')
    {
        if (ft_isdigit(str[i]))
        {
            i++;
        }
        else
        {
            putstr_fd(2, "Number can be in range ");
            if (type == IP)
                putstr_fd(2, "0-255\n");
            else
                putstr_fd(2, "1-65535\n");
            return (2);
        }
    }

    //Ստուգում ենք, արդյոք գտնվում են 1-65535 -ի միջակայքում / 1-255 ի, եթե ip-ն ենք check անում
    int num;
    int max;

    num = ft_atoi(str);
    if (type == IP)
        max = 255;
    else if (type == PORT)
        max = 65535;
    if (num < 0 || num > max)
    {
        if (type == IP)
            putstr_fd(2, "IP octet can be in range 0-255\n");
        else
            putstr_fd(2, "Port scan area can be in range 1-65535\n");
        return (2);
    }
    return 0;
}

int check_arguments(int ac, char **av)
{
    if (ac < 2 || ac > 4)
    {
        putstr_fd(2, "Usage: IP {PORT} {END PORT}\n");
        return (1);
    }
    
    if (ip_check(av[1]) != 0)
        return (3);
    
    if (ac > 2 && ((av[2] && is_correct(av[2], PORT) != 0) || (av[3] && is_correct(av[3], PORT) != 0)))
        return (2);

    return (0);
}