#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_same_c(char c, char *s)
{
	int i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_first_occ(char *s, int i)
{
	char c = s[i];
	if (!i)
		return (1);
	i--;
	while (i >= 0)
	{
		if (s[i] == c)
			return (0);
		i--;
	}
	return (1);
}

void	ft_inter(char *s1, char *s2)
{
	int i = 0;
	while (s1[i])
	{
		if (ft_same_c(s1[i], s2) && ft_first_occ(s1, i))
			ft_putchar(s1[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		ft_inter(av[1], av[2]);
	ft_putchar('\n');
	return (0);
}
