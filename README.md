# 🎮 Game in C

[![Language](https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20POSIX-lightgrey?style=flat-square&logo=linux)](https://www.linux.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=flat-square)](LICENSE)

Un projet de jeu interactif développé en C, mettant en œuvre les principes fondamentaux de la programmation système, de la gestion mémoire explicite et des structures de données.

---

## 📌 Présentation

Ce projet est une application/jeu développée en C. Il illustre la gestion bas niveau des ressources système, le découpage modulaire du code et la gestion de la boucle d'événements (game loop).

### 🌟 Fonctionnalités clés

- **Boucle de jeu (Game Loop) :** Gestion des entrées utilisateur, mise à jour de l'état du jeu et rendu.
- **Gestion explicite de la mémoire :** Allocation et libération dynamique dynamique (`malloc`, `free`) sans fuite mémoire.
- **Architecture modulaire :** Séparation claire entre la logique métier, les structures de données et le rendu.

---

## 🛠️ Stack Technique & Outils

- **Langage :** C (norme C99 / C11)
- **Compilation :** `gcc` / `clang`
- **Build System :** `Makefile`
- **Débogage & Profiling :** `gdb`, `valgrind`

---

## 🚀 Installation & Utilisation

### Prérequis

S'assurer d'avoir les outils de développement C installés sur votre système :

```bash
# Sur Ubuntu / Debian
sudo apt update
sudo apt install build-essential valgrind
