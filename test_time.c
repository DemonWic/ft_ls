#include <stdio.h>  // Для printf
#include <time.h>   // Для time, ctime
#include "ft_ls.h"

int main (void)
{    
   // Переменная для сохранения текущего времени
   long int ttime;
   char *s;
   char *s2;

   // Считываем текущее время
   ttime = time (NULL);

   // С помощью функции ctime преобразуем считанное время в
   // локальное, а затем в строку и выводим в консоль.
   printf ("%s\n",ctime (&ttime));
   s = (ctime(&ttime)) + 4;
   s2 = (ctime(&ttime)) + 20;
   ft_printf("%.6s ",s);
   ft_printf("%.4s",s2);

   return 0;
}