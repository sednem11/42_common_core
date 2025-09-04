import { authenticate } from '../middlewares/authenticate';
import { requireRole } from '../middlewares/requireRole';

app.get('/profile', { preValidation: [authenticate] }, async (req, reply) => {
  reply.send({ msg: 'Perfil autenticado!' });
});

app.get('/admin-only', { preValidation: [requireRole('admin')] }, async (req, reply) => {
  reply.send({ msg: 'Acesso de admin confirmado.' });
});