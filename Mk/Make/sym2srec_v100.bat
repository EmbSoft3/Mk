@echo off

:: Suppression des symboles locaux */
copy /y %1.elf %1-Strip.elf
arm-none-eabi-strip.exe --discard-all --strip-debug  %1-Strip.elf

:: Ajout des symboles dans l'exécutable
"../Mk/Make/sym2srec.exe" %1-Strip.elf %2 %3

:: Affichage des statistiques
arm-none-eabi-size --format=berkeley --totals %1.elf

