document.addEventListener('DOMContentLoaded', () => {
  const logoutBtn = document.getElementById('logoutBtn') as HTMLButtonElement | null;

  if (logoutBtn) {
    logoutBtn.addEventListener('click', async () => {
      try {
        localStorage.removeItem('authToken');
        sessionStorage.removeItem('authToken');

        await fetch('http://localhost:3000/auth/logout', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer ${localStorage.getItem('authToken') || sessionStorage.getItem('authToken')}`
          }
        });

        window.location.href = '../login.html';
      } catch (err) {
        console.error('Erro ao fazer logout:', err);
        alert('Erro ao tentar fazer logout.');
      }
    });
  }
});