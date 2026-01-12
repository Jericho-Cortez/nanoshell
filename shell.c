/* ============================================
   NANOSHELL - Projet de Shell Unix minimal
   Groupe: [Vos 3 noms]
   ============================================ */

// ========== INCLUDES ==========
#include <stdio.h>      // printf, getchar, perror
#include <stdlib.h>     // malloc, free, exit, getenv
#include <string.h>     // strcmp, strtok, strchr, strdup
#include <unistd.h>     // fork, execve, access, chdir, getcwd
#include <sys/wait.h>   // waitpid

// Variable globale pour accéder aux variables d'environnement
extern char **environ;

// ========== PROTOTYPES DE FONCTIONS ==========
// (Les signatures que tout le monde doit respecter)

// PARSING (Personne 1)
char **parse_line(char *line);

// EXÉCUTION (Personne 2)
void execute(char **args);
char *find_in_path(char *cmd);

// BUILTINS (Personne 3)
int is_builtin(char *cmd);
void run_builtin(char **args);
void builtin_cd(char **args);
void builtin_pwd(void);
void builtin_env(void);


// ========================================================
//  SECTION PERSONNE 1 : BOUCLE PRINCIPALE + PARSING
// ========================================================

/**
 * main - Point d'entrée du programme
 * 
 * Boucle infinie qui :
 * 1. Affiche le prompt "?>"
 * 2. Lit une ligne avec getline()
 * 3. Parse la ligne avec parse_line()
 * 4. Exécute avec execute()
 * 5. Recommence
 */
int main(void)
{
    // TODO: Déclarer les variables nécessaires
    //   - char *line = NULL
    //   - size_t len = 0
    //   - char **args
    
    // TODO: Boucle while(1)
    //   - printf("?> ");
    //   - fflush(stdout);
    //   - getline(&line, &len, stdin);
    //   - Vérifier si ligne vide (continuer)
    //   - args = parse_line(line);
    //   - execute(args);
    //   - free(args);
    
    // TODO: Gérer Ctrl-D (quand getline retourne -1)
    
    return 0;
}

/**
 * parse_line - Découpe une ligne en arguments
 * @line: La ligne à découper
 * 
 * Return: Tableau de strings terminé par NULL
 */
char **parse_line(char *line)
{
    // TODO: Allouer un tableau de 64 char*
    // TODO: Utiliser strtok(line, " \t\n") pour découper
    // TODO: Remplir le tableau avec chaque token
    // TODO: Terminer avec NULL
    // TODO: Retourner le tableau
    
    return NULL; // À remplacer
}


// ========================================================
//  SECTION PERSONNE 2 : EXÉCUTION DES COMMANDES
// ========================================================

/**
 * execute - Exécute une commande
 * @args: Tableau d'arguments (args[0] = commande)
 * 
 * Si builtin -> appelle run_builtin()
 * Sinon -> fork + execve + waitpid
 */
void execute(char **args)
{
    pid_t pid;
    int status;
    char *path;
    
    // Vérification de base
    if (args[0] == NULL) {
        return;
    }
    
    // Si builtin, laisser Personne 3 gérer
    if (is_builtin(args[0])) {
        run_builtin(args);
        return;
    }
    
    // Créer un processus fils
    pid = fork();
    
    if (pid == -1) {
        perror("fork");
        return;
    }
    
    if (pid == 0) {
        // ===== PROCESSUS FILS =====
        path = find_in_path(args[0]);
        
        if (path == NULL) {
            printf("nanoshell: weird, %s is not here... :/\n", args[0]);
            exit(1);
        }
        
        execve(path, args, environ);
        perror("execve");
        exit(1);
        
    } else {
        // ===== PROCESSUS PARENT =====
        waitpid(pid, &status, 0);
    }
}

/**
 * find_in_path - Cherche un exécutable dans le PATH
 * @cmd: Nom de la commande
 * 
 * Return: Chemin complet si trouvé, NULL sinon
 */
char *find_in_path(char *cmd)
{
    // Si la commande contient "/", c'est un chemin
    if (strchr(cmd, '/') != NULL) {
        if (access(cmd, X_OK) == 0) {
            return cmd;
        }
        return NULL;
    }
    
    // Récupérer la variable PATH
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        return NULL;
    }
    
    // Copier PATH (car strtok modifie la chaîne)
    char *path_copy = strdup(path_env);
    
    // Buffer pour construire le chemin complet
    static char full_path[1024];
    
    // Découper PATH par ":"
    char *dir = strtok(path_copy, ":");
    
    // Tester chaque répertoire
    while (dir != NULL) {
        // Construire le chemin complet
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
        
        // Vérifier si le fichier existe et est exécutable
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return full_path;
        }
        
        // Passer au répertoire suivant
        dir = strtok(NULL, ":");
    }
    
    // Pas trouvé
    free(path_copy);
    return NULL;
}


// ========================================================
//  SECTION PERSONNE 3 : COMMANDES BUILTIN
// ========================================================

/**
 * is_builtin - Vérifie si une commande est un builtin
 * @cmd: Nom de la commande
 * 
 * Return: 1 si builtin, 0 sinon
 */
int is_builtin(char *cmd)
{
    // TODO: Comparer cmd avec "cd", "exit", "pwd", "env"
    // TODO: Retourner 1 si match, 0 sinon
    
    return 0; // À remplacer
}

/**
 * run_builtin - Exécute un builtin
 * @args: Tableau d'arguments
 */
void run_builtin(char **args)
{
    // TODO: Utiliser strcmp pour identifier la commande
    // TODO: Appeler la fonction appropriée:
    //   - "exit" -> exit(0)
    //   - "cd" -> builtin_cd(args)
    //   - "pwd" -> builtin_pwd()
    //   - "env" -> builtin_env()
}

/**
 * builtin_cd - Change de répertoire
 * @args: args[1] = répertoire cible
 */
void builtin_cd(char **args)
{
    // TODO: Gérer les cas:
    //   - args[1] == NULL ou "~" -> getenv("HOME")
    //   - args[1] == ".." -> utiliser ".."
    //   - Sinon -> utiliser args[1]
    // TODO: Appeler chdir(dir)
    // TODO: Si erreur, afficher avec perror()
}

/**
 * builtin_pwd - Affiche le répertoire courant
 */
void builtin_pwd(void)
{
    // TODO: Déclarer char cwd[1024]
    // TODO: Appeler getcwd(cwd, sizeof(cwd))
    // TODO: printf("%s\n", cwd)
}

/**
 * builtin_env - Affiche les variables d'environnement
 */
void builtin_env(void)
{
    // TODO: Parcourir environ[] avec une boucle
    // TODO: printf("%s\n", environ[i]) pour chaque ligne
}
