// import Database from 'better-sqlite3'
// import bcrypt from 'bcryptjs'

// const db = new Database('./db.sqlite')

// export function createUserTable() {
//   db.prepare(`
//     CREATE TABLE IF NOT EXISTS users (
//       id INTEGER PRIMARY KEY AUTOINCREMENT,
//       username TEXT UNIQUE NOT NULL,
//       email TEXT UNIQUE NOT NULL,
//       password_hash TEXT NOT NULL,
//       avatar_url TEXT,
//       wins INTEGER DEFAULT 0,
//       losses INTEGER DEFAULT 0,
//       created_at TEXT DEFAULT CURRENT_TIMESTAMP
//     )
//   `).run()
// }

// export function createUser(username: string, email: string, password: string) {
//   const hash = bcrypt.hashSync(password, 10)
//   const stmt = db.prepare(`
//     INSERT INTO users (username, email, password_hash)
//     VALUES (?, ?, ?)
//   `)
//   stmt.run(username, email, hash)
// }

// export function findUserByUsername(username: string) {
//   return db.prepare(`SELECT * FROM users WHERE username = ?`).get(username)
// }

// export function validatePassword(user: any, password: string) {
//   return bcrypt.compareSync(password, user.password_hash)
// }

// export function getUserStats(username: string) {
//   return db.prepare(`
//     SELECT wins, losses FROM users WHERE username = ?
//   `).get(username)
// }


import Database from 'better-sqlite3'
import bcrypt from 'bcryptjs'
import { User } from '../models/user'

const db = new Database('./db.sqlite')

export function createUserTable() {
  db.prepare(`
    CREATE TABLE IF NOT EXISTS users (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      username TEXT UNIQUE NOT NULL,
      email TEXT UNIQUE NOT NULL,
      password_hash TEXT NOT NULL,
      avatar_url TEXT,
      wins INTEGER DEFAULT 0,
      losses INTEGER DEFAULT 0,
      created_at TEXT DEFAULT CURRENT_TIMESTAMP
    )
  `).run()

  db.prepare(`
    CREATE TABLE IF NOT EXISTS matches (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      winner TEXT NOT NULL,
      loser TEXT NOT NULL,
      played_at TEXT DEFAULT CURRENT_TIMESTAMP
    )
  `).run()
}

export function createUser(username: string, email: string, password: string) {
  const hash = bcrypt.hashSync(password, 10)
  const stmt = db.prepare(`
    INSERT INTO users (username, email, password_hash)
    VALUES (?, ?, ?)
  `)
  stmt.run(username, email, hash)
}

export function findUserByUsername(username: string): User {
  return db.prepare(`SELECT * FROM users WHERE username = ?`).get(username) as User
}

export function validatePassword(user: User, password: string) {
  return bcrypt.compareSync(password, user.password_hash)
}

export function getUserStats(username: string) {
  return db.prepare(`
    SELECT wins, losses FROM users WHERE username = ?
  `).get(username)
}

export function addMatch(winner: string, loser: string) {
  const stmt = db.prepare('INSERT INTO matches (winner, loser) VALUES (?, ?)')
  stmt.run(winner, loser)
}

export function getMatchHistory(username: string) {
  const stmt = db.prepare(`
    SELECT * FROM matches
    WHERE winner = ? OR loser = ?
    ORDER BY played_at DESC
  `)
  return stmt.all(username, username)
}

export function updateUserProfile(
  username: string,
  updates: { email?: string; password?: string; avatar_url?: string }
): User {
  if (updates.email) {
    db.prepare(`UPDATE users SET email = ? WHERE username = ?`)
      .run(updates.email, username)
  }

  if (updates.password) {
    const hash = bcrypt.hashSync(updates.password, 10)
    db.prepare(`UPDATE users SET password_hash = ? WHERE username = ?`)
      .run(hash, username)
  }

  if (updates.avatar_url) {
    db.prepare(`UPDATE users SET avatar_url = ? WHERE username = ?`)
      .run(updates.avatar_url, username)
  }

  return findUserByUsername(username)
}
