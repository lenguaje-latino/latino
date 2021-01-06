# Descargar imagen
FROM debian:stable

# Instalar paquetes necesarios para compilacion
RUN apt-get update
RUN apt-get install -y --assume-yes \
	apt-utils \
	dialog
RUN apt-get install -y build-essential \
  cmake \
  libreadline-dev \
  sudo

# Crear usuario latino
RUN addgroup latino
RUN adduser latino --ingroup latino
RUN usermod -aG sudo latino
USER latino

# Crear directorios para copiar archivos
RUN mkdir /home/latino/codigo
RUN mkdir /home/latino/codigo/src
RUN mkdir /home/latino/codigo/src/linenoise
RUN mkdir /home/latino/codigo/include
RUN mkdir /home/latino/codigo/ejemplos

# Establecer directorio de trabajo
WORKDIR /home/latino/codigo

# Copiar solo los archivos necesarios para compilar y ejemplos de latino
COPY --chown=latino:latino CMakeLists.txt .
COPY --chown=latino:latino src/. src/
COPY --chown=latino:latino include/. include/
COPY --chown=latino:latino ejemplos/. ejemplos/

# Compilar latino e instalarlo
RUN cmake . && \
  make

# Ejecutar latino
WORKDIR /home/latino/codigo/src
CMD ["latino", "../ejemplos/02-hola.lat"]