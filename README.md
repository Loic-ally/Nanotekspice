# Nanotekspice

Projet **Nanotekspice** (Epitech) : simulateur de circuits logiques inspiré de SPICE.
Le programme lit un fichier `.nts` (netlist), construit le circuit, puis permet de simuler son comportement pas à pas.

## Sommaire

- [Prérequis](#prérequis)
- [Récupération](#récupération)
- [Compiler](#compiler)
- [Lancer](#lancer)
- [Format de netlist](#format-de-netlist)
- [Commandes interactives](#commandes-interactives)
- [Exemples](#exemples)
- [Développement](#développement)
- [Auteurs](#auteurs)

## Prérequis

- Linux / macOS (Windows possible via WSL)
- Un compilateur C++ (g++/clang++)
- `make` (et/ou `cmake` si le projet l’utilise)

> Ajuste cette section si ton repo utilise CMake (présence d’un `CMakeLists.txt`) ou uniquement un `Makefile`.

## Récupération

```bash
git clone https://github.com/Loic-ally/Nanotekspice.git
cd Nanotekspice
```

## Compiler

### Option A — Makefile

```bash
make
```

Binaire attendu (selon le projet) : `./nanotekspice` ou `./nanotekspice/` …

### Option B — CMake (si applicable)

```bash
cmake -S . -B build
cmake --build build -j
```

## Lancer

```bash
./nanotekspice <fichier>.nts
```

Exemple :

```bash
./nanotekspice examples/and.nts
```

## Format de netlist

Une netlist `.nts` est généralement composée de 2 sections :

- `.chipsets:` : déclaration des composants (input, output, gates, clock, etc.)
- `.links:` : connexions entre pins (ex: `a:1 chip:2`)

> Si ton sujet impose une liste précise de composants supportés (4001, 4011, 4030, 4069, 4071, 4081, 4094, 4512, 4514, 4801, etc.), ajoute-la ici.

## Commandes interactives

Une fois lancé, le programme attend des commandes sur stdin (exemples classiques du sujet) :

- `display` : affiche l’état actuel (inputs/outputs)
- `simulate` : avance d’un tick de simulation
- `loop` : simule en boucle (jusqu’à interruption)
- `dump` : affiche des infos internes (debug)
- `exit` : quitte

Affectation d’une entrée :

```text
<nom_input>=<0|1|U>
```

Exemple :

```text
a=1
b=0
simulate
display
```

## Exemples

```bash
./nanotekspice examples/xor.nts
```

Puis :

```text
a=1
b=1
simulate
display
```

## Développement

Recommandations :

- Compiler avec les warnings (`-Wall -Wextra -Werror`) si ce n’est pas déjà fait
- Structurer le code : parsing netlist / factory composants / simulation
- Ajouter des tests (si vous en avez)
