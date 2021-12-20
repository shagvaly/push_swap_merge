#include "./libft/libft.h"

/*
 * ПРЕДСТАВЛЕНИЕ ЧИСЕЛ
 * Какой формат ввода числа считается представимым?
 * 1. Символ '-' ставится только 1 раз. Знак '+' не ставится. (?)
 * 2. Могу встречаться только символы цифр и знака '-' перед числом.
 * 3. Число не должно вызывать переполнение int.
 * 4. (...)
 */

int	ft_is_representable(char *str)
{
	int	i;
	int	length;
	char *int_max;
	char *int_min;

	i = 0;
	int_max = "2147483647";
	int_min = "-2147483648";
	if (str[i] == '-')
		i++;
	while(str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (str[0] == '-' && i == 1)
		return (0);
	length = ft_strlen(str);
	if ((length > 10 && str[0] != '-')
		|| (length > 11 && str[0] == '-'))
		return (0);
	if ((length < 10 && str[0] != '-')
		|| (length < 11 && str[0] == '-'))
		return (1);
	if ((str[0] != '-' && ft_strncmp(str, int_max, 10) > 0)
		|| (str[0] == '-' && ft_strncmp(str, int_min, 11) > 0))
		return (0);
	return (1);
}