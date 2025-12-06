#!/bin/bash
      #_______________________________________________________________________________
      #                      INSTRUCTIONS POUR SLURM
      #_______________________________________________________________________________

      #SBATCH --job-name=cpuinfo   # Nom du job (pour le retrouver facilement)
      #SBATCH --output=cpuinfo_%j.out # Fichier de sortie standard (%j = ID du job)
      #SBATCH --error=Erreur_fm2pn_%j.err   # Fichier de sortie d'erreur (%j = ID du job)
      #SBATCH --time=00:02:00             # Temps max d'exécution (HH:MM:SS) - ici 2 minutes
      #SBATCH --nodes=1                   # Nombre de nœuds requis
      #SBATCH --ntasks=1                  # Nombre total de tâches (processus)
      #SBATCH --cpus-per-task=1          # Nombre de cœurs CPU par tâche
      #SBATCH --mem=50M                   # Mémoire requise par le job (ex: 50 Mo)
      #SBATCH --partition=formation         # !!! ADAPTER LE NOM DE LA PARTITION À VOTRE CLUSTER !!!

      #_______________________________________________________________________________
      #                      COMMANDES À EXÉCUTER PAR LE JOB
      #_______________________________________________________________________________

        echo "------------------------------------------------------"
        echo "Ce job tourne sur le noeud : $(hostname)" # Affiche le nom du noeud de calcul
        echo "Lancé le : $(date)"                       # Affiche la date et l'heure
      	echo "*****  Node de calcul: cpu info" 
        echo "------------------------------------------------------"


      cat /proc/cpuinfo
      # On simule un petit travail qui dure 20 secondes

