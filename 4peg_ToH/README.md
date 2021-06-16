# Torres de Hanoi 12/14/18 discos

## Generar PDBs

1. Situarnos en la carpeta actual 
2. Correr el comando: 
```bash
make <Número de discos del caso>_disk_4peg_ToH/pdb_<Número de discos del caso>_disk_<Número de la PDB>.pdb
```

## Correr el caso

1. Situarnos en la carpeta actual
2. Correr el comando:
```bash
make <Número de discos del caso>_disk_4peg_ToH.succ
```
3. Correr el archivo .succ con el comando:
```bash
<Número de discos del caso>_disk_4peg_ToH.succ instance.txt pdb_<Número de discos del caso>_disk
```


## PDBs usadas por cada caso

### Caso Torres de 12 discos
* pdb_12_disk_0 == Abstracción particionando los 9 discos más pequeños.
* pdb_12_disk_1 == Abstracción particionando los 10 discos más pequeños.
* pdb_12_disk_2 == Abstracción particionando los 11 discos más pequeños.
