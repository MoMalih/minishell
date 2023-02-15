#include "minishell.h"

void	rl_replace_line (text, clear_undo)
     const char *text;
     int clear_undo;
{
  int len;

  len = strlen (text);
  if (len >= 10000)
    rl_extend_line_buffer (len);
  strcpy (rl_line_buffer, text);
  rl_end = len;

  if (clear_undo)
    rl_free_undo_list ();

  _rl_fix_point (1);
}

void handle_int(int signo) 
{
	if (signo == SIGINT)
    {
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handle_quit(int sig_code)
{
	if (sig_code == SIGQUIT)
	{
		printf("Quit: 3\n");
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
