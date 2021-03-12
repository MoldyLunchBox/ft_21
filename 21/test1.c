#include "./libft/libft.h"
#include "includes/monkey_head.h"

int		fd_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int		init_term3(t_core *core)
{
	int				ret;
	t_t				term;
	struct winsize	w;

	tcgetattr(0, &term.config);
	term.config.c_lflag &= ~( ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &term.config) == -1)
		return (-1);
	if (getenv("TERM") == NULL)
		return (0);
	ret = tgetent(NULL, getenv("TERM"));
	if (ret == (-1))
		return (0);
	else if (ret == 0)
		return (0);
	ioctl(0, TIOCGWINSZ, &w);
	term.win = w;
	core->term = term;
//	tputs(tgetstr("ti", NULL), 0, fd_putchar);
	return (1);
}

void        get_cur_position(void)
{
    char    buff[21];
    buff[20] = 0;
	int fd = open("/dev/tty", O_RDWR);
        ft_putstr_fd("\e[6n", fd);
        read(fd, buff, 20);
		ft_putchar('(');
		ft_putstr(buff);
		ft_putchar(')');

  //0  clean_posx_str(buff);
}

int main()
{
	t_core tt;

	init_term3(&tt);
	get_cur_position();
}
