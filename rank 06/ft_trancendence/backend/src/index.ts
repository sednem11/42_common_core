import Fastify from 'fastify'
import jwt from '@fastify/jwt'
import dotenv from 'dotenv'
import authRoutes from './routes/auth'
import protectedRoutes from './routes/protected'
import websocket from '@fastify/websocket'
import staticPlugin from '@fastify/static';
import path from 'path';
import { chatGateway } from './chat/chatGateway'
import { pongGateway } from './game/pong'




dotenv.config()

console.log('JWT_SECRET:', process.env.JWT_SECRET)

async function buildServer() {
  const app = Fastify({ logger: true})

  app.register(staticPlugin, {
    root: path.join(__dirname, '../../frontend'),
    prefix: '/', // serve files at the root
    index: 'login.html', // serve index.html for root
  });

  app.register(staticPlugin, {
    root: path.join(__dirname, '../../frontend/dist'), // serve compiled JS files
    prefix: '/dist/',                          // accessible via /dist/...
    decorateReply: false,
  });

  await app.register(websocket);

  await app.register(jwt, {
    secret: process.env.JWT_SECRET as string,                    // Plugin JWT
  })
  
  await app.register(authRoutes, { prefix: '/auth' })            // auth (ex: /auth/login, /auth/register)
  await app.register(chatGateway, { prefix: '/ws'});
  await app.register(protectedRoutes, { prefix: '/protected' })
  await app.register(pongGateway, { prefix: '/game' });

  app.get('/ping', async () => {
    return { pong: true }                                        // Test
  })
  
  app.ready().then(() => {
    console.log(app.printRoutes());
  });
  app.listen({ port: 3000, host: '0.0.0.0' }, (err, address) => {
  if (err) throw err
  console.log(`Servidor a correr em: ${address}`)
  })
  // app.listen({ port: 3000 }, (err, address) => {
  //     if (err) throw err                                        // server
  //   console.log(`Servidor a correr em: ${address}`)
  // })
  
}
buildServer();

