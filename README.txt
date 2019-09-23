Integrantes: Bergia Eugenio y Có Santiago

El programa debe compilarse de la siguiente manera:

gcc -std=c99 -Wall -c judoca.c
gcc -std=c99 -Wall main.c judoca.o

Para ejecutarlo, se le deben pasar dos argumentos, el archivo de entrada, y el archivo de salida:

./a.out input output

En el archivo de entrada, se le deberan pasar los judocas exactamente de la siguiente manera:

Equipo1:
Nombre,Apellido,Edad
Equipo2:
Nombre,Apellido,Edad

En caso de no existir el archivo de salida, se creará uno nuevo, y en él se escribiran todas las parejas formadas, con sus respectivos estados, asi como los judocas que quedaron sin emparejar.
