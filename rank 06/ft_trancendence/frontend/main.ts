const navButtons = document.querySelectorAll('.nav-btn');
const views = document.querySelectorAll('.view');
const chatContainer = document.getElementById('chatContainer')!;
const matchmaking = document.getElementById('matchmaking')!;
const profileLayout = document.getElementById('profileLayout')!;

function parseJwt(token: string): any {
  try {
    const base64Url = token.split('.')[1];
    const base64 = base64Url.replace(/-/g, '+').replace(/_/g, '/');
    const jsonPayload = decodeURIComponent(
      atob(base64)
        .split('')
        .map(c => '%' + c.charCodeAt(0).toString(16).padStart(2, '0'))
        .join('')
    );
    return JSON.parse(jsonPayload);
  } catch (e) {
    console.error('Failed to parse token', e);
    return null;
  }
}
// Inject HTML and script once
async function injectHTMLAndScript(container: HTMLElement, htmlPath: string, scriptPath: string, innerWrapperClass?: string) {
  if (container.dataset.loaded) return;
  try {
    const res = await fetch(htmlPath);
    const html = await res.text();
    const tempDiv = document.createElement('div');
    tempDiv.innerHTML = html;
    tempDiv.querySelectorAll('script').forEach(script => script.remove());
    container.innerHTML = innerWrapperClass
      ? `<div class="${innerWrapperClass}">${tempDiv.innerHTML}</div>`
      : tempDiv.innerHTML;
    container.dataset.loaded = 'true';

    const script = document.createElement('script');
    script.src = scriptPath;
    script.type = 'module';
    script.defer = true;
    document.body.appendChild(script);

    console.log(`✅ Injected ${htmlPath} and ${scriptPath}`);
  } catch (err) {
    console.error(`❌ Failed to load ${htmlPath} or ${scriptPath}:`, err);
  }
}

// ✅ Preload everything at startup
document.addEventListener('DOMContentLoaded', async () => {
  await injectHTMLAndScript(matchmaking, 'matchmaking.html', '/dist/matchmaking.js', 'inner-matchmaking');
  await injectHTMLAndScript(chatContainer, 'chat.html', '/dist/chat.js');

  document.getElementById('profile')!.style.display = 'none';
  // Optionally: Hide elements initially
  const chatHideEls = chatContainer.querySelectorAll('#roomList, .invite-button, #addFriendModal, .chat-container');
  chatHideEls.forEach((el) => (el as HTMLElement).style.display = 'none');
});

// ✅ Handle nav clicks
navButtons.forEach((btn) => {
  btn.addEventListener('click', async () => {
    const target = btn.getAttribute('data-view');

    // Hide all views
    views.forEach((view) => view.classList.add('hidden'));

    // Handle chat tab
    if (target === 'chat') {
      const profile = document.getElementById('profile');
      if(profile){
        if (profile.style.display === 'block')
          profile.style.display = 'none';
      }
      const chat = document.getElementById('chat');
      if (chat) chat.classList.toggle('hidden');

      const toggleElements = [
        '#chat',
        '#roomList',
        '.invite-button',
        '#addFriendModal',
        '#chatContainer',
        '.chat-container'
      ];
      toggleElements.forEach((selector) => {
        const el = chatContainer.querySelector(selector) as HTMLElement;
        if (el) {
          const isHidden = getComputedStyle(el).display === 'none';
          el.style.display = isHidden ? 'block' : 'none';
        }
      });
      return;
    }

    // Handle matchmaking tab
    if (target === 'matchmaking') {
      const toggleElements = [
        '#matchmakingView',
      ];
      toggleElements.forEach((selector) => {
        const el = matchmaking.querySelector(selector) as HTMLElement;
        if (el) {
          const isHidden = getComputedStyle(el).display === 'none';
          el.style.display = isHidden ? 'block' : 'none';
        }
      });
      return;
    }
    if (target === 'profile') {
      const chat = document.getElementById('chat');
      if (chat) chat.classList.add('hidden');
    
      const toggleElements = [
        '#chat',
        '#roomList',
        '.invite-button',
        '#addFriendModal',
        '#chatContainer',
        '.chat-container'
      ];
      toggleElements.forEach((selector) => {
        const el = chatContainer.querySelector(selector) as HTMLElement | null;
        if (el && getComputedStyle(el).display !== 'none') {
          el.style.display = 'none';
        }
      });
      const profile = document.getElementById('profile');
    
      if (profile && profile.style.display === 'none') {
        profile.style.display = 'block';
    
        // Inject profile layout & script only if not loaded
        const wasLoaded = profileLayout.dataset.loaded;
        await injectHTMLAndScript(profileLayout, 'profile.html', '/dist/profile.js');
    
        // ✅ Only call loadFriends AFTER injection
        if (wasLoaded) {
          // If already loaded, manually call loadFriends again
          const mod = await import('./profile.js');
          const token = sessionStorage.getItem('authToken');
          if (!token) {
            console.error('No token found in sessionStorage');
            return;
          }

          const payload = parseJwt(token);
          if (!payload || !payload.username) {
            console.error('Username not found in token payload');
            return;
          }

          const username = payload.username;
          // now call your function with username

          mod.loadFriendsAndMatchHistory?.(username); // Call it if it's exported
        }
      } else if (profile) {
        profile.style.display = 'none';
      }
      return;
    }
  });
});

// 🔔 Notification toggle
const toggleBtn = document.getElementById('toggleNotifications') as HTMLButtonElement | null;
const notificationPanel = document.getElementById('notificationsPanel') as HTMLElement | null;

toggleBtn?.addEventListener('click', () => {
  if (!notificationPanel) return;
  const isHidden = notificationPanel.style.display === 'none' || getComputedStyle(notificationPanel).display === 'none';
  notificationPanel.style.display = isHidden ? 'block' : 'none';

  views.forEach((view) => view.classList.add('hidden'));
});

// 🔔 Add notification
export function addNotification(message: string, onAccept?: () => void, onDecline?: () => void) {
  const list = document.getElementById('notificationList') as HTMLUListElement | null;
  if (!list) return;

  const li = document.createElement('li');
  li.className = "flex flex-col space-y-2";

  const text = document.createElement('span');
  text.textContent = message;
  li.appendChild(text);

  if (onAccept || onDecline) {
    const buttonContainer = document.createElement('div');
    buttonContainer.className = 'flex justify-end space-x-2';

    if (onAccept) {
      const acceptBtn = document.createElement('button');
      acceptBtn.textContent = 'Accept';
      acceptBtn.className = 'bg-green-500 hover:bg-green-600 text-white px-3 py-1 rounded';
      acceptBtn.onclick = () => {
        onAccept();
        li.remove();
      };
      buttonContainer.appendChild(acceptBtn);
    }

    if (onDecline) {
      const declineBtn = document.createElement('button');
      declineBtn.textContent = 'Decline';
      declineBtn.className = 'bg-red-500 hover:bg-red-600 text-white px-3 py-1 rounded';
      declineBtn.onclick = () => {
        onDecline();
        li.remove();
      };
      buttonContainer.appendChild(declineBtn);
    }

    li.appendChild(buttonContainer);
  }

  list.appendChild(li);
}

// 🔔 Close notification panel if clicking outside
document.addEventListener('click', (event) => {
  if (!notificationPanel || !toggleBtn) return;
  const target = event.target as HTMLElement;
  if (
    !notificationPanel.contains(target) &&
    target !== toggleBtn &&
    getComputedStyle(notificationPanel).display !== 'none'
  ) {
    notificationPanel.style.display = 'none';
  }
});
