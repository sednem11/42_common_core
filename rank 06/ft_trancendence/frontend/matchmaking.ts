const startBtn = document.getElementById('startMatchmaking') as HTMLButtonElement;
const startBtn2v2 = document.getElementById('startMatchmaking2v2') as HTMLButtonElement;
const cancelBtn = document.getElementById('cancelMatchmaking') as HTMLButtonElement;
const FriendInvite = document.getElementById('inviteFriend') as HTMLButtonElement;
// const FriendMatch = document.getElementById('FriendMatch')!;
const statusText = document.getElementById('matchStatus')!;
const matchResult = document.getElementById('matchResult')!;
const gameContainer = document.getElementById('gameContainer')!;
const matchmaking = document.getElementById('matchmaking');

export function initMatchmaking() {
  console.log("🔁 Initializing matchmaking setup");

  let socket: WebSocket | null = null;
  let cleanup: (() => void) | null = null; // Declare cleanup function outside

  const toggleElements = [
    '#matchmakingView',
  ];

  if (!startBtn2v2 || !startBtn || !cancelBtn) {
    console.warn("Matchmaking buttons not found.");
    return;
  }

  FriendInvite.addEventListener('click', async () => {
    const token = sessionStorage.getItem('authToken');
    if (!token) {
      alert('No auth token found');
      return;
    }

    statusText.textContent = 'waiting for Friend';
    FriendInvite.style.display = 'none';
    startBtn.style.display = 'none';
    socket = new WebSocket(`ws://localhost:3000/game/pong?token=${token}`);

    socket.onopen = () => {
      console.log('🔌 Connected to matchmaking');
      const friendId = (document.getElementById('FriendMatchInput') as HTMLInputElement)?.value;
      socket!.send(JSON.stringify({ type: 'friendInvite', friendId }));
    };

    socket.addEventListener('message', async (event) => {
      const data = JSON.parse(event.data);

      if (data.type === 'start') {
        console.log('🎮 Match found, starting game...');

        toggleElements.forEach((selector) => {
          const el = matchmaking?.querySelector(selector) as HTMLElement;
          if (el) {
            const isHidden = getComputedStyle(el).display === 'none';
            el.style.display = isHidden ? 'block' : 'none';
          }
        });

        // Await the fetch and text reading
        const res = await fetch('game.html');
        const html = await res.text();
        gameContainer.innerHTML = html;
        gameContainer.classList.remove('hidden');

        const canvas = gameContainer.querySelector('#gameCanvas') as HTMLCanvasElement;
        if (canvas) {
          // Await dynamic import
          const { default: initGame } = await import('./game.js') as any;
          console.log("check2");
          cleanup = initGame(canvas, socket);
        }
      }
      else if (data.type === 'gameOver') {
        console.log("message received");
        alert(`🏆 Game Over! Winner: ${data.winner.toUpperCase()}`);
        console.log("🏁 Game ended. Cleaning up...");
        if (cleanup) cleanup();
        socket?.close();
        resetUI();
      }
      else if (data.type === 'end') {
        console.log("🏁 Game ended. Cleaning up...");
        if (cleanup) cleanup();
        socket?.close();
        resetUI();
      }
      else if (data.type === 'error')
      {
        alert(data.message);
        resetUI();
        socket?.close();
      }
    });

    socket.onerror = (err) => {
      console.error('WebSocket error:', err);
      statusText.textContent = '❌ WebSocket error. Try again.';
      resetUI();
    };

    socket.onclose = () => {
      console.log('🔌 WebSocket closed');
      resetUI();
    };

  });

  startBtn2v2.addEventListener('click', async () => {
    const token = sessionStorage.getItem('authToken');
    if (!token) {
      alert('No auth token found');
      return;
    }
  
    statusText.textContent = '🔍 Searching for 2v2 match...';
    FriendInvite.style.display = 'none';
    startBtn.style.display = 'none';
    startBtn2v2.style.display = 'none';
    cancelBtn.classList.remove('hidden');
  
    socket = new WebSocket(`ws://localhost:3000/game/pong?token=${token}`);
  
    socket.onopen = () => {
      console.log('🔌 Connected to matchmaking (2v2)');
      socket!.send(JSON.stringify({ type: 'startMatchmaking2v2' }));
    };
  
    socket.addEventListener('message', async (event) => {
      const data = JSON.parse(event.data);
  
      if (data.type === 'start 2v2') {
        console.log('🎮 2v2 Match found, starting game...');
  
        toggleElements.forEach((selector) => {
          const el = matchmaking?.querySelector(selector) as HTMLElement;
          if (el) {
            const isHidden = getComputedStyle(el).display === 'none';
            el.style.display = isHidden ? 'block' : 'none';
          }
        });
  
        const res = await fetch('game.html');
        const html = await res.text();
        gameContainer.innerHTML = html;
        gameContainer.classList.remove('hidden');
  
        const canvas = document.getElementById('gameCanvas') as HTMLCanvasElement;
        if (canvas) {
          const gameModule = await import('./game.js') as any;
          cleanup = gameModule.initGame2v2(canvas, socket);
        }
      } else if (data.type === 'gameOver') {
        matchResult.textContent = `${data.winnerUsername} won! 🎉`;
        matchResult.classList.remove('hidden');
        resetUI(data.winnerUsername);
        setTimeout(() => {
          if (cleanup) cleanup();
          socket?.close();
        }, 5000);
      } else if (data.type === 'end') {
        resetUI();
        setTimeout(() => {
          if (cleanup) cleanup();
          socket?.close();
        }, 5000);
      }
    });
  
    socket.onerror = (err) => {
      console.error('WebSocket error:', err);
      statusText.textContent = '❌ WebSocket error. Try again.';
      resetUI();
    };
  
    socket.onclose = () => {
      console.log('🔌 WebSocket closed (2v2)');
      resetUI();
    };
  });

  startBtn.addEventListener('click', async () => {
    const token = sessionStorage.getItem('authToken');
    if (!token) {
      alert('No auth token found');
      return;
    }

    statusText.textContent = '🔍 Searching for a match...';
    FriendInvite.style.display = 'none';
    startBtn2v2.style.display = 'none'
    startBtn.style.display = 'none';
    cancelBtn.classList.remove('hidden');

    socket = new WebSocket(`ws://localhost:3000/game/pong?token=${token}`);

    socket.onopen = () => {
      console.log('🔌 Connected to matchmaking');
      socket!.send(JSON.stringify({ type: 'startMatchmaking' }));
    };

    socket.addEventListener('message', async (event) => {
      const data = JSON.parse(event.data);

      if (data.type === 'start') {
        console.log('🎮 Match found, starting game...');

        toggleElements.forEach((selector) => {
          const el = matchmaking?.querySelector(selector) as HTMLElement;
          if (el) {
            const isHidden = getComputedStyle(el).display === 'none';
            el.style.display = isHidden ? 'block' : 'none';
          }
        });

        // Await the fetch and text reading
        const res = await fetch('game.html');
        const html = await res.text();
        gameContainer.innerHTML = html;
        gameContainer.classList.remove('hidden');

        const canvas = gameContainer.querySelector('#gameCanvas') as HTMLCanvasElement;
        if (canvas) {
          // Await dynamic import
          const { default: initGame } = await import('./game.js') as any;
          console.log("check2");
          cleanup = initGame(canvas, socket);
        }
      }
      else if (data.type === 'gameOver') {
        console.log("message received");
        matchResult.textContent = `${data.winnerUsername} won! 🎉`;
        matchResult.classList.remove('hidden');
      
        console.log(data.winnerUsername)
        resetUI(data.winnerUsername);
        setTimeout(() => {
          if (cleanup) cleanup();
          socket?.close();
        }, 5000);
      }
      else if (data.type === 'end') {
        console.log("🏁 Game ended. Cleaning up...");
        resetUI();
        setTimeout(() => {
          if (cleanup) cleanup();
          socket?.close();
        }, 5000);
      }
    });

    socket.onerror = (err) => {
      console.error('WebSocket error:', err);
      statusText.textContent = '❌ WebSocket error. Try again.';
      resetUI();
    };

    socket.onclose = () => {
      console.log('🔌 WebSocket closed');
      resetUI();
    };
  });

  cancelBtn.addEventListener('click', () => {
    socket?.close();
    startBtn.style.display = 'block';
    FriendInvite.style.display = 'block';
    statusText.textContent = 'Matchmaking cancelled.';
    resetUI();
  });
}

export function resetUI(winnerUsername?: string) {
  statusText.textContent = 'Click the button below to enter matchmaking.';
  startBtn.style.display = 'inline-block';
  startBtn2v2.style.display = 'inline-block';
  FriendInvite.style.display = 'inline-block';
  gameContainer.classList.add('hidden');

  if (winnerUsername) {
    matchResult.textContent = `${winnerUsername} won!`;
    matchResult.style.display = 'block'
    console.log("there is a winner");
    // Hide after 3 seconds
    setTimeout(() => {
      matchResult.style.display = 'none'
    }, 8000);
  } else {
    matchResult.style.display = 'none'
  }
}
initMatchmaking();