import { FastifyRequest, FastifyReply } from 'fastify'
import speakeasy from 'speakeasy'
import qrcode from 'qrcode'

// guardar na DB associada ao user dps
const user2FASecrets: Record<string, string> = {}

export async function setup2FA(req: FastifyRequest, reply: FastifyReply) {
  const user = req.user as { id: string }
  const userId = user.id
  const secret = speakeasy.generateSecret({
    name: `ft_transcendence (${userId})`
  })

  user2FASecrets[userId] = secret.base32

  const otpauth_url = secret.otpauth_url!
  const qrCodeDataURL = await qrcode.toDataURL(otpauth_url)

  reply.send({ qrCodeDataURL, secret: secret.base32 })
}

export async function verify2FA(req: FastifyRequest, reply: FastifyReply) {
  const user = req.user as { id: string }
  const userId = user.id
  const { token } = req.body as { token: string }

  const secret = user2FASecrets[userId]
  if (!secret) return reply.code(400).send({ error: '2FA not setup' })

  const verified = speakeasy.totp.verify({
    secret,
    encoding: 'base32',
    token,
    window: 1
  })

  if (verified) {
    reply.send({ verified: true })
  } else {
    reply.code(401).send({ error: 'Invalid 2FA token' })
  }
}
