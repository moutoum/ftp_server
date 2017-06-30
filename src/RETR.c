/*
** RETR.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:26:25 2017 moutoum
** Last update Wed May 10 18:26:59 2017 moutoum
*/

#include "ftp.h"

static void send_file(int cfd, int fd)
{
  char buff[3096];
  int i;
  int c;

  bzero(buff, 3096);
  while ((c = read(fd, buff, 3096)) > 0)
    {
      i = 0;
      while (i < c)
	{
	  if (buff[i] == '\n')
	    write(cfd, "\r\n", 2);
	  else
	    write(cfd, &buff[i], 1);
	  i++;
	}
      bzero(buff, 3096);
    }
}

int server_RETR(int cfd, char *const _cmd, struct s_login *login) {
  int fd;
  char buff[3096];
  struct sockaddr_in client;
  char file[3096];
  struct stat buf;

  if (sscanf(_cmd, "RETR %s\r\n", file) < 1
      || (fd = open(file, O_RDONLY)) == -1)
      {
	sprintf(buff, "open: %s - %s", strerror(errno), file);
    	return (print_code(cfd, 550, buff), EXIT_SUCCESS);
      }
  if (login->passive == FTP_NOMODE)
    return (print_code(cfd, 425, NULL), EXIT_SUCCESS);
  if (login->passive == FTP_PASSIVE)
    server_accept(login->fd, &login->cfd, &client);
    else
    {
	if (connect(login->cfd, (const struct sockaddr *)&login->ctmpin,
	      sizeof(struct sockaddr)) == -1)
    	return (print_code(cfd, 530, strerror(errno)), EXIT_SUCCESS);
    }
  fstat(fd, &buf);
  sprintf(buff, "Opening ASCII mode data connection for %s (%lu bytes).",
	  file, buf.st_size);
  print_code(cfd, 150, buff);
  send_file(login->cfd, fd);
  print_code(cfd, 226, NULL);
  close(login->fd);
  close(login->cfd);
  close(fd);
  login->passive = FTP_NOMODE;
  return (EXIT_SUCCESS);
}
