# 1. Imagem base com CMake e compilador
FROM debian:bullseye-slim

# 2. Instala dependências (g++, cmake)
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

# 3. Cria diretório de trabalho
WORKDIR /app

# 4. Copia o projeto para dentro do container
COPY . .

# 5. Cria pasta de build
RUN mkdir -p build

# 6. Compila com CMake
RUN cd build && cmake .. && make

# 7. Define comando padrão
CMD ["./build/main_app"]
