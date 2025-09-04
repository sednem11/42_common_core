import { FastifyInstance } from 'fastify'
import fs from 'fs'
import path from 'path'
import { findUserByUsername } from '../services/userService'
import Database from 'better-sqlite3'

export async function avatarRoutes(app: FastifyInstance) {
  app.post('/avatar', {
    preHandler: [(app as any).authenticate],
  }, async (req, reply) => {
    const data = await req.file()

    if (!data) {
      return reply.status(400).send({ error: 'No file uploaded' })
    }

    const ext = path.extname(data.filename)
    const username = (req.user as any).username
    const newFileName = `${username}${ext}`
    const savePath = path.join(__dirname, '..', 'public', 'avatars', newFileName)

    const buffer = await data.toBuffer()
    fs.writeFileSync(savePath, buffer)

    // Save avatar URL to DB
    const db = new Database('./db.sqlite')
    db.prepare('UPDATE users SET avatar_url = ? WHERE username = ?')
      .run(`/avatars/${newFileName}`, username)

    reply.send({ message: 'Avatar uploaded', avatar: `/avatars/${newFileName}` })
  })
}
