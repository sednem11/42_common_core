import { FastifyInstance } from 'fastify'

interface TokenPayload {
  username: string
}

export function generateToken(app: FastifyInstance, payload: TokenPayload): string {
  return app.jwt.sign(payload)
}
