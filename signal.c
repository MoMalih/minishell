#include "minishell.h"

void handle_int(int signo) 
{
	if (signo == SIGINT)
    {
		printf("\n");
		rl_on_new_line();
		// rl_clear_visible_line();
		rl_set_prompt(">$");
		rl_redisplay();
		// rl_forced_update_display(); 
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
		// rl_clear_visible_line();
		rl_redisplay();
		// rl_forced_update_display(); 
	}
}
