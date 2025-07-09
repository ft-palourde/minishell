
 ------------------------------------------------------------------------------ 

 ÀÀÀÀÀ       ÀÀ†    ÀÀ        ÀÀÀÀÀÀÀÀÀ    ÀÀ    üÀ  ÀÀÀÀÀ    ÀÀÀÀ›     ÀÀÀÀÀÀÀ 
 ããããããã†  ããããããã  ãã      ãã         ãã  ãã    ±ã  ããããããã  ããããããã   ããããããã 
 FF    FF FF    FF  FF     FF õFFFFFFFF FF FF    zF  FF    FF FF    FF  FF	  
 OO   rOO OO    OO  OO     O OO       OO O OO    =O  OO   OOY OO    OO  OOOOO   
 ÍÍÍÍÍÍÍ  ÍÍÍÍÍÍÍÍ  ÍÍ      ÍÍ  ÍÍÍÍÍ` ÍÍ  ÍÍ    ÍÍ  ­ÍÍÍÍÍÍ   ÍÍ   «ÍÍ  ÍÍ	   
 ¤¤       ¤¤    ¤¤  ¤¤¤¤¤¤¤¤  ¤¤¤   ¤¤¤    ¤¤¤¤¤¤¤¤  ¤¤  ¤¤   ¤¤¤¤¤¤¤   ¤¤¤¤¤¤¤ 
 ::       ::    ::  ::::::::     :::         ::::    ::   ::  :::::     ::::::: 

 --------------      a mini shell by RCochran & TCoeffet     ------------------ 


## *******************\/\/🇫🇷 Version francaise 🇫🇷\/\/******************* ##
## 							(english below)								 ##
## ********************************************************************* ##
>>>>>>> Stashed changes

**Minishell** est un projet réalisé en binôme dans le cadre d’un exercice de programmation en C.  
L’objectif est d’implémenter un shell minimaliste en C, qui se comporte de manière similaire au shell POSIX `bash`.

Le programme utilise le langage C, la libft (lib C faite maison), ainsi que les bibliothèques `termios` et `readline`, pour gérer l'entrée utilisateur et les fonctionnalités interactives. Un `Makefile` permet de compiler facilement le projet.

--------------------------------------------------------------------




### Compilation

Le projet se compile à l’aide de `make` :

### Execution

./minishell
aucune option ni argument n'est requis au lancement

### Execution

Le projet a été développé et testé sous Linux Ubuntu 22.04.

--------------------------------------------------------------------




## Fonctionnalités

Minishell implémente un ensemble de fonctionnalités de base pour reproduire le comportement d’un shell POSIX.

### Commandes intégrées (built-ins)

Les commandes suivantes sont intégrées au shell :

- `cd` : changer de répertoire
- `echo` : afficher un message dans le terminal
- `export` : définir une variable d’environnement
- `unset` : supprimer une variable d’environnement
- `env` : afficher les variables d’environnement
- `exit` : quitter le shell
- `pwd` : afficher le répertoire courant

### Fonctionnalités supportées

- **Redirections** : `>`, `>>`, `<`
- **Pipes** : exécution de commandes chaînées avec `|`
- **Variables d’environnement** : expansion avec `$VAR`, y compris `$?` pour le code de retour
- **Quotes** : gestion des guillemets simples `'` et doubles `"`
- **Commandes externes** : exécution de n’importe quelle commande présente dans le `$PATH`
- **Signaux** : gestion de `Ctrl+C` (SIGINT) et `Ctrl+D` (EOF)

### Limitations connues

Certaines fonctionnalités avancées ne sont pas prises en charge :

- **Wildcards** : les jokers (`*`, `?`) ne sont pas interprétés
- **Subshells** : pas de support pour les expressions entre parenthèses `( )`
- **Opérateurs logiques** : `&&`, `||` et les priorites par parentheses `( )` ne sont pas gérés, leur comportement est indefini.

--------------------------------------------------------------------




##### Parsing & Analyse Syntaxique

La ligne de commande saisie par l'utilisateur passe par plusieurs étapes avant d’être interprétée :

### 1. Lexing

Le **lexer** analyse la chaîne brute entrée par l’utilisateur pour identifier deux grandes familles d’éléments :

- **Mots (T_WORD)** : chaînes de caractères représentant les commandes et leurs arguments
- **Opérateurs** : symboles de contrôle du shell, classés par type :
  - `T_PIPE` (`|`)
  - `T_REDIR_IN` (`<`)
  - `T_REDIR_OUT` (`>`)
  - `T_APPEND` (`>>`)
  - `T_HEREDOC` (`<<`)
  - `T_AND_IF` (`&&`)
  - `T_OR_IF` (`||`)
  - `T_UNKNOWN` pour les erreurs ou cas non pris en charge

Chaque élément identifié est représenté par un **token**, avec son type (`t_token_type`) et son contenu textuel.

### 2. Tokenization

Une fois le lexing terminé, une **phase de tokenization** structure les tokens pour préparer l’exécution :

- Les séquences de `T_WORD` sont regroupées pour identifier les **commandes (`T_CMD`)** et leurs **arguments**
- Les métacaractères sont conservés pour la construction de l’arbre syntaxique
- Les quotes (`'`, `"`) sont traitées à cette étape pour conserver les chaînes exactes (sans encore faire d’expansion)

### 3. Expansion

L’**expansion des variables** (comme `$HOME`, `$?`, etc.) n’est **pas faite au moment du lexing**, mais **différée jusqu’à l’exécution**.  
Cela permet de traiter avec précision les cas où des variables apparaissent dans des redirections ou des quotes.

---

Exemple :

Input : echo "Hello $USER" | grep Hello > out.txt
Tokens :
[T_CMD "echo"], [T_WORD "Hello $USER"], [T_PIPE "|"],
[T_CMD "grep"], [T_WORD "Hello"], [T_REDIR_OUT ">"], [T_WORD "out.txt"]

--------------------------------------------------------------------




##### ARBRE BINAIRE

Pour executer les commandes on recupere la liste des tokens crees au parsing et on construit un arbre binaire comme ceci :

## ex1 `cat file.txt < in.txt | grep hello > out.txt`

##           [ T_PIPE ]
##           /        \
##    [T_CMD cat]     [T_CMD grep]
##         |               |
##   [ T_REDIR_IN ]   [ T_REDIR_OUT ]
##       ("in.txt")       ("out.txt")

Cela garantit que :

-    Les redirections sont liées directement à leur commande
-    L’exécution des pipes respecte bien l’ordre et l’isolement des contextes


## ex2 `<< LIM cat | grep "toto" | wc -l > out1 > out2 > out3` 

##                    [ T_PIPE ]
##                    /       \
##            [ T_PIPE ]       [T_CMD wc]
##            /       \              |
##    [T_CMD cat]   [T_CMD grep]   [T_REDIR_OUT >]
## 		|							("out1")
##  [T_HEREDOC <<]							\
## 									[T_REDIR_OUT >]
## 										("out2")
##                                           	\
## 	                                  	[T_REDIR_OUT >]
## 											("out3")

--------------------------------------------------------------------




##### EXECUTION

### Parcours de l’arbre

L’exécution est centralisée dans une fonction récursive appelée `exec_tree`.

Le parcours suit une logique en profondeur (postfixée) :

`1`  Si le nœud est un pipe `(T_PIPE)`, on appelle exec_pipe.

`2`  Si le nœud représente une redirection (`T_REDIR_IN`,` T_REDIR_OUT`, `T_APPEND`), la redirection est configurée via exec_redir.

`3`  Si le nœud est un heredoc `(T_HEREDOC)`, un fichier temporaire est utilisé et stocké dans ms->file_in.

`4`  On exécute récursivement la branche gauche `(root->left)` puis la branche droite `(root->right)`.

`5`  Si le nœud est une commande `(T_CMD)` et qu’aucune erreur de redirection `(open_failed)` n’a eu lieu, la fonction `exec_cmd` est appelée.

### Gestion des redirections

Les redirections sont toujours traitées avant l'exécution d'une commande :
-	Les descripteurs de fichiers (file descriptors) sont ouverts et redirigés temporairement.

-	Tous les descripteurs ouverts sont conservés dans une structure, pour être fermés correctement une fois la commande exécutée.

-	En cas d'échec d'ouverture (par exemple si un fichier est manquant), un indicateur `open_failed` empêche l’exécution de la commande.

### Built-ins vs Commandes externes

-	Lorsqu'une commande built-in (comme `cd`, `export`, `exit`, etc.) est utilisée hors pipeline, elle est exécutée dans le processus principal, sans fork.

-	En revanche, si elle est utilisée dans un pipeline, elle est exécutée dans un processus enfant via `fork`, comme une commande externe.

-	Cela respecte le comportement attendu d’un shell POSIX : un `cd` dans un pipe ne modifie pas l’environnement du shell parent.

### Gestion des erreurs

-	Les erreurs d'exécution sont récupérées via `waitpid`, qui permet d’obtenir le code de retour ou le signal d'un processus enfant.

-   Ces codes sont stockés dans une variable spéciale `($?)` accessible pour les expansions.

-	Les signaux comme `Ctrl+C (SIGINT)` ou `Ctrl+\ (SIGQUIT)` sont interceptés et traités pour empêcher l'arrêt brutal du shell ou pour fournir un retour utilisateur lisible.

--------------------------------------------------------------------


## *******************\/\/ 🇬🇧 ENGLISH VERSION 🇬🇧 \/\/******************* ##
## 					    	(chatgpt translated)						 ##
## ********************************************************************* ##



**Minishell** is a project developed in pairs as part of a C programming exercise.  
The goal is to implement a minimalist shell in C that behaves similarly to the POSIX `bash` shell.

The program uses the C language, a homemade `libft`, and the `termios` and `readline` libraries to handle user input and interactive features. A `Makefile` is provided for easy compilation.

--------------------------------------------------------------------

### Compilation

The project is compiled using `make`:

### Execution

Run with:  
`./minishell`  
No options or arguments are required.

### Platform

The project was developed and tested on Linux Ubuntu 22.04.

--------------------------------------------------------------------

## Features

Minishell implements a basic set of functionalities to replicate the behavior of a POSIX shell.

### Built-in commands

The following built-ins are supported:

- `cd`: change directory
- `echo`: display a message to the terminal
- `export`: set an environment variable
- `unset`: remove an environment variable
- `env`: display the environment variables
- `exit`: exit the shell
- `pwd`: print the current working directory

### Supported features

- **Redirections**: `>`, `>>`, `<`
- **Pipes**: execution of chained commands using `|`
- **Environment variable expansion**: with `$VAR`, including `$?` for exit codes
- **Quotes**: support for single `'` and double `"` quotes
- **External commands**: execution of any command found in the `$PATH`
- **Signals**: support for `Ctrl+C` (SIGINT) and `Ctrl+D` (EOF)

### Known limitations

Some advanced features are not implemented:

- **Wildcards**: pattern matching with `*` or `?` is not supported
- **Subshells**: expressions in parentheses `( )` are not handled
- **Logical operators**: `&&`, `||` and precedence with parentheses are not supported — their behavior is undefined

--------------------------------------------------------------------

##### Parsing & Syntax Analysis

The input command line is processed in multiple steps before being executed:

### 1. Lexing

The **lexer** scans the raw input string to identify two major families of elements:

- **Words (`T_WORD`)**: strings representing commands and arguments
- **Operators**: shell control symbols, categorized by type:
  - `T_PIPE` (`|`)
  - `T_REDIR_IN` (`<`)
  - `T_REDIR_OUT` (`>`)
  - `T_APPEND` (`>>`)
  - `T_HEREDOC` (`<<`)
  - `T_AND_IF` (`&&`)
  - `T_OR_IF` (`||`)
  - `T_UNKNOWN`: for errors or unsupported cases

Each identified element is represented by a **token**, with a `t_token_type` and its textual content.

### 2. Tokenization

After lexing, a **tokenization phase** structures the tokens to prepare for execution:

- Sequences of `T_WORD` are grouped into **commands (`T_CMD`)** with their arguments
- Metacharacters are preserved to help construct the syntax tree
- Quotes (`'`, `"`) are processed at this stage to preserve literal strings (without yet performing expansions)

### 3. Expansion

**Environment variable expansion** (e.g., `$HOME`, `$?`) is **not performed during lexing**, but is **deferred until execution**.  
This allows for precise handling of variables in quotes and redirections.

---

Example:

Input:  
`echo "Hello $USER" | grep Hello > out.txt`

Token output:

`[T_CMD "echo"], [T_WORD "Hello $USER"], [T_PIPE "|"],`  
`[T_CMD "grep"], [T_WORD "Hello"], [T_REDIR_OUT ">"], [T_WORD "out.txt"]`

--------------------------------------------------------------------

##### BINARY TREE

To execute the command, we build a binary tree from the parsed tokens:

## ex1 `cat file.txt < in.txt | grep hello > out.txt`

##          [ T_PIPE ]
##          /        \
##   [T_CMD cat]     [T_CMD grep]
##        |               |
##  [ T_REDIR_IN ]   [ T_REDIR_OUT ]
##      ("in.txt")       ("out.txt")

Cela garantit que :

-    Les redirections sont liées directement à leur commande
-    L’exécution des pipes respecte bien l’ordre et l’isolement des contextes


## ex2 `<< LIM cat | grep "toto" | wc -l > out1 > out2 > out3`

##                   [ T_PIPE ]
##                   /       \
##           [ T_PIPE ]       [T_CMD wc]
##           /       \              |
##   [T_CMD cat]   [T_CMD grep]   [T_REDIR_OUT >]
## 		|							("out1")
## [T_HEREDOC <<]							\
##									[T_REDIR_OUT >]
##										("out2")
##                                          	\
##	                                  	[T_REDIR_OUT >]
##											("out3")


--------------------------------------------------------------------

##### EXECUTION

### Tree traversal

Execution is handled by a recursive function called `exec_tree`.

The tree is traversed in **depth-first (postfix)** order:

1. If the node is a pipe `(T_PIPE)`, `exec_pipe` is called  
2. If the node is a redirection (`T_REDIR_IN`, `T_REDIR_OUT`, `T_APPEND`), it is processed with `exec_redir`  
3. If the node is a heredoc `(T_HEREDOC)`, a temporary file is created and stored in `ms->file_in`  
4. The left (`root->left`) and right (`root->right`) branches are executed recursively  
5. If the node is a command `(T_CMD)` and no redirection error occurred (`open_failed`), the function `exec_cmd` is called  

### Redirection management

Redirections are **handled before command execution**:

- File descriptors are opened and temporarily redirected
- All open descriptors are stored and **properly closed** after command execution
- If an opening fails (e.g., missing file), a flag `open_failed` prevents command execution

### Built-ins vs external commands

- Built-ins (like `cd`, `export`, `exit`, etc.) are executed **in the main process** if they are **not** inside a pipeline
- If they are part of a pipe, they are executed in a **child process via `fork`**
- This mimics the expected POSIX shell behavior (e.g., a `cd` in a pipe does not affect the parent shell)

### Error handling

- Execution errors are handled using `waitpid`, which retrieves the exit status or signal from the child process
- The return value is stored in a special variable (`$?`) and can be reused in later commands
- Signals like `Ctrl+C (SIGINT)` or `Ctrl+\ (SIGQUIT)` are caught and processed to avoid crashing the shell or to display clear messages

--------------------------------------------------------------------




🐚 
