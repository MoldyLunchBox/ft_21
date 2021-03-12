#include "libft/libft.h"

void	handle_quotes(char c, int *balance)
{
	if (c == '\"' && *balance == 0)
		*balance = 2;
	else if (c == '\'' && *balance == 0)
		*balance = 1;
	else if (c == '\"' && *balance == 2)
		*balance = 0;
	else if (c == '\'' && *balance == 1)
		*balance = 0;
}
int     check_quotes(char *str)
{
    int i;
    int balance;
    
    i = 0;
    balance = 0;
    ft_strdel(&str);
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
            handle_quotes(str[i], &balance);
        i++;
    }
    return (balance);
}
int     main()
{
    char    *input;
    char    *temp;
    char    *tmp;
    int     i;

    input = NULL;
    temp = NULL;
    tmp = NULL;
    while (1)
    {
        ft_putstr("$> ");
        get_next_line(0, &input);
        while ((i =check_quotes(input)))
        {
            if (i == 1)
                ft_putstr("squote> ");
            else
                ft_putstr("dquote> ");
            temp = ft_strjoin(input, "\n");
            ft_strdel(&input);
            get_next_line(0, &tmp);
            input = ft_strjoin(temp, tmp);
            ft_strdel(&temp);
            ft_strdel(&tmp);
        }
        ft_putstr("Line is : ");
        ft_putendl(input);
    }
}