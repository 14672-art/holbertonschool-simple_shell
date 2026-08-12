# 0x11. C - Simple Shell (`hsh`)

`hsh` est un interpréteur de commandes UNIX simple développé dans le cadre du cursus de programmation C de Holberton School. Il emule les fonctionnalités de base du shell Bourne (`/bin/sh`).

## Description

Le shell lit l'entrée utilisateur, analyse les commandes et arguments, recherche les exécutables dans le `PATH`, crée des processus enfants à l'aide de `fork()`, et exécute les programmes avec `execve()`. Il fonctionne en mode interactif et non-interactif.

## Sorties et Gestion des Erreurs

- Produit la même sortie exacte que `/bin/sh`.
- Les messages d'erreur respectent la syntaxe de `/bin/sh` en utilisant le nom du programme (`argv[0]`) :
  ```bash
  ./hsh: 1: qwerty: not found
