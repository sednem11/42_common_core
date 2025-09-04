import { userChannels } from './chatGateway';


type Message = {
    user: string
    room: string
    text: string
    timestamp: number
  }
  
  const messageStore: Record<string, Message[]> = {
    general: [],
  }

  const rooms: Map<string, Set<WebSocket>> = new Map([
    ['general', new Set()],
  ]);
  
  export function saveMessage(room: string, message: Message) {
    if (!messageStore[room]) {
      messageStore[room] = []
    }
    messageStore[room].push(message)
  }
  
  export function getMessages(room: string): Message[] {
    return messageStore[room] || []
  }

  export function joinRoom(socket: WebSocket, roomName: string) {
    if (!rooms.has(roomName)) {
      rooms.set(roomName, new Set());
    }
    rooms.get(roomName)!.add(socket);
    const userData = userChannels.get(socket);
    if (userData) {
      userData.currentRoom = roomName;
      userChannels.set(socket, userData);
    }
  }
  
  // Remove a socket from a room
  export function leaveRoom(socket: WebSocket, roomName: string) {
    const room = rooms.get(roomName);
    if (room) {
      room.delete(socket);
      if (room.size === 0) {
        rooms.delete(roomName); // Optional: delete empty rooms
      }
    }
  }
  