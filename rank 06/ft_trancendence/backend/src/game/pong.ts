import { FastifyPluginAsync } from 'fastify';
import { userSocketMap, userChannels } from '../chat/chatGateway';

interface TokenPayload {
  username: string;
}

type Player = {
  socket: any;
  username: string;
};

type GameResult2v2 = {
  teamLeft: [string, string];  // [player1, player2]
  teamRight: [string, string];
  scoreLeft: number;
  scoreRight: number;
  result: string; // e.g., 'normal win', 'disconnect win', 'teamRight won by disconnect'
};


type GameResult = {
  player1: string;
  player2: string;
  P1result: number;
  p2result: number;
  Gameresult: string; // Only one result per game (e.g., 'normal win', 'disconnect win')
};

let gameOver = false;

export const GameRecords2v2 = new Map<string, GameResult2v2[]>();
export const GameRecords = new Map<string, GameResult[]>();

export function recordGame2v2(
  teamLeft: [string, string],
  teamRight: [string, string],
  scoreLeft: number,
  scoreRight: number,
  result: string
) {
  const game: GameResult2v2 = {
    teamLeft,
    teamRight,
    scoreLeft,
    scoreRight,
    result
  };

  // Add to each player's history
  [...teamLeft, ...teamRight].forEach(username => {
    const history = GameRecords2v2.get(username) || [];
    history.push(game);
    GameRecords2v2.set(username, history);
  });
}

export function recordGame(
  player1: string,
  player2: string,
  P1result: number,
  p2result: number,
  result: string
) {
  const game: GameResult = {
    player1,
    player2,
    P1result,
    p2result,
    Gameresult: result,
  };

  const p1History = GameRecords.get(player1) || [];
  p1History.push(game);
  GameRecords.set(player1, p1History);

  const p2History = GameRecords.get(player2) || [];
  p2History.push(game);
  GameRecords.set(player2, p2History);
}


interface GameState {
  ball: { x: number; y: number; vx: number; vy: number };
  paddles: { [key: string]: number };
  scores: { left: number; right: number };
}

const waitingPlayers: Player[] = [];
const waitingPlayers2v2: Player[] = [];
const connectedPlayers = new Map<string, Player>();
const pendingFriendInvites = new Map<string, string>();


function resetBall(state: GameState, direction: 1 | -1) {
  state.ball.x = 300;
  state.ball.y = 1000;
  state.ball.vx = 5 * direction;
  state.ball.vy = 0;
}

function startGame2v2([p1, p2, p3, p4]: Player[]) {
  const WINNING_SCORE = 5;
  const gameOverFlag = { value: false };
  let cleanedUp = false;

  const gameState = {
    ball: { x: 300, y: 1000, vx: 5, vy: 0 },
    paddles: {
      left1: 900,
      left2: 1100,
      right1: 900,
      right2: 1100,
    },
    scores: { left: 0, right: 0 },
  };

  const players = [
    { socket: p1.socket, username: p1.username, role: 'left1' },
    { socket: p2.socket, username: p2.username, role: 'left2' },
    { socket: p3.socket, username: p3.username, role: 'right1' },
    { socket: p4.socket, username: p4.username, role: 'right2' },
  ];

  players.forEach(player => {
    player.socket.send(JSON.stringify({
      type: 'start 2v2',
      role: player.role,
      teammates: players.filter(p => p.role.includes('left') === player.role.includes('left')).map(p => p.username),
      opponents: players.filter(p => p.role.includes('left') !== player.role.includes('left')).map(p => p.username)
    }));
  });

  const inputs: Record<string, 'up' | 'down' | 'stop'> = {
    left1: 'stop',
    left2: 'stop',
    right1: 'stop',
    right2: 'stop',
  };

  players.forEach(({ socket, role }) => {
    socket.on('message', (msg: any) => {
      const data = JSON.parse(msg.toString());
      if (data.type === 'move') {
        inputs[role] = data.direction;
      }
    });
  });

  const interval = setInterval(() => {
    Object.entries(inputs).forEach(([role, direction]) => {
      if (direction === 'up') gameState.paddles[role] -= 15;
      if (direction === 'down') gameState.paddles[role] += 15;
    });

    Object.keys(gameState.paddles).forEach(role => {
      gameState.paddles[role] = Math.max(0, Math.min(gameState.paddles[role], 2000 - 150));
    });

    gameState.ball.x += gameState.ball.vx;
    gameState.ball.y += gameState.ball.vy;

    if (gameState.ball.y <= 0 || gameState.ball.y >= 2000) {
      gameState.ball.vy *= -1;
    }

    const checkCollision = (side: 'left' | 'right', xTarget: number, paddles: [string, string]) => {
      if (
        (gameState.ball.x <= xTarget && side === 'left') ||
        (gameState.ball.x >= xTarget && side === 'right')
      ) {
        for (const paddleKey of paddles) {
          const paddleY = gameState.paddles[paddleKey];
          if (gameState.ball.y >= paddleY && gameState.ball.y <= paddleY + 150) {
            gameState.ball.vx *= -1;
            const relativeY = (gameState.ball.y - paddleY) / 150;
            gameState.ball.vy = relativeY < 0.5 ? -5 : 5;
            return true;
          }
        }
      }
      return false;
    };

    checkCollision('left', 20, ['left1', 'left2']);
    checkCollision('right', 580, ['right1', 'right2']);

    if (gameState.ball.x < 0) {
      gameState.scores.right += 1;
      resetBall(gameState, -1);
    }
    if (gameState.ball.x > 600) {
      gameState.scores.left += 1;
      resetBall(gameState, 1);
    }

    if (gameState.scores.left >= WINNING_SCORE || gameState.scores.right >= WINNING_SCORE) {
      const winner = gameState.scores.left >= WINNING_SCORE ? 'left' : 'right';
      const winnerUsernames = players
        .filter(p => p.role.startsWith(winner))
        .map(p => p.username);

      const gameOverMessage = JSON.stringify({
        type: 'gameOver',
        winner,
        winnerUsernames
      });

      players.forEach(p => p.socket.send(gameOverMessage));

      // Record the game
      const teamLeft = players.filter(p => p.role.startsWith('left')).map(p => p.username) as [string, string];
      const teamRight = players.filter(p => p.role.startsWith('right')).map(p => p.username) as [string, string];
      
      recordGame2v2(teamLeft, teamRight, gameState.scores.left, gameState.scores.right, 'normal win');

      gameOverFlag.value = true;  // <-- mark game as ended normally
      
      cleanup();
      return;
      
    }

    const stateUpdate = JSON.stringify({
      type: 'state',
      ball: gameState.ball,
      paddles: gameState.paddles,
      scores: gameState.scores
    });

    players.forEach(p => p.socket.send(stateUpdate));
  }, 1000 / 30);

  // ✅ Cleanup logic
  cleanedUp = false;  // keep this outside cleanup so it persists

  function cleanup() {
    if (cleanedUp) return;
    cleanedUp = true;
  
    clearInterval(interval);
  
    if (!gameOverFlag.value) {
      // Find disconnected players
      const disconnectedPlayers = players.filter(p => !p.socket || p.socket.readyState === 3);
      const disconnectedUsernames = disconnectedPlayers.map(p => p.username);
  
      const teamLeft = players.filter(p => p.role.startsWith('left')).map(p => p.username) as [string, string];
      const teamRight = players.filter(p => p.role.startsWith('right')).map(p => p.username) as [string, string];
  
      let result = 'disconnect win';
      if (disconnectedUsernames.some(username => teamLeft.includes(username))) {
        result = 'teamRight won by disconnect';
      } else if (disconnectedUsernames.some(username => teamRight.includes(username))) {
        result = 'teamLeft won by disconnect';
      }
  
      recordGame2v2(teamLeft, teamRight, gameState.scores.left, gameState.scores.right, result);
    }
  
    players.forEach(({ socket }) => {
      try { socket.close(); } catch {}
    });
  }
  

  // Bind cleanup on any socket close
  players.forEach(({ socket }) => {
    socket.on('close', cleanup);
  });
}

function startGame(player1: Player, player2: Player) {
  const WINNING_SCORE = 5;

  const gameState: GameState = {
    ball: { x: 300, y: 1000, vx: 5, vy: 0 },
    paddles: { left: 1000, right: 1000 },
    scores: { left: 0, right: 0 }
  };

  player1.socket.send(JSON.stringify({ type: 'start', role: 'left', opponent: player2.username }));
  player2.socket.send(JSON.stringify({ type: 'start', role: 'right', opponent: player1.username }));

  const inputs = { left: 'stop', right: 'stop' };

  const handleMessage = (player: 'left' | 'right') => (msg: any) => {
    const data = JSON.parse(msg.toString());
    if (data.type === 'move') {
      inputs[player] = data.direction;
    }
  };

  player1.socket.on('message', handleMessage('left'));
  player2.socket.on('message', handleMessage('right'));

  const interval = setInterval(() => {
    if (inputs.left === 'up') gameState.paddles.left -= 15;
    if (inputs.left === 'down') gameState.paddles.left += 15;
    if (inputs.right === 'up') gameState.paddles.right -= 15;
    if (inputs.right === 'down') gameState.paddles.right += 15;

    const GAME_HEIGHT = 2000;
    const PADDLE_HEIGHT = 150;
    gameState.paddles.left = Math.max(0, Math.min(gameState.paddles.left, GAME_HEIGHT - PADDLE_HEIGHT));
    gameState.paddles.right = Math.max(0, Math.min(gameState.paddles.right, GAME_HEIGHT - PADDLE_HEIGHT));

    gameState.ball.x += gameState.ball.vx;
    gameState.ball.y += gameState.ball.vy;

    if (gameState.ball.y <= 0 || gameState.ball.y >= 2000) {
      gameState.ball.vy *= -1;
    }

    if (
      gameState.ball.x <= 20 &&
      gameState.ball.y >= gameState.paddles.left &&
      gameState.ball.y <= gameState.paddles.left + 150
    ) {
      gameState.ball.vx *= -1;
      const relativeY = (gameState.ball.y - gameState.paddles.left) / 150;
      gameState.ball.vy = relativeY < 0.5 ? -5 : 5;
    }

    if (
      gameState.ball.x >= 580 &&
      gameState.ball.y >= gameState.paddles.right &&
      gameState.ball.y <= gameState.paddles.right + 150
    ) {
      gameState.ball.vx *= -1;
      const relativeY = (gameState.ball.y - gameState.paddles.right) / 150;
      gameState.ball.vy = relativeY < 0.5 ? -5 : 5;
    }

    if (gameState.ball.x < 0) {
      gameState.scores.right += 1;
      resetBall(gameState, -1);
    }
    if (gameState.ball.x > 600) {
      gameState.scores.left += 1;
      resetBall(gameState, 1);
    }

    if (gameState.scores.left >= WINNING_SCORE || gameState.scores.right >= WINNING_SCORE) {
      const winner = gameState.scores.left >= WINNING_SCORE ? 'left' : 'right';
      const winnerUsername = winner === 'left' ? player1.username : player2.username;

      const gameOverMessage = JSON.stringify({
        type: 'gameOver',
        winner,
        winnerUsername
      });

      player1.socket.send(gameOverMessage);
      player2.socket.send(gameOverMessage);

      gameOver = true;

      recordGame(
        player1.username,
        player2.username,
        gameState.scores.left,
        gameState.scores.right,
        'normal win'
      );

      clearInterval(interval);
      return;
    }

    const stateUpdate = JSON.stringify({
      type: 'state',
      ball: gameState.ball,
      paddles: gameState.paddles,
      scores: gameState.scores
    });

    player1.socket.send(stateUpdate);
    player2.socket.send(stateUpdate);
  }, 1000 / 30);

  const cleanup = () => {
    clearInterval(interval);
  
    if (!gameOver) {
      const disconnectLoser = !player1.socket.readyState || player1.socket.readyState === 3
        ? player1.username
        : player2.username;
  
      const disconnectWinner = disconnectLoser === player1.username
        ? player2.username
        : player1.username;
  
      // Record a disconnect result
      recordGame(
        player1.username,
        player2.username,
        gameState.scores.left,
        gameState.scores.right,
        `${disconnectWinner} won by disconnect`
      );
    }
  
    try { player1.socket.close(); } catch {}
    try { player2.socket.close(); } catch {}
  };
  

  player1.socket.on('close', cleanup);
  player2.socket.on('close', cleanup);
}

export const pongGateway: FastifyPluginAsync = async (fastify) => {
  fastify.get('/pong', { websocket: true }, (socket, request) => {
    const url = new URL(request.url, 'http://localhost');
    const token = url.searchParams.get('token');

    let username = '';

    try {
      const payload = fastify.jwt.verify(token) as TokenPayload;
      username = payload.username;
      (socket as any).username = username;
      console.log(`User connected to Pong: ${username}`);
    } catch (err) {
      console.error('Invalid token');
      socket.close();
      return;
    }

    const player: Player = { socket, username };
    connectedPlayers.set(username, player);

    socket.send(JSON.stringify({ type: 'joined', message: 'Welcome to Pong' }));

    socket.on('message', (msg: any) => {
      const data = JSON.parse(msg.toString());

      if (data.type === 'friendInvite') {
        const friendId = data.friendId;
        const userInfo = userChannels.get(userSocketMap.get(username)!);
        if (!userInfo || !userInfo.friends.includes(friendId)) {
          socket.send(JSON.stringify({ type: 'error', message: 'User is not your friend' }));
          return;
        }

        const friendSocket = userSocketMap.get(friendId);
        if (!friendSocket) {
          socket.send(JSON.stringify({ type: 'error', message: 'Friend is not online' }));
          return;
        }

        pendingFriendInvites.set(friendId, username);

        friendSocket.send(JSON.stringify({
          event: 'pongInvite',
          data: { from: username }
        }));

        socket.send(JSON.stringify({ type: 'info', message: `Invite sent to ${friendId}` }));
      }

      if (data.type === 'friendAccept') {
        const inviterUsername = pendingFriendInvites.get(username);
        if (!inviterUsername) {
          socket.send(JSON.stringify({ type: 'error', message: 'No pending invite found' }));
          return;
        }

        const inviter = connectedPlayers.get(inviterUsername);
        const invitee = connectedPlayers.get(username);

        if (inviter && invitee) {
          pendingFriendInvites.delete(username);
          startGame(inviter, invitee);
        } else {
          socket.send(JSON.stringify({ type: 'error', message: 'Both players must be online' }));
        }
      }

      if (data.type === 'startMatchmaking') {
        waitingPlayers.push(player);

        if (waitingPlayers.length >= 2) {
          const p1 = waitingPlayers.shift()!;
          const p2 = waitingPlayers.shift()!;
          startGame(p1, p2);
        }
      }

      if (data.type === 'startMatchmaking2v2') {
        waitingPlayers2v2.push(player);
        console.log("check");
        if (waitingPlayers2v2.length >= 4) {
          const players = waitingPlayers2v2.splice(0, 4);
          startGame2v2(players);
        }
      }
    });

    socket.on('close', () => {
      connectedPlayers.delete(username);
      const i1 = waitingPlayers.findIndex(p => p.username === username);
      if (i1 !== -1) waitingPlayers.splice(i1, 1);

      const i2 = waitingPlayers2v2.findIndex(p => p.username === username);
      if (i2 !== -1) waitingPlayers2v2.splice(i2, 1);
    });
  });
};
