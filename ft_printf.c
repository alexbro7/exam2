#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct	s_arg
{
	int	l;
	int	p;
}		t_arg;

int	ft_strlen(char *s)
{
	int  i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_nbrlen_d(int n)
{
	int i = 0;
	if (!n)
		return (1);
	if (n == -2147483648)
		return (10);
	n *= (n < 0 ? -1 : 1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_nbrlen_x(unsigned int n)
{
	int i = 0;
	if (!n)
		return (1);
	n *= (n < 0 ? -1 : 1);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_put_x_char(int x, char c)
{
	while (x)
	{
		ft_putchar(c);
		x--;
	}
}

void	ft_putnbr_d(int n)
{
	int x = 1;
	if (n == -2147483648)
	{
		write(1, "2147483648", 10);
		return ;
	}
	n *= (n < 0 ? -1 : 1);
	while (n / x >= 10)
		x *= 10;
	while (x)
	{
		ft_putchar((n/x) + '0');
		n %= x;
		x /= 10;
	}
}

void	ft_putnbr_x(unsigned int n)
{
	unsigned int x = 1;
	char *base = "0123456789abcdef";
	while (n / x >= 16)
		x *= 16;
	while (x)
	{
		ft_putchar(base[n/x]);
		n %= x;
		x /= 16;
	}
}

int	ft_is_num(char c)
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}

int	ft_is_arg(char *s)
{
	int i = 0;
	while (ft_is_num(s[i]))
		i++;
	if (s[i] == '.')
	{
		i++;
		while (ft_is_num(s[i]))
			i++;
	}
	return (s[i] == 's' || s[i] == 'd' || s[i] == 'x' ? 1 : 0);
}

int	ft_arg_in_format(char *s)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == '%')
			if (ft_is_arg(s + i + 1))
				return (1);
		i++;
	}
	return (0);
}

t_arg	ft_get_arg(char *s, int *i)
{
	t_arg	a;
	a.l = 0;
	a.p = 0;
	*i += 1;
	while (ft_is_num(s[*i]))
	{
		a.l *= 10;
		a.l += s[*i] - '0';
		*i += 1;
	}
	if (s[*i] == '.')
	{

		*i += 1;
		while (ft_is_num(s[*i]))
		{
			a.p *= 10;
			a.p += s[*i] - '0';
			*i += 1;
		}
	}
	return (a);
}

int	ft_put_s(t_arg a, va_list *ap)
{
	char *s = va_arg(*ap, char *);
	int sz = ft_strlen(s);
	int l2 = (ap && a.p < sz ? a.p : sz);
	int l1 = (a.l && a.l > l2 ? a.l - l2 : 0);
	ft_put_x_char(l1, ' ');
	write(1, s, l2);
	return (l1 + l2);
}

int	ft_put_d(t_arg a, va_list *ap)
{
	int n = va_arg(*ap, int);
	int sz = ft_nbrlen_d(n);
	int l2 = (a.p > sz ? a.p - sz : 0);
	int l1 = (a.l > l2 + sz ? a.l - (l2 + sz) : 0);
	l1 -= (l1 && n < 0 ? 1 : 0);
	ft_put_x_char(l1, ' ');
	if (n < 0)
	{
		ft_putchar('-');
		l1++;
	}
	ft_put_x_char(l2, '0');
	ft_putnbr_d(n);
	return (l1 + l2 + sz);
}

int	ft_put_x(t_arg a, va_list *ap)
{
	unsigned int n = va_arg(*ap, unsigned int);
	int sz = ft_nbrlen_x(n);
	int l2 = (a.p > sz ? a.p - sz : 0);
	int l1 = (a.l > l2 + sz ? a.l - (l2 + sz) : 0);
	ft_put_x_char(l1, ' ');
	ft_put_x_char(l2, '0');
	ft_putnbr_x(n);
	return (l1 + l2 + sz);
}

int	ft_printf(char const *s, ...)
{
	va_list ap;
	t_arg	arg;
	int i = 0, ret = 0, b = ft_arg_in_format((char *)s);
	if (b)
		va_start(ap, s);
	while (s[i])
	{
		if (s[i] != '%')
		{
			ft_putchar(s[i]);
			ret++;
		}
		else if (ft_is_arg((char *)s + i + 1))
		{
			arg = ft_get_arg((char *)s, &i);
			if (s[i] == 's')
				ret += ft_put_s(arg, &ap);
			else if (s[i] == 'd')
				ret += ft_put_d(arg, &ap);
			else if (s[i] == 'x')
				ret += ft_put_x(arg, &ap);
		}
		i++;
	}
	if(b)
		va_end(ap);
	return (ret);
}

int	main()
{
	ft_putnbr_d(ft_printf("salutsalut%23.4d%30.7s    %x|\n", -2147483648, "i42424242424224242424242424242424242", -42));
	ft_putchar('\n');
	ft_putnbr_d(   printf("salutsalut%23.4d%30.7s    %x|\n", -2147483648, "i42424242424224242424242424242424242", -42));
	ft_putchar('\n');
	ft_putnbr_d(ft_printf(""));
	ft_putchar('\n');
	ft_putnbr_d(   printf(""));
	ft_putchar('\n');
}
