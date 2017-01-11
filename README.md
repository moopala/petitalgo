# petitalgo

Ces lignes de code écrites en C++, sont tirées d'un projet visant à optimiser la gestion énergétique d’un foyer. 
Un foyer est constitué d’appareils électroniques qui doivent fonctionnées à certaines heures de la journée pendant un certain temps. 
On place les appareils suivant un planning et suivant ce planning un score est retourné pour savoir si l’optimisation est bonne. 
Le but du projet est de lisser la courbe de consommation des appareils.
Vous trouverez ci-dessous une petite explication de l'implémentationfaite pour ajuster la gestion du planning.

L'objet appareil

Un appareil est defini avec  : 

- Une consommation  énergétique
- Un durée de fonctionnement T_{fct}
- une plage de fonctionnement possible [T_{deb,plage},T_{fin,palge}]
- le temps de depart du fonctionnement T_{dep} ou on a T_{deb} \in [T_{deb,plage},T_{fin,palge}-T_{fct}]


Algorithme d'optimisation

L’optimisation se fait en 5 étapes :

- {Etape 1 :} Tous les appareils sont placés à leurs T_{deb,plage} de fonctionnement respectif. (T_{dep} = T_{deb,plage}) 
- {Etape 2 :} On calcule le score. 
- {Etape 2 :} Recherche de la position optimale pour le premier appareil dans la liste avec le nouveau $T_{deb}$. On calcule le score. 
- {Etape 3 :} Recherche de la position optimale pour l’appareil qui suit dans la liste, et ainsi de suite. On calcule le score. 
- {Etape 4 :} On répète les étapes 3 et 4  pour chaque nouveau temps de fonctionnement de l’appareil à déplacer.
- {Etape 5 :} La trie s’arrête lorsque le score ne peut plus être amélioré. 

Critque

Cet algorithme, en plus d’être lent, n'est pas du tout optimiser. 
A l’époque ou le projet était à faire, l’optimisation des calculs ne nous avait pas encore été exposée. 
Si c’était à refaire je tenterais l’implémentation avec un trie fusion.

