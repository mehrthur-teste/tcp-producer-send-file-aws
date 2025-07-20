import json
import socket

# 1. Criar um JSON de exemplo
data = {
    "sensor": "temperature",
    "value": 23.5,
    "unit": "C",
    "timestamp": "2025-07-20T18:00:00"
}

# 2. Serializar para bytes
json_bytes = json.dumps(data).encode('utf-8')

# 3. Salvar em um arquivo binário
file_path = "dados.json.bin"
with open(file_path, "wb") as f:
    f.write(json_bytes)

# 4. Conectar ao servidor TCP (C++)
HOST = "127.0.0.1"
PORT = 9000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    
    # 5. Enviar o conteúdo do arquivo
    with open(file_path, "rb") as f:
        while True:
            chunk = f.read(1024)
            if not chunk:
                break
            s.sendall(chunk)

    print("Arquivo enviado com sucesso!")
     
