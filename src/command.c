/*
** command.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:18:10 2017 moutoum
** Last update Wed May 10 18:18:11 2017 moutoum
*/

#include "ftp.h"

struct s_command g_cmds[] =
    {
	{.name = "USER",
	 .callback = &server_USER,
	 .connected = 0},
	{.name = "PASS",
	 .callback = &server_PASS,
	 .connected = 0},
	{.name = "CWD",
	 .callback = &server_CWD,
	 .connected = 1},
	{.name = "CDUP",
	 .callback = &server_CDUP,
	 .connected = 1},
	{.name = "QUIT",
	 .callback = &server_QUIT,
	 .connected = 0},
	{.name = "PORT",
	 .callback = &server_PORT,
	 .connected = 1},
	{.name = "PASV",
	 .callback = &server_PASV,
	 .connected = 1},
	{.name = "STOR",
	 .callback = &server_STOR,
	 .connected = 1},
	{.name = "RETR",
	 .callback = &server_RETR,
	 .connected = 1},
	{.name = "LIST",
	 .callback = &server_LIST,
	 .connected = 1},
	{.name = "DELE",
	 .callback = &server_DELE,
	 .connected = 1},
	{.name = "PWD",
	 .callback = &server_PWD,
	 .connected = 1},
	{.name = "HELP",
	 .callback = &server_HELP,
	 .connected = 1},
	{.name = "NOOP",
	 .callback = &server_NOOP,
	 .connected = 1},
	{.name = NULL,
	 .callback = NULL,
	 .connected = 0}};
