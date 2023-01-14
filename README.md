OBJECTIF: réaliser une simulation des trajectoires des planètes de notre système solaire
	  avec des méthodes de calcul différentes (Euler, Euler Asymétrique et Runge Kutta d'ordre 2)

###C:
	compilation : 
		- make cleanAll : supprime les fichiers .o, l'executable et la librarie
		- make cleanData : supprime les fichier .json
		- make all : compilation
	 
	- Affectation des données de chaque planètes à partir d'un fichier .json
	- Calcul de la trajectoire des planètes stocké dans une liste de stuct Point
	- Ecriture des données de la trajectoire dans 3 fichiers en fonction de la méthode de calcul utilisé

	Un fichier par méthode contenant les informations de la trajectoire de chaque planètes

JavaScript:
	- Récupération du fichier de l'utilisateur selon son choix
	- Résolution adaptive du nombre de point essentiel à la trajectoire afin d'optimiser 
	  l'affichage graphique

Interface WEB:
	- Fiche descriptive de chaque planètes
