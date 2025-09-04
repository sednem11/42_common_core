import { FastifyInstance } from 'fastify'
import { getUserStats } from '../services/userService'

export async function statsRoutes(app: FastifyInstance) {
  app.get('/stats/:username', async (req, reply) => {
    const { username } = req.params as any
    const stats = getUserStats(username)

    if (!stats) return reply.status(404).send({ error: 'User not found' })
    return reply.send(stats)
  })
}