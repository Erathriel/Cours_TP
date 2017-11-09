/***************************************************

Fichier : tp3_ex1.c
Date de creation : 01 novembre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

// Q1 :

// Q2 : La commande pstree affiche la liste des processus en cours d'execution sous la forme d'un arbre et fusionne les branche si 
// un processus est lancer plusieurs fois. Par exemple : ├─upowerd───2*[{upowerd}] De plus les accolades indique que ceci est un 
// thread d'un processus. Il est plus simple d'observer un lien de parenté avec pstree qu'avec ps.

// Q3 : La commande ps affiche la liste des processus en cours de manière statique alors que top l'affiche de manière dynamique
// et donne l'utilisation de la memoire et de la CPU par les processus en cours en s'actualisant en continue jusqu'à stopper la commande.

// Q4 : Pour obtenir un affichage complet on utilise la commande ps -l qui permet de faire un affichage long. Cet affichage nous donne 
// l'etat du processus, son UID ( ID de l'utilisateur ), son PID, son PPID ( ID du pere du processus ), CMD la commande executée, ainsi 
// que d'autre informations.
// Les états possibles des processus sont : 
// - D pour "sommeil ininterruptible"
// - R pour "prêt à être exécuté"
// - S pour "endormi"
// - T pour "arrêté ou suivi"
// - Z pour "zombie"
// - W pour "processus n'a pas de pages résidentes"
// - X pour "mort"
// - t pour "arrêter par debugger"

// Q5 : ps -ef

// Q6 : watch ps -ef

// Q7 : nombre de processeur :
//
// nombre de coeur : 
//     -grep -c "processor" /proc/cpuinfo
//     -lscpu -a -e=socket | grep 0 | wc -l
// hyperthreading :