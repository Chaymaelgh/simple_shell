#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*** cmd chaining ***/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*** Convert_number() ***/
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*** system getline() ***/
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_Histry"
#define HIST_MAX	4096

extern char **Environment;

/* for read AND Write buff */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/**
 * struct liststr - singly linked list
 * @Num: number OF field
 * @str: string
 * @next: points
 */
typedef struct liststr
{
	int Num;
	char *str;
	struct liststr *next;
} List_t;

/***           ***/
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_Num;
	int linecount_flag;
	char *fname;
	List_t *ENV;
	List_t *Histry;
	List_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* PARSER.c */
int is_CMD(info_t *, char *);
char *DUP_chars(char *, int, int);
char *Find_path(info_t *, char *, char *);

/*** LOOPhsh.c ***/
int LOOPhsh(char **);


/*** Errors.c ***/
void _Eputs(char *);
int _Eputchar(char);
int _Putfd(char B)
int _Putsfd(char *Str, int fd);


/***
 *struct BuiltIN - contain a builtin string and related A Function
 *@type: BuiltIN command flag
 *@fnc: the function
 */
typedef struct BuiltIN
{
	char *type;
	int (*fnc)(info_t *);
} BuiltIN_table;


/*** shLOOP.c ***/
int hsh(info_t *, char **);
int find_BuiltIN(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/***  string.c ***/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/***  STRing01.c ***/
char *_STRcpy(char *, char *);
char *_STRdup(const char *);
void _Puts(char *);
int _Putchar(char);

/***  MEmories.c ***/
int Bfree(void **);

/***  AtOi.c ***/
int INTERactive(info_t *);
int IS_delim(char, char *);
int _ISalpha(int);
int _AtOi(char *);

/***  Errors01.c ***/
int _eRRatoi(char *);
void Print_error(info_t *, char *);
int Print_d(int, int);
char *CONvert_number(long int, int, int);
void Remove_Comments(char *);

/***  EXITS.c ***/
char *_sSrncpy(char *, char *, int);
char *_STRNcat(char *, char *, int);
char *_stRCHr(char *, char);

/***  TOKENizer.c ***/
char **STRtow(char *, char *);
char **STRtow2(char *, char);

/***  realloc.c ***/
char *_memSET(char *, char, unsigned int);
void Ffree(char **);
void *_RELLoc(void *, unsigned int, unsigned int);

/***  GITline.c ***/
ssize_t get_input(info_t *);
int _GETline(info_t *, char **, size_t *);
void SIGintHandler(int);

/***  GITINF.c ***/
void clear_INF(info_t *);
void set_INF(info_t *, char **);
void free_INF(info_t *, int);

/***  Environment.c ***/
char *_GetEnv(info_t *, const char *);
int _MYenv(info_t *);
int _MYsetenV(info_t *);
int _MYunsetenV(info_t *);
int populate_ENV_list(info_t *);

/***  Lists.c ***/
List_t *add_node(List_t **, const char *, int);
List_t *add_node_end(List_t **, const char *, int);
size_t print_List_STR(const List_t *);
int delete_node_at_Indx(List_t **, unsigned int);
void free_List(List_t **);

/***  Lists01.c ***/
size_t List_len(const List_t *);
char **List_to_Strings(List_t *);
size_t Print_List(const List_t *);
List_t *node_starts_with(List_t *, char *, char);
ssize_t GET_node_Indx(List_t *, List_t *);

/***  BuiltIN.c ***/
int _MYexit(info_t *);
int _MYcd(info_t *);
int _MYhelp(info_t *);

/***  BuiltIN01.c ***/
int _MYhistory(info_t *);
int _MYalias(info_t *);

/***  GITenv.c ***/
char **GET_Environ(info_t *);
int _UNsetenV(info_t *, char *);
int _setenV(info_t *, char *, char *);

/***  history.c ***/
char *GET_Histry_file(info_t *INF);
int write_Histry(info_t *INF);
int read_Histry(info_t *INF);
int build_Histry_list(info_t *INF, char *buff, int linecount);
int renumber_Histry(info_t *INF);

/*** Vars.c ***/
int IS_chain(info_t *, char *, size_t *);
void Check_chain(info_t *, char *, size_t *, size_t, size_t);
int Replace_alias(info_t *);
int Replace_vars(info_t *);
int Replace_String(char **, char *);

#endif
