export interface User {
  id: number
  username: string
  email: string
  password_hash: string
  avatar_url: string | null
  wins: number
  losses: number
  created_at: string
}