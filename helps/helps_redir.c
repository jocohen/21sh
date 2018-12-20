void	test(t_alloc al)
{
	char	*s;
	char	*file;
	int		fd_redir;
	int		fd_to_save;
	int		fd_file;
	int		redir_mode;
	int 	x;
	int		y;
	char	**cmd;

	x = 0;
	fd_file = 0;
	fd_redir = 1;
	s = al.input->s;

	// CHECK INPUT

	while (s[x] && s[x] != '>' && s[x] != '<')
		x += 1;
	if (!s[x])
		return ;
	if (s[x] == '>')
	{
		if (s[x + 1] == '>')
			redir_mode = 2;
		else
			redir_mode = 1;
	}
	else if (s[x] == '<')
		redir_mode = 0;
	(s[x - 1] == '&' || s[x + 1] == '&') ? redir_mode += 10 : 0;
	if (s[x] == '<')
		fd_redir = 0;
	y = x;
	(x) ? y -= 1 : 0;

	// CHECK FOR FD

	while (y && s[y] >= '0' && s[y] <= '9')
		y -= 1;
	if (s[y] == ' ' && s[y + 1] >= '0' && s[y + 1] <= '9')
		fd_redir = ft_atoi(s + y + 1);
	y = x + 1;

	(redir_mode == 2 || s[y] == '&') ? y += 1 : 0;
	while (s[y] && s[y] == ' ')
		y += 1;
	(redir_mode == 1 && s[y] == '|') ? y += 1 : 0;
	file = s + y;
	if (s[y] != '-')
	{
		while (s[y])
		{
			if (!ft_isdigit(s[y]))
				(redir_mode >= 10) ? redir_mode -= 10 : 0;
			y += 1;
		}
	}
	(s[y] == '-') ? redir_mode = -1 : 0;

	// OPEN FILE SUIVANT MODE

	if (redir_mode == 2)
		fd_file = open(file, O_WRONLY | O_APPEND | O_CREAT);
	else if (redir_mode == 1)
		fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!redir_mode)
		fd_file = open(file, O_RDONLY);
	else if (redir_mode >= 10 && ft_atoi(file) > 2)
		fd_file = ft_atoi(file);
	if (fd_file == -1)
		return ;
	ft_printf("file %s fd redir %d mode %d\n", file, fd_redir, redir_mode);
	fd_to_save = dup(fd_redir);
	if (redir_mode == -1)
		close(fd_redir);
	else
		dup2(fd_file, fd_redir);
	(s[x - 1] == '&') ? x -= 1 : 0;
	s[x] = 0;
	cmd = ft_strsplit(s, ' ');
	bin_exec(ft_strsplit(s, ' '), *al.env, cmd[0]);
	dup2(fd_to_save, fd_redir);
}
