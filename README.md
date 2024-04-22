# DLogger

[![Static Badge](https://img.shields.io/badge/Downloads-V1.0-%2328d456)](https://github.com/Dr4kiel/DLogger/releases/download/V1.0/DLogger.x64.zip)

DLogger est un Logger simple en C/C++ permettant de gérer vos logs comme bon vous semble.

## Installation

Pour l'installer, il vous suffit de télécharger le .zip contenant : les .h, .lib et .dll nécessaires à l'utilisation de la librairie

## Utilisation

Pour utiliser le DLogger, vous devez, dans un premier temps, le paramétrer avec la fonction DLoggerInit() :

```c
// log_file_path correspond au chemin du dossier d'écriture des logs (veillez à ce que le dossier soit créée)
// log_level correspond au niveau de lecture des logs (expliqués plus bas)
DLoggerInit(log_file_path, log_level);
```

Dans un second temps, vous pouvez agrémenter votre code de lignes de logs comme celles-ci :

```c
// Un log de débug
DLoggerLog(DLOGGER_DEBUG_LEVEL, message);

// Un log de warning
DLoggerLog(DLOGGER_WARNING_LEVEL, message);

// il existe des macros par défaut pour chaque type de log
DLoggerDebug(message);
DLoggerInfo(message);
DLoggerWarning(message);
DLoggerError(message);
DLoggerFatal(message);
```
## Les Niveaux de Logs

| Niveau | Priorité |
|:------:|:--------:|
| DEBUG | 0 |
| INFO | 1 |
| WARNING | 2 |
| ERROR | 3 |
| FATAL | 4 |
