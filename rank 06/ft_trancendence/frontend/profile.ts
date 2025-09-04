type Friend = string;
type GameType = '1v1' | '2v2';

interface GameResultRequest {
  username: string;
  gameType: GameType;
}

interface GameResultResponse {
  type: 'gameResults';
  gameType: GameType;
  results: any[]; // Replace with your actual GameResult or GameResult2v2
}

function getUsernameFromSessionToken(): string | null {
    const token = sessionStorage.getItem('authToken');
    if (!token) return null;
  
    try {
      const payloadBase64 = token.split('.')[1];
      const payload = JSON.parse(atob(payloadBase64));
      return payload.username || payload.sub || null; // Adjust based on your JWT payload
    } catch (err) {
      console.error('Failed to decode session token:', err);
      return null;
    }
  }

// === Request Friends ===
function requestFriendsOverSocket(): Promise<Friend[]> {
  return new Promise((resolve, reject) => {
    const socket = window.chatSocket;
    if (!socket || socket.readyState !== WebSocket.OPEN) {
      reject(new Error('Socket not connected'));
      return;
    }

    const onMessage = (event: MessageEvent) => {
      const msg = JSON.parse(event.data);
      if (msg.event === 'userRooms') {
        socket.removeEventListener('message', onMessage);
        resolve(msg.data.friends);
      }
    };

    socket.addEventListener('message', onMessage);

    socket.send(JSON.stringify({
      event: 'getUserRoomsAndFriends',
      data: {}
    }));

    setTimeout(() => {
      socket.removeEventListener('message', onMessage);
      reject(new Error('Timed out while waiting for friends list'));
    }, 3000);
  });
}

// === Request Match History ===
function requestGameResultsOverSocket(req: GameResultRequest): Promise<GameResultResponse> {
  return new Promise((resolve, reject) => {
    const socket = window.chatSocket;
    if (!socket || socket.readyState !== WebSocket.OPEN) {
      reject(new Error('Socket not connected'));
      return;
    }

    const onMessage = (event: MessageEvent) => {
      const msg = JSON.parse(event.data);
      if (msg.type === 'gameResults' && msg.gameType === req.gameType) {
        socket.removeEventListener('message', onMessage);
        resolve(msg);
      }
    };

    socket.addEventListener('message', onMessage);

    socket.send(JSON.stringify({
        event: 'getGameResults',
        data: {
          username: req.username,
          gameType: req.gameType
        }
      }));
      

    setTimeout(() => {
      socket.removeEventListener('message', onMessage);
      reject(new Error('Timed out while waiting for game results'));
    }, 3000);
  });
}

// === Render Friends ===
function renderFriends(friends: Friend[]) {
  const friendList = document.querySelector('#friendlist ul');
  if (!friendList) return;
  friendList.innerHTML = '';
  friends.forEach(friend => {
    const li = document.createElement('li');
    li.textContent = friend;
    friendList.appendChild(li);
  });
}

// === Render Match History ===
function renderMatchHistory(results: any[], containerId: string) {
    const container = document.querySelector(`#${containerId} ul`);
    if (!container) return;
  
    container.innerHTML = '';
  
    results.forEach(result => {
      const li = document.createElement('li');
  
      // Extract players and scores
      const p1 = result.player1;
      const p2 = result.player2;
      const score1 = result.P1result;
      const score2 = result.p2result;
  
      // Determine winner and loser
      let winner, loser, winnerScore, loserScore;
  
      if (score1 > score2) {
        winner = p1;
        winnerScore = score1;
        loser = p2;
        loserScore = score2;
      } else {
        winner = p2;
        winnerScore = score2;
        loser = p1;
        loserScore = score1;
      }
  
      // Create spans for coloring
      const winnerSpan = document.createElement('span');
      winnerSpan.textContent = winner;
      winnerSpan.style.color = 'green';
  
      const winnerScoreSpan = document.createElement('span');
      winnerScoreSpan.textContent = winnerScore.toString();
      winnerScoreSpan.style.color = 'green';
  
      const loserSpan = document.createElement('span');
      loserSpan.textContent = loser;
      loserSpan.style.color = 'red';
  
      const loserScoreSpan = document.createElement('span');
      loserScoreSpan.textContent = loserScore.toString();
      loserScoreSpan.style.color = 'red';
  
      // Construct the formatted result: "WinnerName WinnerScore : LoserScore LoserName"
      // But per your example, you want "username 5:0 username"
      // Let's keep order as p1 ... p2 but color winner/loser accordingly
  
      // Create the full text with spans
  
      li.appendChild(p1 === winner ? winnerSpan : loserSpan);
      li.appendChild(document.createTextNode(' '));
      li.appendChild(p1 === winner ? winnerScoreSpan : loserScoreSpan);
      li.appendChild(document.createTextNode(':'));
      li.appendChild(p2 === winner ? winnerScoreSpan : loserScoreSpan);
      li.appendChild(document.createTextNode(' '));
      li.appendChild(p2 === winner ? winnerSpan : loserSpan);
  
      container.appendChild(li);
    });
  }

  function renderMatchHistory2v2(results: any[], containerId: string) {
    const container = document.querySelector(`#${containerId} ul`);
    if (!container) return;
  
    container.innerHTML = '';
  
    results.forEach(result => {
      const li = document.createElement('li');
  
      const [p1Left, p2Left] = result.teamLeft;
      const [p1Right, p2Right] = result.teamRight;
      const scoreLeft = result.scoreLeft;
      const scoreRight = result.scoreRight;
      const resultText = result.result;
  
      let winnerTeam, loserTeam, winnerScore, loserScore;
      let winnerTeamIsLeft = false;
      if (scoreLeft > scoreRight) {
        winnerTeam = result.teamLeft;
        loserTeam = result.teamRight;
        winnerScore = scoreLeft;
        loserScore = scoreRight;
        winnerTeamIsLeft = true;
      } else {
        winnerTeam = result.teamRight;
        loserTeam = result.teamLeft;
        winnerScore = scoreRight;
        loserScore = scoreLeft;
      }
  
      // Clear li content in case
      li.innerHTML = '';
  
      // Create spans for teams and scores with colors
      const winnerSpan = document.createElement('span');
      winnerSpan.style.color = 'green';
      winnerSpan.textContent = `${winnerTeam.join(', ')} ${winnerScore}`;
  
      const loserSpan = document.createElement('span');
      loserSpan.style.color = 'red';
      loserSpan.textContent = `${loserScore} ${loserTeam.join(', ')}`;
  
      // Compose the final line: "WinnerTeam WinnerScore : LoserScore LoserTeam - result"
      li.appendChild(winnerSpan);
      li.appendChild(document.createTextNode(' : '));
      li.appendChild(loserSpan);
      li.appendChild(document.createTextNode(` - ${resultText}`));
  
      container.appendChild(li);
    });
  }
  
  
// === Load Everything Automatically ===
export async function loadFriendsAndMatchHistory(username: string) {
  try {
    const friends = await requestFriendsOverSocket();
    renderFriends(friends);

    const [oneVone, twoVtwo] = await Promise.all([
      requestGameResultsOverSocket({ username, gameType: '1v1' }),
      requestGameResultsOverSocket({ username, gameType: '2v2' }),
    ]);

    renderMatchHistory(oneVone.results, 'matchhistory1v1');
    renderMatchHistory2v2(twoVtwo.results, 'matchhistory2v2');
    
  } catch (err) {
    console.error('Error loading data:', err);
  }
}

const username = getUsernameFromSessionToken();
if (username) {
  loadFriendsAndMatchHistory(username);
} else {
  console.error('No username found in sessionStorage token');
}