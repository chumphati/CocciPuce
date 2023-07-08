# CocciPuce

## Lancer le projet

Après avoir cloné le projet et s'être mis dans le répertoire coccipuce, 2 méthodes sont possibles : <br/>

### Méthode 1 : lancer par ligne de commande dans un terminal

La commande est :<br/>

    gcc -Wall model/coccinelle.c model/direction.c model/potager.c model/puceron.c model/tomato.c ui/cui.c ui/manager.c initialization.c rule.c simulation.c main.c -o executable
    ./executable

### Méthode 2 : utilisation du makefile

Les commandes pour lancer le projet en entier sont :<br/>

    make all
    make launch
