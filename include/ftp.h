/*
** ftp.h for  in /home/moutou_m/c/PSU_2016_myftp/include
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 23:09:41 2017 moutoum
** Last update Wed May 10 23:09:57 2017 moutoum
*/

#ifndef FTP_H_
#define FTP_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#undef _GNU_SOURCE
#endif

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

#define FTP_SP ' '
#define FTP_CRLF "\r\n"
#define FTP_ANONYM "Anonymous"

struct s_login
{
  char login[3096];
  char pass[3096];
  int connected;
  int passive;
  int fd;
  int cfd;
  int port;
  char *ip;
  struct sockaddr_in ctmpin;
};

#define FTP_NOMODE 0
#define FTP_PASSIVE 1
#define FTP_ACTIVE 2

struct s_command
{
  const char *name;
  int (*callback)(int cfd, char *const cmd, struct s_login *login);
  int connected;
};

extern struct s_command g_cmds[];

struct s_code
{
  uint16_t code;
  const char *msg;
};

int print_code(int fd, uint16_t code, const char *msg);
int server_accept(int fd, int *cfd, struct sockaddr_in *cin);
int server_init_tcp(struct protoent **protocol_addr);
int server_close_socket(int fd);
int server_bind(int fd, int port);
int server_listen(int fd);
int server_create_socket(int *fd_addr, const struct protoent *protocol);
int server_USER(int cfd, char *const _cmd, struct s_login *login);
int server_PASS(int cfd, char *const _cmd, struct s_login *login);
int server_CWD(int cfd, char *const _cmd, struct s_login *login);
int server_CDUP(int cfd, char *const _cmd, struct s_login *login);
int server_QUIT(int cfd, char *const _cmd, struct s_login *login);
int server_NOOP(int cfd, char *const _cmd, struct s_login *login);
int server_PWD(int cfd, char *const _cmd, struct s_login *login);
int server_DELE(int cfd, char *const _cmd, struct s_login *login);
int server_HELP(int cfd, char *const _cmd, struct s_login *login);
int server_PASV(int cfd, char *const _cmd, struct s_login *login);
int server_RETR(int cfd, char *const _cmd, struct s_login *login);
int server_PORT(int cfd, char *const _cmd, struct s_login *login);
int server_LIST(int cfd, char *const _cmd, struct s_login *login);
int server_STOR(int cfd, char *const _cmd, struct s_login *login);

#endif
