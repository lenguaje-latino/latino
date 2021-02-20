# Comandos para correr latino en Docker

## Crear imagen
`docker build --pull --rm -f "Dockerfile" -t latino:latest "."`

## Ejecutar docker
`docker run --rm -dit --name latino latino:latest sh`
### Despliega algo como lo siguiente:
### 457bd54046b023678cf2f5d9b1631578fc7f42438da52c29c97cf03467493284

## correr bash
### copiar el id anterior y pegarlo a continuacion
`docker exec -it 457bd54046b023678cf2f5d9b1631578fc7f42438da52c29c97cf03467493284 bash`

# Ejecutar latino REPL
`./latino`

# Ejecutar un archivo de los ejemplos
`./latino ../ejemplos/02-hola.lat`