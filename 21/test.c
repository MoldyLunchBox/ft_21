#include <unistd.h>
 #include <stdlib.h>

//  void biggest_pal(char *str)
//  {
//      int i;
//      int l;
//      int len;
//      int mlen;
//      int f;
//      int start;
    
//      len = 0;
//      i = 1;
//      mlen = 1;
//      start = 0;
//      while(str[len])
//      {
//          len++;
//      }
//      while(i < len)
//      {
         
       
//          f = i - 1;
//          l = i + 1;
//          while (f >= 0 && l < len && str[f] == str[l])
//          {
//              if(l - f + 1 > mlen)
//              {
//                  start = f;
//                  mlen = l - f + 1; 
//              }
//              f--;
//              l++;
//          }
//          i++;
//      }
//      f = start;
//      while (f <= start + mlen - 1)
//      {
//          write(1,&str[f++],1);
//      }
     
//  }
//  int main(int ac, char **av)
//  {
//      if(ac == 2)
//      {
//          biggest_pal(av[1]);
//      }
//      write(1,"\n",1);
//      return (0);

//  }


char    *itoa_base(int value, int base)
{
    int nbr;
    int i = 0;
    if (value == 0)
        return 0;
    nbr = value;
    while (nbr)
    {
        nbr = nbr / base;
        i++;
    }
    nbr = value;
    while (nbr)
    {
        if (base == 10)
            i++;
        nbr *= -1;
    }
}
 int main(int ac, char **av)
 {

     
     

 }