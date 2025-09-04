FROM node:18

WORKDIR /ft_transcendence

# Copia os arquivos de dependências do root (onde está o package.json)
COPY package*.json ./

# Instala as dependências no root
RUN npm install

# Copia todo o projeto para a imagem
COPY . .

RUN npm install -g typescript


# Compila o frontend TypeScript
CMD ["npx", "tsc", "--project", "frontend/tsconfig.json"]
