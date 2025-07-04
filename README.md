# pipex


## Enunciado

![Screenshot from 2025-07-02 13-03-54](https://github.com/user-attachments/assets/d5bd3e52-2e9d-49ba-bf9e-da269c1a95e6)

La finalidad del programa es simular el comportamiento del comando shell`< archivo1 comando1 | comando2 > archivo2`, tanto en la ejecución de comandos como manejo de errores.

## Requisitos

- Debe tener 4 argumentos (sin contar la ejecución del programa). La evaluación indica que ni más ni menos, no obstante, mi versión del programa maneja un solo comando. Así mismo, el bonus pide que se manejen varios comandos.
- Debe tener un Makefile que compile los archivos fuente. No debe hacer relink.
- Debe gestionar los errores minuciosamente. De ninguna forma tu programa debe
salir de forma inesperada (segmentation fault, bus error, double free, y similares).

## Ejemplos

El infile contiene este texto :

```
hola que tal
MariCarrmen, la gente está muy
agobiada
```

1. **grep hola | wc -l**
    
    `grep hola` busca las lineas con hola en infile, el resultado se pasa por el pipe a `wc -l`, este comando cuenta cuantas lineas ha recibido.
    
    ```bash
    ~/pipexGit % ./pipex infile "grep 'hola'"  "wc -l"  outfile
    ~/pipexGit % cat outfile
    1
    ~/pipexGit % < infile grep hola | wc -l > outfile
    ~/pipexGit % cat outfile
    1
    ```
    
2. **cat | grep gente**
    
    `cat` imprime el contenido de infile, el resultado se pasa por el pipe a `grep gente`, las lineas que contienen gente se pasan a outfile.
    
    ```bash
    ~/pipexGit % < infile cat | grep gente > outfile
    ~/pipexGit % cat outfile
    MariCarrmen, la gente está muy
     ~/pipexGit % ./pipex infile "cat" "grep gente" outfile
     ~/pipexGit % cat outfile
    MariCarrmen, la gente está muy
    ```
3. **ls -l | wc -l**

    `ls -l` ignora la stdin (infile no se usa), muestra listado del directorio actual. `wc -l`cuenta cuantas lineas    hay, el numero se escribe en outfile
    ```bash
    < infile ls -l | wc -l > outfile
    ./pipex infile "ls -l" "wc -l" outfile

    mregada-@cbr13s6 ~/prueba % < infile ls -l | wc -l > outfile
    mregada-@cbr13s6 ~/prueba % cat outfile 
    15
    mregada-@cbr13s6 ~/prueba % ./pipex infile "ls -l" "wc -l" outfile        
    mregada-@cbr13s6 ~/prueba % cat outfile 
    15
    ```
4. 4. **head -n 3 | tail -n 1**
    
    ```bash
    < infile head -n 3 | tail -n 1 > outfile
    ./pipex infile "head -n 3" "tail -n 1" outfile 
    ```
    
    `head -n 3` obtiene las **primeras 3 líneas** del `infile`.`tail -n 1` se queda con **la tercera línea**.Esta se guarda en `outfile`.

    ![imagen](https://github.com/user-attachments/assets/587cc7bf-4e62-4f76-a3b5-e404cc718145)

