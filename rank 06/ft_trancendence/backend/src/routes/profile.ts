// import { FastifyInstance } from 'fastify'
// import { updateUserProfile } from '../services/userService'
// import { User } from '../models/user'

// export async function profileRoutes(app: FastifyInstance) {
//   app.put('/profile', {
//     preHandler: [(app as any).authenticate]
//   }, async (req, reply) => {
//     const username = (req.user as any).username
//     const { email, password } = req.body as any

//     try {
//       const updatedUser = updateUserProfile(username, { email, password }) as User
//       const { password_hash, ...safeUser } = updatedUser
//       reply.send(safeUser)
//     } catch (err) {
//       reply.status(400).send({ error: 'Failed to update profile' })
//     }
//   })
// }


import { FastifyInstance } from 'fastify'
import { updateUserProfile } from '../services/userService'
import { User } from '../models/user'

interface ProfileUpdateRequest {
  email?: string
  password?: string
}

export async function profileRoutes(app: FastifyInstance) {
  app.put('/profile', {
    preHandler: [(app as any).authenticate]
  }, async (req, reply) => {
    const username = (req.user as any).username
    const { email, password } = req.body as ProfileUpdateRequest

    try {
      const updatedUser = updateUserProfile(username, { email, password })
      const { password_hash, ...safeUser } = updatedUser
      reply.send(safeUser)
    } catch (err) {
      reply.status(400).send({ error: 'Failed to update profile' })
    }
  })
}
