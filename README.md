# LO21-Project

Projet dans le cadre de l'UV LO21 "Programmation et conception orientees objet" de l'Université de Technologie de Compiègne.

## Copier le projet

- `git clone https://github.com/StephaneBranly/LO21-Project.git`

## Ajouter une feature / branche

### Creer sa branche
- `git checkout main`
- `git pull`
- `git checkout -b nomBranche`

### Sequencer l'ajout de contenu en commit
- `git add .`
- `git commit -m "Description du commit"`
- `git push`

## Quelques infos dans le tas :

- [Note de clarification](etudes_de_projet/NoteDeClarification.md)
- la partie Ui et Engine ne doivent jamais communiquer entre elles directement. Elles doivent passer par le Connector
- nommer les fonctions et variables avec la meme casse, cf: camelCase
- bien mettre le namespace en fonction de la partie exploitee (Ui, Engine, Connector) et ranger correctement dans les dossiers
