export default function initGame(canvas: HTMLCanvasElement, socket: WebSocket) {
  console.log("check");
  const ctx = canvas.getContext("2d")!;
  const GAME_WIDTH = 600;
  const GAME_HEIGHT = 2000;

  function resizeCanvas() {
    canvas.width = canvas.parentElement?.clientWidth || window.innerWidth;
    canvas.height = canvas.parentElement?.clientHeight || window.innerHeight;
  }

  window.addEventListener("resize", resizeCanvas);
  resizeCanvas();

  let currentDirection: 'up' | 'down' | 'stop' = 'stop';

  const handleKeyDown = (e: KeyboardEvent) => {
    if (e.key === "ArrowUp") currentDirection = "up";
    else if (e.key === "ArrowDown") currentDirection = "down";
    else return;

    socket.send(JSON.stringify({ type: "move", direction: currentDirection }));
  };

  const handleKeyUp = () => {
    currentDirection = "stop";
    socket.send(JSON.stringify({ type: "move", direction: currentDirection }));
  };

  window.addEventListener("keydown", handleKeyDown);
  window.addEventListener("keyup", handleKeyUp);

  let gameState: any = null;

  socket.onopen = () => console.log("Connected to Pong server");
  socket.onerror = (error) => console.error("WebSocket error:", error);

  socket.onmessage = (event: MessageEvent) => {
    try {
      const data = JSON.parse(event.data);
      switch (data.type) {
        case "start 2v2":
          console.log(`Game started as ${data.role}`);
          break;
        case "joined":
          console.log(data.message);
          break;
        case "state":
          gameState = data;
          draw();
          break;

        // Notice no 'gameOver' case here — handled externally
      }
    } catch (err) {
      console.error("Invalid JSON from server:", event.data);
    }
  };

  function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    const scaleX = canvas.width / GAME_WIDTH;
    const scaleY = canvas.height / GAME_HEIGHT;

    // Draw ball (red)
    ctx.fillStyle = 'red';
    ctx.beginPath();
    ctx.arc(
      gameState.ball.x * scaleX,
      gameState.ball.y * scaleY,
      10 * ((scaleX + scaleY) / 2),
      0,
      Math.PI * 2
    );
    ctx.fill();

    // Draw paddles (green)
    ctx.fillStyle = 'green';
    ctx.fillRect(
      10 * scaleX,
      gameState.paddles.left * scaleY,
      10 * scaleX,
      150 * scaleY
    );

    ctx.fillRect(
      (GAME_WIDTH - 20) * scaleX,
      gameState.paddles.right * scaleY,
      10 * scaleX,
      150 * scaleY
    );

    // Draw score (white)
    ctx.fillStyle = "white";
    ctx.font = `${20 * ((scaleX + scaleY) / 2)}px Arial`;
    ctx.fillText(`${gameState.scores.left}`, canvas.width / 3, 40);
    ctx.fillText(`${gameState.scores.right}`, (2 * canvas.width) / 3, 40);
  }

  // Optional cleanup you can return
  return () => {
    window.removeEventListener("keydown", handleKeyDown);
    window.removeEventListener("keyup", handleKeyUp);
  };
}

export function initGame2v2(canvas: HTMLCanvasElement, socket: WebSocket) {
  console.log("check1");
  const ctx = canvas.getContext("2d")!;
  const GAME_WIDTH = 600;
  const GAME_HEIGHT = 2000;

  function resizeCanvas() {
    canvas.width = canvas.parentElement?.clientWidth || window.innerWidth;
    canvas.height = canvas.parentElement?.clientHeight || window.innerHeight;
  }

  window.addEventListener("resize", resizeCanvas);
  resizeCanvas();

  let currentDirection: 'up' | 'down' | 'stop' = 'stop';

  const handleKeyDown = (e: KeyboardEvent) => {
    if (e.key === "ArrowUp") currentDirection = "up";
    else if (e.key === "ArrowDown") currentDirection = "down";
    else return;

    socket.send(JSON.stringify({ type: "move", direction: currentDirection }));
  };

  const handleKeyUp = () => {
    currentDirection = "stop";
    socket.send(JSON.stringify({ type: "move", direction: currentDirection }));
  };

  window.addEventListener("keydown", handleKeyDown);
  window.addEventListener("keyup", handleKeyUp);

  let gameState: any = null;

  socket.onopen = () => console.log("Connected to Pong server");
  socket.onerror = (error) => console.error("WebSocket error:", error);

  socket.onmessage = (event: MessageEvent) => {
    try {
      const data = JSON.parse(event.data);
      switch (data.type) {
        case "start":
          console.log(`Game started as ${data.role}`);
          break;
        case "joined":
          console.log(data.message);
          break;
        case "state":
          gameState = data;
          draw();
          break;

        // Notice no 'gameOver' case here — handled externally
      }
    } catch (err) {
      console.error("Invalid JSON from server:", event.data);
    }
  };

  function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    const scaleX = canvas.width / GAME_WIDTH;
    const scaleY = canvas.height / GAME_HEIGHT;

    // Draw ball (red)
    ctx.fillStyle = 'red';
    ctx.beginPath();
    ctx.arc(
      gameState.ball.x * scaleX,
      gameState.ball.y * scaleY,
      10 * ((scaleX + scaleY) / 2),
      0,
      Math.PI * 2
    );
    ctx.fill();

    // Draw paddles (green)
    ctx.fillStyle = 'green';

    ctx.fillRect(10 * scaleX, gameState.paddles.left1 * scaleY, 10 * scaleX, 150 * scaleY);
    ctx.fillRect(10 * scaleX, gameState.paddles.left2 * scaleY, 10 * scaleX, 150 * scaleY);
    
    ctx.fillRect((GAME_WIDTH - 20) * scaleX, gameState.paddles.right1 * scaleY, 10 * scaleX, 150 * scaleY);
    ctx.fillRect((GAME_WIDTH - 20) * scaleX, gameState.paddles.right2 * scaleY, 10 * scaleX, 150 * scaleY);
    

    // Draw score (white)
    ctx.fillStyle = "white";
    ctx.font = `${20 * ((scaleX + scaleY) / 2)}px Arial`;
    ctx.fillText(`${gameState.scores.left}`, canvas.width / 3, 40);
    ctx.fillText(`${gameState.scores.right}`, (2 * canvas.width) / 3, 40);
  }

  // Optional cleanup you can return
  return () => {
    window.removeEventListener("keydown", handleKeyDown);
    window.removeEventListener("keyup", handleKeyUp);
  };
}