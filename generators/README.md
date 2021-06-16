# Generadores

## Generadores de archivos PSVN
Los generadores de archivos PSVN para cada problema fueron implementados en Python3, para usarlos corremos el comando:
```bash
python <Nombre del generador>.py <Número de caso>
```
Ejemplo para generar el problema Torres de Hanoi con 4 astas y 12 discos:
```bash
python 4_peg_ToH.py 12
```

Una vez corrido dicho comando, se creará el archivo PSVN en la carpeta del problema.

## Generador de distancia Manhattan
El generador de la distancia Manhattan fue implementado en Python3, para usarlo corremos el comando:
```bash
python <Nombre del generador>.py <Número de casillas del caso de n puzzle>
```

Esto nos arrojará en la terminal una fracción de codigo en C++, el cual tendremos que copiar y pegar en el archivo con el algoritmo informado que usaremos para buscar la solución al problema de n puzzle con distancia Manhattan.
