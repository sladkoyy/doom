#include "doom.h"

t_v2	v2_add(t_v2 v1, t_v2 v2)
{
	t_v2 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

/*
**	Возвращает 1 если координаты точек v1 и v2 совпадают
*/

int			v2_compare(t_v2 v1, t_v2 v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
		return (1);
	return (0);
}

/*
**	Проверяет, находится ли установленная точка v2 в заданных границах
**	Возвращает 0, если точка выходит за 0 или обозначенные границы maxx, maxy
*/

int			v2_in_borders(t_v2 v2, int maxx, int maxy)
{
	if (v2.x < 0 || v2.x >= maxx || v2.y < 0 || v2.y >= maxy)
		return (0);
	return (1);
}
