import { FastifyRequest, FastifyReply } from 'fastify'
import bcrypt from 'bcrypt'
import db from '../db/database'

export async function register(req: FastifyRequest, reply: FastifyReply) {
  const { username, password } = req.body as { username: string; password: string }

  if (!username || !password)
    return reply.code(400).send({ error: 'Username and password are required.' })

  const existing = db.prepare('SELECT * FROM users WHERE username = ?').get(username)
  if (existing)
    return reply.code(400).send({ error: 'Username already exists.' })

  const hashedPassword = await bcrypt.hash(password, 10)

  db.prepare(`
    INSERT INTO users (username, password)
    VALUES (?, ?)
  `).run(username, hashedPassword)

  reply.send({ message: 'User successfully registered.' })
}

export async function login(req: FastifyRequest, reply: FastifyReply) {
  const { username, password } = req.body as { username: string; password: string }

  const user = db.prepare('SELECT * FROM users WHERE username = ?').get(username) as {
    id: number
    username: string
    password: string
    two_factor_enabled?: number
  }

  if (!user)
    return reply.code(401).send({ error: 'User not found.' })

  const valid = await bcrypt.compare(password, user.password)
  if (!valid)
    return reply.code(401).send({ error: 'Incorrect password.' })

  const twoFactorEnabled = user.two_factor_enabled === 1

  if (twoFactorEnabled) {
    const tempToken = reply.server.jwt.sign({
      id: user.id,
      username: user.username,
      requires2FA: true,
    })
    return reply.send({ requires2FA: true, token: tempToken })
  } else {
    const token = reply.server.jwt.sign({
      id: user.id,
      username: user.username,
      requires2FA: false,
    })
    return reply.send({ requires2FA: false, token })
  }
}
