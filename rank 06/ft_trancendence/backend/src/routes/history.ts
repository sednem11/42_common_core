import { FastifyInstance } from 'fastify'
import { getMatchHistory, addMatch } from '../services/userService'

export async function historyRoutes(app: FastifyInstance) {
  // ✅ Authenticated route to get user's match history
  app.get('/history', {
    preHandler: [(app as any).authenticate]
  }, async (req, reply) => {
    const username = (req.user as any).username
    const history = getMatchHistory(username)
    reply.send(history)
  })

  // 🛠 Temporary route to insert test matches manually
  app.post('/history/test', async (req, reply) => {
    const { winner, loser } = req.body as any
    if (!winner || !loser) {
      return reply.status(400).send({ error: 'Missing winner or loser' })
    }
    addMatch(winner, loser)
    reply.send({ message: 'Match recorded!' })
  })
}
