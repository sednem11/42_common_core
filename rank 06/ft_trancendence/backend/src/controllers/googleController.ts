import { FastifyRequest, FastifyReply } from 'fastify'
import { OAuth2Client } from 'google-auth-library'
import db from '../db/database'  // <-- Importa aqui o db

const client = new OAuth2Client(process.env.GOOGLE_CLIENT_ID)

type User = {
  id: number
  username: string
  email: string
  two_factor_secret?: string | null
}

export async function googleAuth(req: FastifyRequest, reply: FastifyReply) {
  const { id_token } = req.body as { id_token: string }

  if (!id_token) {
    return reply.code(400).send({ error: 'Missing Google ID token' })
  }

  let payload: any
  try {
    const ticket = await client.verifyIdToken({
      idToken: id_token,
      audience: process.env.GOOGLE_CLIENT_ID,
    })
    payload = ticket.getPayload()
  } catch (err) {
    return reply.code(401).send({ error: 'Invalid Google token' })
  }

  if (!payload || !payload.email) {
    return reply.code(401).send({ error: 'Invalid token payload' })
  }

  const email = payload.email
  const username = payload.name || email.split('@')[0]

  let user = db.prepare('SELECT * FROM users WHERE email = ?').get(email) as User | undefined

  if (!user) {
    const result = db.prepare('INSERT INTO users (username, email) VALUES (?, ?)').run(username, email)
    user = {
      id: Number(result.lastInsertRowid),
      username,
      email,
    }
  }

  const token = reply.server.jwt.sign({
    id: user.id,
    username: user.username,
    email: user.email,
    requires2FA: true,
  })

  const requires2FA = !!user.two_factor_secret

  reply.send({ token, requires2FA })
}
