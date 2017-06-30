/*
** server2.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:10:16 2017 moutoum
** Last update Wed May 10 18:10:27 2017 moutoum
*/

#include "ftp.h"

int server_accept(int fd, int *cfd, struct sockaddr_in *cin)
{
  socklen_t s;

  s = 0;
  if ((*cfd = accept(fd, (struct sockaddr *)cin, &s)) == -1)
    return (perror("accept"), EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
