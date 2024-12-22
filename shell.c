#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief The main loop of the shell program.
 */
void main_loop();

/**
 * @brief Changes the current working directory.
 * 
 * @param args The arguments passed to the "cd" command.
 * @return Always returns 1 to continue the shell loop.
 */
int main_cd(char **args);

/**
 * @brief Exits the shell program.
 * 
 * @param args The arguments passed to the "exit" command (not used).
 * @return Always returns 0 to terminate the shell loop.
 */
int main_exit(char **args);

/**
 * @brief Gets the number of built-in shell commands.
 * 
 * @return The number of built-in commands.
 */
int main_size_builtIn();

/**
 * @brief Reads a line of input from the user.
 * 
 * @return The line of input as a dynamically allocated string. Must be freed by the caller.
 */
char *main_read_line();

/**
 * @brief Splits a line into tokens (arguments).
 * 
 * @param line The input line to split.
 * @return A dynamically allocated array of tokens. Must be freed by the caller.
 */
char **main_split_line(char *line);

/**
 * @brief Launches a program specified in the arguments.
 * 
 * @param args The arguments, including the program name.
 * @return Always returns 1 to continue the shell loop.
 */
int main_launch(char **args);

/**
 * @brief Executes a command, either built-in or external.
 * 
 * @param args The arguments of the command.
 * @return 1 to continue the shell loop, or 0 to terminate.
 */
int main_execute(char **args);

// Array of built-in command names
char *builtIn_str[] = {"cd", "exit"};

// Array of corresponding function pointers for built-in commands
int (*builtin_func[])(char **) = {&main_cd, &main_exit};

/**
 * @brief Entry point of the shell program.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return Exit status code.
 */
int main(int argc, char **argv)
{
    main_loop();
    return 0;
}

int main_size_builtIn()
{
    return sizeof(builtIn_str) / sizeof(char *);
}

void main_loop()
{
    char *line;
    char **args;
    int willContinue;

    do
    {
        printf("$ ");
        line = main_read_line();
        if (!line)
        {
            fprintf(stderr, "Failed to read line\n");
            continue;
        }

        args = main_split_line(line);
        if (!args)
        {
            free(line);
            fprintf(stderr, "Failed to split line\n");
            continue;
        }

        willContinue = main_execute(args);

        free(line);
        free(args);
    } while (willContinue);
}

int main_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "$: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("$");
        }
    }
    return 1;
}

int main_exit(char **args)
{
    return 0;
}

char **main_split_line(char *line)
{
    int bufSize = 64;
    int position = 0;
    char **tokens = malloc(bufSize * sizeof(char *));
    char *token;

    if (tokens == NULL)
    {
        fprintf(stderr, "Allocation Error\n");
        return NULL;
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;
        if (position >= bufSize)
        {
            bufSize += bufSize;
            char **temp = realloc(tokens, bufSize * sizeof(char *));
            if (temp == NULL)
            {
                free(tokens);
                fprintf(stderr, "Reallocation Error\n");
                return NULL;
            }
            tokens = temp;
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

int main_launch(char **args)
{
    pid_t pid;
    pid_t wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("$");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("$");
    }
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
            printf("Waiting for process %d\n", wpid);  

        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int main_execute(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }
    for (int i = 0; i < main_size_builtIn(); i++)
    {
        if (strcmp(args[0], builtIn_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }
    return main_launch(args);
}

char *main_read_line()
{
    char *returnLine = NULL;
    size_t bufferSize = 0;
    ssize_t statusValue = getline(&returnLine, &bufferSize, stdin);

    if (statusValue == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("readline");
            free(returnLine);
            exit(EXIT_FAILURE);
        }
    }
    return returnLine;
}
