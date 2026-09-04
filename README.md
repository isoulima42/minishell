*Ce projet a été réalisé dans le cadre du cursus de 42 par isoulima et abouzidi.*

# minishell

![Language](https://img.shields.io/badge/Language-C-blue)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen)

## Description

minishell est un interpréteur de commandes minimaliste, inspiré de `bash`. Il affiche
un prompt, lit une ligne via `readline`, la découpe en tokens, la parse en une suite de
commandes reliées par des pipes, développe les variables et les guillemets, applique les
redirections, puis exécute chaque commande (builtin interne ou binaire externe via
`execve`). Le projet couvre l'analyse lexicale, le parsing, la gestion des processus
(`fork`/`pipe`/`wait`), les redirections, les heredocs, l'expansion de variables et la
gestion fine des signaux.

---

## Instructions

### Compilation

```bash
make
```

La bibliothèque `libft` est compilée automatiquement, puis l'exécutable `minishell`
est généré. La compilation lie `-lreadline`.

```bash
make clean    # supprime les .o
make fclean   # supprime les .o et minishell
make re       # recompile tout
```

### Utilisation

```bash
./minishell
```

Exemples :

```bash
minishell$ echo "bonjour $USER" | cat -e
minishell$ ls -la | grep .c > liste.txt
minishell$ cat << EOF
minishell$ export NOM=42 && echo $NOM        # (&& non géré en mandatory)
minishell$ cd /tmp ; pwd                     # (; non géré en mandatory)
```

---

## Fonctionnalités

- **Prompt** interactif et **historique** des commandes (`readline`, `add_history`)
- **Recherche et exécution** du bon binaire via `PATH`, chemin relatif ou absolu
- **Guillemets** : `'` (aucune interprétation) et `"` (tout sauf `$`)
- **Expansion** de variables d'environnement : `$VAR`, `${VAR}`, et `$?` (code de sortie
  du dernier pipeline en avant-plan)
- **Redirections** : `<` (entrée), `>` (sortie tronquée), `>>` (sortie ajoutée),
  `<<` (heredoc, avec ou sans expansion selon les guillemets du délimiteur)
- **Pipes** `|` reliant un nombre arbitraire de commandes
- **Builtins** : `echo` (option `-n`), `cd` (chemin relatif/absolu), `pwd`, `export`,
  `unset`, `env`, `exit`
- **Signaux** en mode interactif :
  - `Ctrl-C` affiche un nouveau prompt sur une nouvelle ligne (`$?` = 130)
  - `Ctrl-D` quitte le shell
  - `Ctrl-\` est ignoré au prompt ; en cours de commande affiche `Quit (core dumped)`
- **Codes de sortie** cohérents : `127` (commande introuvable), `126` (permission /
  répertoire), `128+n` (terminaison par signal), `2` (erreur de syntaxe)

---

## Choix techniques

- **Pipeline en trois temps** — un *lexer* produit une liste de tokens en respectant les
  guillemets ; un *parser* les regroupe en `t_cmd` (argv + liste de redirections) séparés
  par les pipes ; un *expander* développe variables et guillemets puis reconstruit `argv`.
- **Expansion avec découpage en champs** — une variable non protégée par des guillemets
  qui contient des espaces est éclatée en plusieurs arguments, comme dans `bash` ; entre
  guillemets, les espaces sont conservés et une expansion vide `""` produit un argument
  vide.
- **Une seule variable globale** `g_signal` (int), limitée au numéro du signal reçu,
  conformément au sujet. Les handlers sont reconfigurés selon le contexte (prompt,
  exécution, heredoc).
- **Builtins qui modifient le shell** (`cd`, `export`, `unset`, `exit`) exécutés dans le
  processus parent lorsqu'ils sont seuls, afin que leurs effets persistent ; dans un pipe
  ils tournent dans l'enfant.
- **Heredoc** lu dans le parent avant l'exécution (interruptible par `Ctrl-C`), le contenu
  transitant par un `pipe()`.
- **Environnement** stocké en liste chaînée `t_env` (clé/valeur), converti en tableau
  `char **` uniquement au moment de `execve`.
- **Dépendance libft** : listes chaînées (`ft_lst*`), `ft_split`, `ft_substr`,
  `ft_strjoin`, `ft_itoa`, `ft_putstr_fd`, etc.

---

## Ressources

- `man readline`, `man 3 rl_on_new_line`
- `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 wait`
- `man 2 open`, `man 2 access`, `man 3 getcwd`, `man 2 chdir`
- `man 2 signal`, `man 7 signal`
- Sujet officiel 42

---

## AI usage

L'IA a été utilisée uniquement pour :
- clarifier le comportement de `readline` et des signaux, le découpage en champs de
  l'expansion, et les conventions de codes de sortie de `bash`
- structurer ce README

L'implémentation, l'architecture et la compréhension du code ont été réalisées
manuellement.

---

## Auteurs

42 Lausanne
Logins : isoulima (exécution, builtins, heredoc, signaux, environnement) et abouzidi (lexer, parser, expansion)
