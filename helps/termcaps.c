#include "../../includes/shell.h"

int		ft_writestdin(int c)
{
	write(0, &c, 1);
	return (0);
}


int		main()
{
	int				success;
	int				x;
	size_t			buf_size;
	char			line;
	char			*tmp;
	char			*input;
	struct termios	term;
	struct termios	old;
	char			*termtype;

	x = 0;
	if (!(termtype = getenv("TERM")))
		return (ft_printf("Error TERM doesnt exist\n"));
	if (0 > (success = tgetent(0, termtype)))
		return (ft_printf("Error couldnt access termcap data base\n"));
	if (!success)
		ft_printf("Terminal type %s not defined\n", termtype);
	if (tcgetattr(0, &old) == -1)
		return (-1);
	buf_size = 1024;
	if (!(input = ft_memalloc(1024)))
		return (0);
	input[12239] = 123;
	term.c_lflag &= ~(ICANON); // canonique form
	term.c_lflag &= ~(ECHO); // echoing form
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	while (1)
	{
		if (ft_strlen(input) == buf_size - 1)
		{
			if (!(tmp = ft_memalloc(buf_size + 1024)))
				return (0);
			ft_memcpy(tmp, input, buf_size);
			ft_memdel((void **)&input);
			buf_size += 1024;
			input = tmp;
		}
		read(0, &line, 1);
		if (line == 4 && !input[0])
		{
			tputs(tgetstr("do", 0), 1, ft_writestdin);
			write(0, "\rQuiting\n\r", 10);
			break ;
		}
		else if (line == 12)
		{
			tputs(tgetstr("cl", 0), 1, ft_writestdin);
		}
		else if (line == 27)
		{
			read(0, &line, 1);
			if (line == 91)
			{
				read(0, &line, 1);
				if (line == 68 && x)
				{
					x -= 1;
					tputs(tgetstr("le", 0), 1, ft_writestdin);
				}
				else if (line == 67 && input[x])
				{
					x += 1;
					tputs(tgetstr("nd", 0), 1, ft_writestdin);
				}
				else if (line == 72)
				{
					tputs(tgetstr("cr", 0), 1, ft_writestdin);
					x = 0;
				}
				else if (line == 70)
				{
					while (input[x])
					{
						tputs(tgetstr("nd", 0), 1, ft_writestdin);
						x += 1;
					}
				}
				else if (line == 51)
				{
					read(0, &line, 1);
					if (line == 126)
					{
						ft_memmove(input + x, input + x + 1, ft_strlen(input + x + 1) + 1);
						tputs(tgetstr("dc", 0), 1, ft_writestdin);
					}
				}
				else if (line == 49)
				{
					read(0, &line, 1);
					if (line == 59)
					{
						read(0, &line, 1);
						if (line == 53)
						{
							read(0, &line, 1);
							if (line == 68)
							{
								while (x)
								{
									x -= 1;
									tputs(tgetstr("le", 0), 1, ft_writestdin);
									if (x && !(ft_isalnum(input[x - 1])) && ft_isalnum(input[x]))
										break ;
								}
							}
							else if (line == 67)
							{
								while (input[x])
								{
									x += 1;
									tputs(tgetstr("nd", 0), 1, ft_writestdin);
									if (input[x] && !(ft_isalnum(input[x - 1])) && ft_isalnum(input[x]))
										break ;
								}
							}
						}
					}
				}
			}
		}
		else if (line == 4)
		{
			ft_memmove(input + x, input + x + 1, ft_strlen(input + x + 1) + 1);
			tputs(tgetstr("dc", 0), 1, ft_writestdin);
		}
		else if (line == 127 && x)
		{
			x -= 1;
			ft_memmove(input + x, input + x + 1, ft_strlen(input + x + 1) + 1);
			tputs(tgetstr("le", 0), 1, ft_writestdin);
			tputs(tgetstr("dc", 0), 1, ft_writestdin);
		}
		else if (line == 13 || line == 3)
		{
			tputs(tgetstr("do", 0), 1, ft_writestdin);
			write(0, "\rinput :", 9);
			write(0, input, ft_strlen(input));
			write(0, "\n\r", 2);
			x = 0;
			ft_bzero(input, buf_size);
		}
		else if (line > 31 && line < 127)
		{
			tputs(tgetstr("im", 0), 1, ft_writestdin);
			ft_writestdin(line);
			ft_memmove(input + x + 1, input + x, ft_strlen(input + x) + 1);
			input[x++] = line;
			tputs(tgetstr("ei", 0), 1, ft_writestdin);
		}
	}
	// QUIT
	if (tcsetattr(0, TCSANOW, &old) == -1)
		return (-1);
	ft_printf("\ninput :%s|\n", input);
	ft_memdel((void **)&input);
	return (0);
}
