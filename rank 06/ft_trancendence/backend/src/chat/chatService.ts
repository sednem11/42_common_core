import { saveMessage, getMessages } from './messageStore'

type IncomingMessage = {
  user: string
  room: string
  text: string
}

export function handleIncomingMessage(msg: IncomingMessage) {
  const message = {
    ...msg,
    timestamp: Date.now()
  }

  saveMessage(msg.room, message)

  return message
}

export function fetchRoomMessages(room: string) {
  return getMessages(room)
}