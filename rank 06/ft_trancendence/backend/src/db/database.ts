// backend/src/db/database.ts
import Database from 'better-sqlite3'
import path from 'path'

const dbPath = path.join(__dirname, 'data.db')
const db = new Database(dbPath)

db.prepare(`
  CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    google_id TEXT UNIQUE,
    email TEXT,
    username TEXT,
    avatar_url TEXT,
    password TEXT
  )
`).run()


export default db
