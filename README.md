minishel : sleep 10 | sleep 25 | sleep 13 ---> doit attendre 25 secondes.

PARENT : recoit la ligne, attend de recevoir un signal ou que la ligne soit finie Tourne tant qu'il a pas recu EXIT. (ou qu'on ferme pas le terminal)
ENFANT ligne : creer autant d'enfant que de commande et attend que toutes les commandes soient finit Tourne tant que les commandes sont pas finies.
ENFANT CMD : execute sa commande

void execcmd(char *scanned, t_struct struct)
{
	if (struct.builtin)
		exec_builtin(scanned);
	if (struct.pipe)
		exec_pipe(scanned);
	if (struct.empty)
		exec_empty();
}

int main()
{
	init_minishell(); //retient l'historique / les variables d'env...
	char *scanned;
	while(scanned != exit)
	{
		newprompt(); //reinitialise la struct de l'input et display le prompt
		scanned = readline(); //lit l'input suivant
		t_struct = parsing_mimishell(); //parse l'input
		execcmd(scanned, struct); // execute l'input en fonction du parsing donne
	}
	freetout();
}
