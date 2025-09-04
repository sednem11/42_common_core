// import { validateUsername, validatePassword } from '../utils/validateInput';

// if (!validateUsername(username)) {
//   return reply.code(400).send({ error: 'Username inválido.' });
// }

// if (!validatePassword(password)) {
//   return reply.code(400).send({ error: 'Password muito curta.' });
// }


// export function validateUsername(username: string): boolean {
//   const re = /^[a-zA-Z0-9_]{3,20}$/;
//   return re.test(username);
// }

// export function validatePassword(password: string): boolean {
//   return typeof password === 'string' && password.length >= 6;
// }

// export function validateEmail(email: string): boolean {
//   const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
//   return re.test(email);
// }

// export function validateNotEmpty(input: string): boolean {
//   return typeof input === 'string' && input.trim().length > 0;
// }