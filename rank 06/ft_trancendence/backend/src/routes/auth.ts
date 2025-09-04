import { FastifyInstance } from 'fastify'
import { register, login } from '../controllers/authController'
import { googleAuth } from '../controllers/googleController'
import { authenticate } from '../middlewares/authenticate'
import { setup2FA, verify2FA } from '../controllers/twoFactorController'

export default async function (app: FastifyInstance) {
  app.post('/register', register)
  app.post('/login', login)
  app.post('/google', googleAuth)

  app.get('/2fa/setup', { preValidation: [authenticate] }, setup2FA)
  app.post('/2fa/verify', { preValidation: [authenticate] }, verify2FA)

  app.get('/profile', { preValidation: [authenticate] }, async (req, reply) => {
    const user = req.user as { id: number; username: string; email: string }
    reply.send({
      id: user.id,
      username: user.username,
      email: user.email
    })
  })

}
