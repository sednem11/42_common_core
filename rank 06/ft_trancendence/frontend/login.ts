const loginBtn = document.getElementById('loginBtn') as HTMLButtonElement | null;
const usernameInput = document.getElementById('username') as HTMLInputElement | null;
const passwordInput = document.getElementById('password') as HTMLInputElement | null;

if (loginBtn && usernameInput && passwordInput) {
  loginBtn.addEventListener('click', async () => {
    const username = usernameInput.value;
    const password = passwordInput.value;

    try {
      const res = await fetch('http://localhost:3000/auth/login', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username, password }),
      });

      const data = await res.json();

      if (data.token) {
        sessionStorage.setItem('authToken', data.token); // 🔐 Save JWT token

        if (data.requires2FA) {
          window.location.href = '/2fa.html';
        } else {
          window.location.href = '/index.html';
        }
      } else {
        alert('Login failed.');
      }
    } catch (error) {
      console.error('Login error:', error);
      alert('An error occurred during login.');
    }
  });
} else {
  console.error('Login form elements not found in the DOM.');
}
