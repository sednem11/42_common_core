import { FastifyPluginAsync } from 'fastify';
import { fetchRoomMessages, handleIncomingMessage } from './chatService';
import { saveMessage } from './messageStore';
import { joinRoom, leaveRoom } from './messageStore';
import { GameRecords2v2 } from '../game/pong';
import { GameRecords } from '../game/pong';


interface TokenPayload {
  username: string;
}

type friendsAndRooms = {
  friends: string[];
  rooms: string[];
  currentRoom?: string;
};

export const userSocketMap = new Map<string, WebSocket>();
export const userChannels = new Map<WebSocket, friendsAndRooms>();

// Optional: WebSocket type augmentation (if needed for TS)
interface ExtendedWebSocket extends WebSocket {
  username?: string;
}

export const chatGateway: FastifyPluginAsync = async (fastify) => {
  fastify.get('/chat', { websocket: true }, (socket, request) => {
    const url = new URL(request.url, 'http://localhost');
    const token = url.searchParams.get('token');

    let username = '';

    try {
      const payload = fastify.jwt.verify(token) as TokenPayload;
      username = payload.username;
      (socket as ExtendedWebSocket).username = username;
      console.log(`User connected: ${username}`);
    } catch (err) {
      console.error('Invalid token');
      socket.close();
      return;
    }

    userSocketMap.set(username, socket);

    socket.on('message', (raw) => {
      console.log('Received raw message:', raw.toString());

      try {
        const parsed = JSON.parse(raw.toString());

        switch (parsed.event) {
          case 'message': {
            const savedMessage = handleIncomingMessage(parsed.data);
            const room = parsed.data.room;
            
            for (const [clientSocket, data] of userChannels.entries()) {
              const clientUsername = (clientSocket as ExtendedWebSocket).username;
            
              const isDM = room.startsWith('@');
              const isCurrentRoom = data.currentRoom === room;

              const isDirectMessageToUser = room === `@${clientUsername}`;
              if (isDirectMessageToUser)
                  saveMessage(`@${parsed.data.user}`, parsed.data);
              if ((!isDM && isCurrentRoom) || (isDM && ((isDirectMessageToUser && data.currentRoom === `@${parsed.data.user}` ) || clientUsername === parsed.data.user))) {
                clientSocket.send(JSON.stringify({ event: 'message', data: savedMessage }));
              }
            }
            break;
          }
          case 'getGameResults': {
            const { username, gameType } = parsed.data;
          
            if (!username || !gameType) {
              socket.send(JSON.stringify({
                type: 'error',
                message: 'Missing username or gameType in getGameResults'
              }));
              return;
            }
          
            let results;
          
            if (gameType === '1v1') {
              results = GameRecords.get(username) || [];
            } else if (gameType === '2v2') {
              results = GameRecords2v2.get(username) || [];
            } else {
              socket.send(JSON.stringify({
                type: 'error',
                message: 'Invalid gameType. Must be "1v1" or "2v2"'
              }));
              return;
            }
          
            socket.send(JSON.stringify({
              type: 'gameResults',
              gameType,
              results
            }));
            break;
          }   
          case 'getPreviousMessages': {
            const roomName = parsed.data.room;
            const messages = fetchRoomMessages(roomName);
            socket.send(JSON.stringify({ event: 'previousMessages', data: messages }));
            break;
          }

          case 'getUserRoomsAndFriends': {
            const username = (socket as ExtendedWebSocket).username!;
            const rooms = getRoomsForUser(username, socket);
            const friends = getFriendsForUser(socket);
            socket.send(JSON.stringify({ event: 'userRooms', data: { rooms, friends } }));
            break;
          }

          case 'addFriend': {
            const requester = (socket as ExtendedWebSocket).username!;
            const friendUsername = parsed.data.friendUsername;
            const friendSocket = userSocketMap.get(friendUsername);
            
            if (!friendSocket) {
              console.log('No such person exists:', friendUsername);
              return;
            }

            friendSocket.send(JSON.stringify({ event: 'requestingFriend', data: { username: requester } }));
            break;
          }

          case 'respondFriendInvite': {
            const responder = (socket as ExtendedWebSocket).username!;
            const { from, accepted } = parsed.data;
            const fromSocket = userSocketMap.get(from);
          
            if (!fromSocket) {
              socket.send(JSON.stringify({ event: 'error', data: { message: 'User not found' } }));
              return;
            }
          
            if (accepted) {
              console.log(from);
              addFriendToUser(socket, from);     // Add friend to responder's friend list
              addFriendToUser(fromSocket, responder);  // Add responder to requester's friend list
          
              // Notify both users
              socket.send(JSON.stringify({ event: 'addingFriend', data: { username: from } }));
              fromSocket.send(JSON.stringify({ event: 'addingFriend', data: { username: responder } }));
            } else {
              // Notify requester that invite was declined
              fromSocket.send(JSON.stringify({ event: 'friendInviteDeclined', data: { username: responder } }));
            }
            break;
          }

          case 'ping': {
            socket.send(JSON.stringify({ event: 'pong' }));
            break;
          }

          case 'joinRoom': {
            const roomName = parsed.data.room;
            joinRoom(socket, roomName);
          
            const currentUsername = (socket as ExtendedWebSocket).username!;
            const messages = fetchRoomMessages(roomName);
          
            const senders = Array.from(new Set(messages.map((msg) => msg.user))).sort();
            const isUserAllowedInDM = senders.includes(currentUsername);
            const roomFromSenders = `@${senders.join(' ')}`; // Join with space instead of -
          
            const participants = roomName.replace(/^@/, '').split(' ');
            const isInRoomName = participants.includes(currentUsername);
          
            console.log(roomName);
            if (!roomName.startsWith('@') || isUserAllowedInDM || roomName === roomFromSenders || isInRoomName) {
              socket.send(JSON.stringify({ event: 'previousMessages', data: messages }));
            }
          
            break;
          }
          

          case 'leaveRoom': {
            const roomName = parsed.data.room;
            leaveRoom(socket, roomName);
            break;
          }

          default: {
            console.warn('Unknown event:', parsed.event);
            socket.send(JSON.stringify({ event: 'error', data: 'Unknown event type' }));
            break;
          }
        }
      } catch (err) {
        console.error('Failed to parse message:', err);
        socket.send(JSON.stringify({ event: 'error', data: 'Invalid message format' }));
      }
    });

    socket.on('close', () => {
      console.log(`Client ${username} disconnected`);
      userSocketMap.delete(username);
      userChannels.delete(socket);
    });

    socket.on('error', (error) => {
      console.error('WebSocket error:', error);
    });

    socket.on('pong', () => {
      console.log('Pong received');
    });
  });
};

function getRoomsForUser(username: string, socket: WebSocket): string[] {
  const entry = userChannels.get(socket);

  if (entry) return entry.rooms;

  const defaultRooms = ['general'];
  userChannels.set(socket, {
    rooms: defaultRooms,
    friends: [],
    currentRoom: 'general',
  });
  return defaultRooms;
}

function getFriendsForUser(socket: WebSocket): string[] {
  const entry = userChannels.get(socket);
  return entry?.friends ?? [];
}

function addFriendToUser(socket: WebSocket, friendUsername: string) {
  const data = userChannels.get(socket) ?? { friends: [], rooms: [] };
  if (!data.friends.includes(friendUsername)) {
    data.friends.push(friendUsername);
  }
  userChannels.set(socket, data);
}
