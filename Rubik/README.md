# Cubo de Rubik 3x3x3

## Generar PDBs

1. Situarnos en la carpeta actual 
2. Correr el comando: 
```bash
make rubik3/pdb_rubik_<Número de PDB>.pdb
```

## Correr el caso

1. Situarnos en la carpeta actual
2. Correr el comando:
```bash
make rubik3.succ
```
3. Correr el archivo rubik3.succ con el comando:
```bash
<Número de discos del caso>_disk_4peg_ToH.succ instances_<Número de distancia>.txt pdb_rubik
```


## PDBs usadas por cada caso

### Caso Torres de 12 discos
* pdb_rubik_0 == Abstracción particionando los primeros 6 cubitos bordes del cubo.
* pdb_rubik_1 == Abstracción particionando los últimos 6 cubitos bordes del cubo.
* pdb_rubik_2 == Abstracción particionando los 8 cubitos esquinas del cubo.
