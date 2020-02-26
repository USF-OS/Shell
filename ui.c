#include <stdio.h>
#include <readline/readline.h>
#include <locale.h>

#include "history.h"
#include "logger.h"
#include "ui.h"

/* -- Private function forward declarations -- */
static int readline_init(void);
static int key_up(int count, int key);
static int key_down(int count, int key);
static char **command_completion(const char *text, int start, int end);
static char *command_generator(const char *text, int state);

static char prompt_str1[80] = "--[enter a command]--";
static char prompt_str2[80] = "-> ";

void init_ui(void)
{
    LOGP("Initializing UI...\n");

    char *locale = setlocale(LC_ALL, "en_US.UTF-8");
    LOG("Setting locale: %s\n",
            (locale != NULL) ? locale : "could not set locale!");

    rl_startup_hook = readline_init;
}

char *prompt_line1(void) {
    return prompt_str1;
}

char *prompt_line2(void) {
    return prompt_str2;
}

char *read_command(void)
{
    puts(prompt_line1());
    return readline(prompt_line2());
}

int readline_init(void)
{
    rl_bind_keyseq("\\e[A", key_up);
    rl_bind_keyseq("\\e[B", key_down);
    rl_variable_bind("show-all-if-ambiguous", "on");
    rl_variable_bind("colored-completion-prefix", "on");
    rl_attempted_completion_function = command_completion;
    return 0;
}

int key_up(int count, int key)
{
    /* Modify the command entry text: */
    rl_replace_line("User pressed 'up' key", 1);

    /* Move the cursor to the end of the line: */
    rl_point = rl_end;

    return 0;
}

int key_down(int count, int key)
{
    /* Modify the command entry text: */
    rl_replace_line("User pressed 'down' key", 1);

    /* Move the cursor to the end of the line: */
    rl_point = rl_end;

    return 0;
}

char **command_completion(const char *text, int start, int end)
{
    /* Tell readline that if we don't find a suitable completion, it should fall
     * back on its built-in filename completion. */
    rl_attempted_completion_over = 0;

    return rl_completion_matches(text, command_generator);
}

/**
 * This function is called repeatedly by the readline library to build a list of
 * possible completions. It returns one match per function call. Once there are
 * no more completions available, it returns NULL.
 */
char *command_generator(const char *text, int state)
{
    return NULL;
}
