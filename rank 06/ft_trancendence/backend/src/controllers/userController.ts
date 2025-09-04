// import { FastifyInstance } from 'fastify'
// import {
//   createUser,
//   findUserByUsername,
//   validatePassword
// } from '../services/userService'
// import { generateToken } from '../utils/jwt'
// import { User } from '../models/user'

// export async function userController(app: FastifyInstance) {
//   app.post('/register', async (req, reply) => {
//     const { username, email, password } = req.body as any
//     if (!username || !email || !password)
//       return reply.status(400).send({ error: 'Missing fields' })

//     try {
//       createUser(username, email, password)
//       return reply.send({ message: 'User created' })
//     } catch (err: any) {
//       return reply.status(400).send({ error: 'User already exists' })
//     }
//   })

//   app.post('/login', async (req, reply) => {
//     const { username, password } = req.body as any
//     const user = findUserByUsername(username) as User

//     if (!user || !validatePassword(user, password))
//       return reply.status(401).send({ error: 'Invalid credentials' })

//     const token = generateToken(app, { username: user.username })
//     return reply.send({ token })
//   })

//   app.get('/me', {
//     preHandler: [(app as any).authenticate]
//   }, async (req, reply) => {
//     const user = findUserByUsername((req.user as any).username) as User
//     if (!user) return reply.status(404).send({ error: 'User not found' })

//     const { password_hash, ...safeUser } = user
//     return reply.send(safeUser)
//   })
// }


import { FastifyInstance } from 'fastify'
import {
  createUser,
  findUserByUsername,
  validatePassword
} from '../services/userService'
import { generateToken } from '../utils/jwt'
import { User } from '../models/user'

export async function userController(app: FastifyInstance) {
  app.post('/register', async (req, reply) => {
    const { username, email, password } = req.body as any
    if (!username || !email || !password)
      return reply.status(400).send({ error: 'Missing fields' })

    try {
      createUser(username, email, password)
      return reply.send({ message: 'User created' })
    } catch (err: any) {
      return reply.status(400).send({ error: 'User already exists' })
    }
  })

  app.post('/login', async (req, reply) => {
    const { username, password } = req.body as any
    const user = findUserByUsername(username) as User

    if (!user || !validatePassword(user, password))
      return reply.status(401).send({ error: 'Invalid credentials' })

    const token = generateToken(app, { username: user.username })
    return reply.send({ token })
  })

  app.get('/me', {
    preHandler: [(app as any).authenticate]
  }, async (req, reply) => {
    const user = findUserByUsername((req.user as any).username) as User
    if (!user) return reply.status(404).send({ error: 'User not found' })

    const { password_hash, ...safeUser } = user

    // Add default avatar if none
    if (!safeUser.avatar_url) {
      safeUser.avatar_url = '/avatars/default.png'
    }

    return reply.send(safeUser)
  })
}
