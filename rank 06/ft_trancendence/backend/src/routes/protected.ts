import { FastifyInstance } from 'fastify'

export default async function (app: FastifyInstance) {
  // This hook runs before the request handler
  app.addHook('onRequest', async (req, reply) => {
    try {
      await req.jwtVerify() // Verifies the token
    } catch (err) {
      reply.code(401).send({ error: 'Invalid or missing token.' })
    }
  })

  // Protected route
  app.get('/me', async (req, reply) => {
    // req.user contains the decoded JWT payload
    reply.send({ user: req.user })
  })
}
