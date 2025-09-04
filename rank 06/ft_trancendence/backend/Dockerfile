# # backend/Dockerfile
# FROM node:18

# WORKDIR /app

# # Copy backend dependency definitions
# COPY package*.json ./

# # Install backend dependencies (bcryptjs, ts-node-dev, etc.)
# RUN npm install

# # Copy the rest of the backend source
# COPY . .

# # Run the backend server
# CMD ["npx", "ts-node-dev", "backend/src/index.ts"]


# FROM node:18

# WORKDIR /app

# # Install only backend dependencies
# COPY package*.json ./
# RUN npm install

# # Copy entire project
# COPY . .

# # Optional: if you ever add a frontend build step, do it here
# # WORKDIR /app/frontend
# # RUN npm install && npm run build

# WORKDIR /app

# CMD ["npx", "ts-node-dev", "backend/src/index.ts"]

# FROM node:18

# WORKDIR /app

# COPY package*.json ./
# RUN npm install

# COPY . .

# # No attempt to enter or build frontend
# # This is just backend setup

# CMD ["npx", "ts-node-dev", "backend/src/index.ts"]

# FROM node:18

# # Create app directory
# WORKDIR /app

# # Copy only package files first for caching
# COPY package*.json ./
# RUN npm install

# # Copy the whole project (frontend + backend)
# COPY . .

# # Install and build frontend
# WORKDIR /app/frontend
# RUN npm install && npm run build

# # Back to backend root
# WORKDIR /app

# # Start the backend
# CMD ["npx", "ts-node-dev", "backend/src/index.ts"]

# # backend/Dockerfile
# FROM node:18

# WORKDIR /app

# # Install only backend dependencies
# COPY package*.json ./
# RUN npm install

# # Copy all backend source files
# COPY . .

# # Start the server with ts-node-dev (no tsc build)
# CMD ["npx", "ts-node-dev", "backend/src/index.ts"]



# # backend/Dockerfile
# FROM node:18

# WORKDIR /app

# # Install backend deps first
# COPY package*.json ./
# RUN npm install

# # Copy everything else
# COPY . .

# # Build frontend
# WORKDIR /app/frontend
# RUN npm install && npm run build-force

# # Back to backend
# WORKDIR /app
# CMD ["npx", "ts-node-dev", "backend/src/index.ts"]




FROM node:18

WORKDIR /ft_transcendence

COPY package*.json ./
RUN npm install

COPY . .

CMD ["npx", "ts-node-dev", "backend/src/index.ts"]
