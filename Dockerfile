# Descargar imagen
FROM debian:stable

# Instalar paquetes necesarios para compilacion
RUN apt-get update
RUN apt-get install -y --assume-yes \
	apt-utils \
	dialog
RUN apt-get install -y build-essential \
  cmake libreadline-dev sudo

# Crear usuario latino
RUN adduser --disabled-password --gecos '' docker
RUN adduser docker sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER docker

# Crear directorios para copiar archivos
RUN mkdir /home/docker/codigo
RUN mkdir /home/docker/codigo/src
RUN mkdir /home/docker/codigo/include
RUN mkdir /home/docker/codigo/ejemplos

# Establecer directorio de trabajo
WORKDIR /home/docker/codigo

# Copiar solo los archivos necesarios para compilar y ejemplos de latino
COPY --chown=docker:docker CMakeLists.txt .
COPY --chown=docker:docker src/. src/
COPY --chown=docker:docker include/. include/
COPY --chown=docker:docker ejemplos/. ejemplos/

# Compilar latino e instalarlo
RUN cmake . && \
make
RUN sudo make install

# Ejecutar latino
WORKDIR /home/docker/codigo/src
CMD ["latino", "../ejemplos/02-hola.lat"]